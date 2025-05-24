/**
 **************************
 * @file           : init.h
 * @author         : Nimish Sabnis
 * @brief          : Header file for init.c
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

#ifndef INIT_H
#define INIT_H

#include "stm32f091xc.h"
#include <stdint.h>

/**
 * @brief  Definitions for system timings.
 */
#define SYS_TICK_HZ        1000U
#define MS_TO_TICKS(ms)    ((ms) * (SystemCoreClock / SYS_TICK_HZ))

/**
 * @brief  Definitions for led at PA5
 */
#define ULED_GPIO_PORT     GPIOA
#define ULED_GPIO_PIN      5U

/**
 * @brief  Definitions for UART2
 */
#define UART2_GPIO_PORT    GPIOA
#define UART2_TX_PIN       2U
#define UART2_RX_PIN       3U
#define UART2_AF           1U
#define UART2_BAUD         9600U


/* TIM14 (1 µs tick if SystemCoreClock is 48 MHz) */
#define TIM14_TIMER        TIM14
#define TIM14_PRESCALER    ((SystemCoreClock / 1000000U) - 1U)

/* Global time variable updated by SysTick */
extern volatile uint32_t g_time_ms;


/**
 * @brief  Initializes SysTick to generate 1 ms interrupts.
 */
void init_systick(void);
/**
 * @brief  Initializes UART2 at 9600 baud (8N1) on PA2/PA3.
 */
void init_uart2(void);

/**
 * @brief  Initializes TIM14 for 1 µs tick.
 */
void init_uleD(void);
/**
 * @brief  Initializes User LED (ULED) on PA5.
 */
void init_tim14(void);
/**
 * @brief  Calls all initialization functions.
 */
void init_all(void);

/**
 * @brief  Returns the current time in ms since startup.
 */
uint32_t now(void);
/**
 * @brief  Blocking delay in milliseconds using SysTick.
 */
void delay_ms(uint32_t ms);


#endif // INIT_H
