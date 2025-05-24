/**
 **************************
 * @file           : dht11.h
 * @author         : Nimish Sabnis
 * @brief          : Header file for dht11.c
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

#ifndef DHT11_H
#define DHT11_H

#include <stdint.h>
#include "stm32f091xc.h"


/**
 * @brief definitions for pin & port configuration
 */
#define DHT11_GPIO_PORT        GPIOA
#define DHT11_GPIO_PIN         6U


/**
 * @brief Computing mask/position once
 */
#define DHT11_PIN_POS          (DHT11_GPIO_PIN * 2U)
#define DHT11_PIN_MODER_MASK   (3U << DHT11_PIN_POS)
#define DHT11_PIN_OUTPUT_MODE  (1U << DHT11_PIN_POS)
#define DHT11_PIN_BIT          (1U << DHT11_GPIO_PIN)

/**
 * @brief  Timing parameters (µs)
 */
#define DHT11_START_LOW_US     1000U
#define DHT11_START_HIGH_US    30U
#define DHT11_TIMEOUT_US       1000U

/**
 * @brief  Sensor data structure for integer and one decimal place
 */
typedef struct {
    uint8_t temperature;
    uint8_t temp_decimal;
    uint8_t humidity;
    uint8_t hum_decimal;
} dht11_t;

/**
 * @brief  Initialize DHT driver on DHT11_GPIO_PIN with given timer for microsecond delays.
 * @param  sensor Pointer to dht11_t struct
 * @param  timer  Any TIM_TypeDef configured to count µs ticks
 */
void init_dht11(dht11_t *sensor, TIM_TypeDef *timer);

/**
 * @brief  Read temperature and humidity from DHT sensor
 * @param  sensor Pointer to dht11_t struct where readings are stored
 * @return 1 on success (valid CRC), 0 on failure
 */
uint8_t readDHT11(dht11_t *sensor);

#endif // DHT11_H
