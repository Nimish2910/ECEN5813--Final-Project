/**
 **************************
 * @file           : test_statemachine.h
 * @author         : Nimish Sabnis
 * @brief          : header file of Automated test case for state machine
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
#ifndef TEST_STATEMACHINE_H
#define TEST_STATEMACHINE_H
#include "config.h"
#include "init.h"
#include <stdint.h>
#include "dht11.h"

/**
 * @brief  Initialize the test state‐machine stub.
 *         Call once before using test_readDHT11().
 */
void test_init(void);

/**
 * @brief  Fills in dht values based on 5-second window.
 * @param  dht  pointer to sensor struct
 * @return always 1 to indicate “fake” read succeeded
 */
uint8_t test_readDHT11(dht11_t *dht);

#endif // TEST_STATEMACHINE_H
