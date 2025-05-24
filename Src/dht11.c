/**
 **************************
 * @file           : dht11.c
 * @author         : Nimish Sabnis
 * @brief          : Function and calculations of the DHT sensor
 **************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 **************************
 */
#include "dht11.h"
#include <stddef.h>

static TIM_TypeDef *dht_timer = NULL; //Pointer to the hardware timer used for generating microsecond delays

// Microsecond delay using TIM counter
static void delay_us(uint32_t us) {
    dht_timer->CNT = 0;
    while (dht_timer->CNT < us) { }
}

// Configuring pin as output
static void set_pin_output(void) {
    DHT11_GPIO_PORT->MODER &= ~DHT11_PIN_MODER_MASK;
    DHT11_GPIO_PORT->MODER |=  DHT11_PIN_OUTPUT_MODE;
}

// Configuring pin as input
static void set_pin_input(void) {
    DHT11_GPIO_PORT->MODER &= ~DHT11_PIN_MODER_MASK;
}

void init_dht11(dht11_t *sensor, TIM_TypeDef *timer) {
    (void)sensor;
    dht_timer = timer;
    // Enabling GPIOA clock
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    // Ensuring that pin is output and held high
    set_pin_output();
    DHT11_GPIO_PORT->ODR |= DHT11_PIN_BIT;
}

uint8_t readDHT11(dht11_t *sensor) {
    uint32_t count;
    uint8_t bits[5] = {0};

    // Start signal
    set_pin_output();
    DHT11_GPIO_PORT->ODR &= ~DHT11_PIN_BIT;
    delay_us(DHT11_START_LOW_US);
    DHT11_GPIO_PORT->ODR |=  DHT11_PIN_BIT;
    delay_us(DHT11_START_HIGH_US);
    set_pin_input();

    // Sensor response: low, high, then low
    count = 0;
    while ((DHT11_GPIO_PORT->IDR & DHT11_PIN_BIT) && ++count < DHT11_TIMEOUT_US);
    if (count >= DHT11_TIMEOUT_US) return 0;
    count = 0;
    while (!(DHT11_GPIO_PORT->IDR & DHT11_PIN_BIT) && ++count < DHT11_TIMEOUT_US);
    if (count >= DHT11_TIMEOUT_US) return 0;
    count = 0;
    while ((DHT11_GPIO_PORT->IDR & DHT11_PIN_BIT) && ++count < DHT11_TIMEOUT_US);
    if (count >= DHT11_TIMEOUT_US) return 0;

    // 3) Reading 40 bits
    for (int i = 0; i < 40; i++) {
        count = 0;
        while (!(DHT11_GPIO_PORT->IDR & DHT11_PIN_BIT) && ++count < DHT11_TIMEOUT_US);
        if (count >= DHT11_TIMEOUT_US) return 0;

        // The length of the HIGH pulse determines 0 or 1
        delay_us(DHT11_START_HIGH_US);
        if (DHT11_GPIO_PORT->IDR & DHT11_PIN_BIT) {
            bits[i / 8] |= (1U << (7 - (i % 8)));
        }

        count = 0;
        while ((DHT11_GPIO_PORT->IDR & DHT11_PIN_BIT) && ++count < DHT11_TIMEOUT_US);
        if (count >= DHT11_TIMEOUT_US) return 0;
    }

    //  verify
    uint16_t raw_hum  = (bits[0] << 8) | bits[1];
    uint16_t raw_tmp  = (bits[2] << 8) | bits[3];
    uint8_t checksum  = bits[4];
    if ((((bits[0] + bits[1] + bits[2] + bits[3]) & 0xFF) != checksum)) {
        return 0;
    }

    // Store with one decimal place
    sensor->humidity     = raw_hum  / 10;
    sensor->hum_decimal  = raw_hum  % 10;
    uint16_t tv          = raw_tmp & 0x7FFF;
    sensor->temperature  = tv / 10;
    sensor->temp_decimal = tv % 10;

    return 1;
}
