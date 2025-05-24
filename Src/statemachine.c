/**
 **************************
 * @file           : statemachine.h
 * @author         : Nimish Sabnis
 * @brief          : Functioning of state machine
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
#include "statemachine.h"

// External globals from main and command processor
extern dht11_t sensor;
extern bool systemActive;
static state_t currentState = STATE_NORMAL;
static uint32_t lastBlinkTime = 0;
static bool ledOn = false;

static StateDef stateTable[NUM_STATES] = {
    [STATE_NORMAL]  = { "Normal",  1000 },
    [STATE_WARNING] = { "Warning",  500 },
    [STATE_ALERT]   = { "Alert",    200 }
};

void state_machine_init(void) {
    currentState = STATE_NORMAL;
    lastBlinkTime = now();
    ledOn = false;
    GPIOA->ODR &= ~(1 << 5);  // LED OFF initially at boot
}

void state_machine_run(void) {
    if (!systemActive) {
        // Do nothing until started
        return;
    }

    uint32_t currentTime = now();
    uint8_t temp = sensor.temperature;  // integer temperature

    // Check thresholds and update state
    state_t prevState = currentState;
    if (temp < TEMP_NORMAL_THRESHOLD) {
        currentState = STATE_NORMAL;
    } else if (temp < TEMP_WARNING_THRESHOLD) {
        currentState = STATE_WARNING;
    } else {
        currentState = STATE_ALERT;
    }

    // Print state change with full readings
    if (currentState != prevState) {
        LOG("State: %s (%u.%u°C, %u.%u%%)\r\n",
            stateTable[currentState].name,
            sensor.temperature, sensor.temp_decimal,
            sensor.humidity, sensor.hum_decimal);
    }

    // Handle LED blinking at the current state's rate
    if ((currentTime - lastBlinkTime) >= stateTable[currentState].blinkRateMs) {
        ledOn = !ledOn;
        if (ledOn) {
            GPIOA->ODR |= (1 << 5);
        } else {
            GPIOA->ODR &= ~(1 << 5);
        }
        lastBlinkTime = currentTime;
    }
}
