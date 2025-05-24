/**
 **************************
 * @file           : statemachine.h
 * @author         : Nimish Sabnis
 * @brief          : header file of state machine
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
#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "init.h"
#include "dht11.h"
#include "config.h"
#include <stdint.h>
#include <stdbool.h>
/**
 * @brief setting thresholds for the Statemachine
 */
#define TEMP_NORMAL_THRESHOLD   25  // Below this = Normal
#define TEMP_WARNING_THRESHOLD  30  // Between Warning

/**
 * @brief enum for states
 */
typedef enum {
    STATE_NORMAL = 0,
    STATE_WARNING,
    STATE_ALERT,
    NUM_STATES
} state_t;
/**
 * @brief structure for blink rate
 */
typedef struct {
    const char *name;
    uint32_t blinkRateMs;
} StateDef;
/**
  * @brief Initializes the state machine to its default (NORMAL) state.
  */
void state_machine_init(void);
/**
  * @brief Executes one cycle of the state machine logic (state update & LED blink).
  */
void state_machine_run(void);

#endif // STATEMACHINE_H
