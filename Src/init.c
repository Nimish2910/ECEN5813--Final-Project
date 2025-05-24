/**
 **************************
 * @file           : init.c
 * @author         : Nimish Sabnis
 * @brief          : Initialization of timer and uart
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


#include "init.h"

volatile uint32_t g_time_ms = 0;

void init_systick(void) {
    SysTick->LOAD = (SystemCoreClock / SYS_TICK_HZ) - 1U;
    SysTick->VAL  = 0U;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk
                  | SysTick_CTRL_TICKINT_Msk
                  | SysTick_CTRL_ENABLE_Msk;
}


uint32_t now(void) {
    return g_time_ms;
}

void delay_ms(uint32_t ms) {
    uint32_t start = now();
    while ((now() - start) < ms) {
        // busy wait
    }
}

/**
 * @brief  SysTick interrupt handler (called every 1 ms).
 */
void SysTick_Handler(void) {
    g_time_ms++;
}




void init_uart2(void) {
    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    UART2_GPIO_PORT->MODER &= ~((0x3U << (UART2_TX_PIN * 2))
                              | (0x3U << (UART2_RX_PIN * 2)));
    UART2_GPIO_PORT->MODER |=  ((0x2U << (UART2_TX_PIN * 2))
                              | (0x2U << (UART2_RX_PIN * 2)));
    UART2_GPIO_PORT->AFR[0] &= ~((0xFU << (UART2_TX_PIN * 4))
                               | (0xFU << (UART2_RX_PIN * 4)));
    UART2_GPIO_PORT->AFR[0] |=  ((UART2_AF << (UART2_TX_PIN * 4))
                               | (UART2_AF << (UART2_RX_PIN * 4)));
    USART2->BRR  = SystemCoreClock / UART2_BAUD;
    USART2->CR1  = USART_CR1_TE | USART_CR1_RE;
    USART2->CR1 |=  USART_CR1_UE;
}


void init_tim14(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
    TIM14_TIMER->PSC = TIM14_PRESCALER;
    TIM14_TIMER->CR1 |= TIM_CR1_CEN;
}


void init_uleD(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    ULED_GPIO_PORT->MODER &= ~(0x3U << (ULED_GPIO_PIN * 2));
    ULED_GPIO_PORT->MODER |=  (0x1U << (ULED_GPIO_PIN * 2));
    ULED_GPIO_PORT->ODR   &= ~(1U << ULED_GPIO_PIN);
}


void init_all(void) {
    init_systick();
    init_uart2();
    init_uleD();
    init_tim14();
}
