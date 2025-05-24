/**
 **************************
 * @file           : command_processor.c
 * @author         : Nimish Sabnis
 * @brief          : Functioning of for Command Processor
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
#include "command_processor.h"

#define CMD_BUF_SIZE 64
#define TX_BUF_SIZE 128

static char    cmd_buffer[CMD_BUF_SIZE];
static uint8_t cmd_index;

// Global mode flag (real or test) and active flag
data_mode_t current_mode = MODE_REAL;
bool systemActive = false;

static void uart2_tx_char(char c) {
    while (!(USART2->ISR & USART_ISR_TXE));
    USART2->TDR = (uint8_t)c;
}

static void uart2_tx_str(const char *s) {
    while (*s) uart2_tx_char(*s++);
}
// print the prompt
static void uart2_prompt(void) {
   uart2_tx_str(">> ");
}

// Process a complete command string
static void process_command(const char *cmd) {
    if (strcmp(cmd, "start") == 0) {
    	uart2_tx_str("RUNNING WITH DHT READINGS \r\n");
        // Start in real sensor mode
        current_mode = MODE_REAL;
        systemActive = true;
        state_machine_init();  // reset LED and state
    }
    else if (strcmp(cmd, "test") == 0) {
        // Start in test mode
        uart2_tx_str("RUNNING THE AUTOMATED TESTCASE\r\n");
        current_mode = MODE_TEST;
        systemActive = true;
        state_machine_init();  // reset LED and state
    }
    else{
    	 uart2_tx_str("UNKNOWN COMMAND \r\n");
    }

}

void command_processor_init(void) {
    cmd_index = 0;
    memset(cmd_buffer, 0, CMD_BUF_SIZE);
    uart2_prompt();
}

void command_processor_run(void) {
    // Check if a character was received on UART2
    if (USART2->ISR & USART_ISR_RXNE) {
        char ch = (char)USART2->RDR;
        uart2_tx_char( ch); // to print the string on serial monitor with local echo off.
        if (ch == '\r' || ch == '\n') {
            if (cmd_index) {
                cmd_buffer[cmd_index] = '\0';
                process_command(cmd_buffer);
                cmd_index = 0;
            }
        }
        else if (cmd_index < CMD_BUF_SIZE - 1) {
            // Append character to command buffer
            cmd_buffer[cmd_index++] = ch;
        }
        else {
            // Buffer overflow, reset
            cmd_index = 0;
        }
    }
}
