/**
 **************************
 * @file           : test_statemachine.c
 * @author         : Nimish Sabnis
 * @brief          : Functioning of Automated test case for state machine
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
#include "test_statemachine.h"

// Duration of each phase in ms
#define PHASE_DURATION_MS 5000U

static uint32_t _start_time;

void test_init(void) {
    // record the millisecond timestamp when test mode begins
    _start_time = now();
}


uint8_t test_readDHT11(dht11_t *dht) {
    uint32_t elapsed = now() - _start_time;
    uint32_t phase   = (elapsed / PHASE_DURATION_MS) % 3;

    switch (phase) {
      case 0: // Normal (<25°C)
        dht->temperature  = 20;
        dht->temp_decimal = 0;
        dht->humidity     = 40;
        dht->hum_decimal  = 0;
        break;

      case 1: // Warning (25–29°C)
        dht->temperature  = 28;
        dht->temp_decimal = 0;
        dht->humidity     = 50;
        dht->hum_decimal  = 0;
        break;

      case 2: // Alert (>=30°C)
      default:
        dht->temperature  = 36;
        dht->temp_decimal = 0;
        dht->humidity     = 60;
        dht->hum_decimal  = 0;
        break;
    }

    return 1;
}
