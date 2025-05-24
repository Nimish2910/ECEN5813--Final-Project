/**
 **************************
 * @file           : main.c
 * @author         : Nimish Sabnis
 * @brief          :
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
#include <stdbool.h>
#include "init.h"
#include "dht11.h"
#include "test_statemachine.h"
#include "statemachine.h"
#include "command_processor.h"
#include "config.h"
#include <stdint.h>

dht11_t sensor;

extern data_mode_t current_mode;
extern bool systemActive;

int main(void) {
    init_all();
    init_dht11(&sensor, TIM14);

    // give the DHT11 time to power up
    delay_ms(2000);

    // health check for sensor
    if (readDHT11(&sensor) || readDHT11(&sensor)) {
        LOG("===DHT WORKING !===\r\n");
    } else {
        LOG("===ERROR: DHT SENSOR IS NOT RESPONDING! PLEASE CHECK OR SENSOR.\r\n===");
    }


    LOG(
    		"ECEN 5813 SMART TEMPERATURE MONITOR USING STATEMACHINE\r\n"
    		    "1. TYPE 'start' for LIVE SENSOR MODE\r\n"
    		    "2. TEST 'test' for  AUTOMATED TEST MODE\r\n"
    );
    command_processor_init();
    delay_ms(1000);
    state_machine_init();
    test_init();

    while (1) {
        command_processor_run();
        state_machine_run();
        if (systemActive) {
            if (current_mode == MODE_REAL) {
                if (readDHT11(&sensor)) {
                    
                }
            } else {
                test_readDHT11(&sensor);
            }
        }
    }
}
