/**
 **************************
 * @file           : command_processor.h
 * @author         : Nimish Sabnis
 * @brief          : Header file for Command Processor
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
#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>
#include "statemachine.h"
#include "stm32f091xc.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
/** Data source mode for temperature readings. */
typedef enum {
    MODE_REAL = 0,
    MODE_TEST = 1
} data_mode_t;

/** Global mode and active flag. */
extern data_mode_t current_mode;
extern bool systemActive;

/** Initialize UART command processor. */
void command_processor_init(void);

/** Poll UART2, build commands, and dispatch them. */
void command_processor_run(void);

#endif /* COMMAND_PROCESSOR_H */
