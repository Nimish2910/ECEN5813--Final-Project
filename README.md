[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/FlzTjSEb)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=18292084&assignment_repo_type=AssignmentRepo)
# FINAL PROJECT ECEN 5813 : SMART TEMPERATURE MONITORING SYSTEM USING STATEMACHINE
## Overview
This project implements an automated monitoring system for temperature and humidity using a state machine architecture on the STM32 Nucleo-64 board. The system monitors environmental conditions in real-time between different operational states based on thresholds, providing visual feedback through LED blinking patterns.

## Features
- Real-time temperature and humidity monitoring using DHT sensor
- State machine implementation with multiple operational states:
  - **Normal State**: Conditions below thresholds (slow LED blink with internal LED)
  - **Warning State**: Approaching thresholds (medium LED blink with internal LED)
  - **Alert State**: Exceeding thresholds (fast LED blink with internal LED)
- Interactive UART command interface for:
  - Adjusting between Live sensor mode and Automated test mode
  - Checking current system status
  - Viewing sensor readings
- Robust error handling for sensor communication failures
- Visual feedback through programmable LED sequences

## Hardware Requirements
- STM32 Nucleo-64 development board (STM32F091RC)
- DHT temperature and humidity sensor
- LEDs for state indication
- Jumper wires
- USB cable for programming and UART communication

## Software Components
- `main.c`: Entry point and main application loop
- `statemachine.c/h`: State machine implementation for system states
- `dht11.c/h`: DHT sensor interface and reading functions
- `command_processor.c/h`: UART command parsing and execution
- `init.c/h`: System initialization functions
- `syscalls.c`: System call implementations
- `sysmem.c`: Memory management functions
- `config.h`: LOG definitions
- `test_statemachine.c/h`: Test harness for state machine functionality

## Setup and Installation
1. Connect the DHT sensor to the STM32 board:
   - VCC to 3.3V
   - GND to GND
   - DATA to a digital pin currently on D12 (PA6)

2. Connect the indicator LEDs to the appropriate GPIO pins currently on D13 (PA5)

3. Import the project into your preferred IDE (STM32CubeIDE recommended)

4. Build and flash the firmware to the board

## Usage

Available commands:
- `start`: To start statemachine using live temperature readings from DHT.
- `test`: To test statemachine based on automated test.


### LED Indicators
- **Slow blinking** (1Hz): Normal state, conditions are acceptable
- **Medium blinking** (2Hz): Warning state, approaching thresholds
- **Fast blinking** (4Hz): Alert state, thresholds exceeded

## State Machine Logic
The system uses a state machine to manage transitions between operational states:
1. Initialization → Normal state (default)
2. Normal state → Warning state 
3. Warning state → Alert state 
4. Alert state → Warning state 
5. Warning state → Normal state

**Below is Statemachine diagram for real world senario:**

<img width="844" alt="image" src="https://github.com/user-attachments/assets/a833a711-42c9-4b21-be41-1a815ed7b894" />



**Below is Ideal statemachine diagram assuming temperature drops from 30 to below 25 in 1 sec:**

<img width="844" alt="image" src="https://github.com/user-attachments/assets/4c9ea722-624e-41bf-b91f-f453660ddbf9" />


## Development Notes
- The DHT sensor has a reading accuracy of ±0.5°C for temperature and ±2-5% for humidity
- UART command parsing is case-sensitive
- The system samples the DHT22 sensor every 2 seconds to avoid overheating
- Error handling includes sensor timeout detection and communication failure recovery

## Future Enhancements
- Add LCD display support for more detailed status information
- Add new features to command processor
- Implement data logging to onboard storage
- Create transition state LED sequences to visually indicate state changes
- Add support for additional environmental sensors
- Implement wireless communication options (Bluetooth/WiFi)
## Screenshots:
**Terminal Output of Live sensor mode:**

![image](https://github.com/user-attachments/assets/decac35b-a52c-4e7e-8d3e-d6273b47da02)

**Terminal Output of Automated test mode:**

![image](https://github.com/user-attachments/assets/0dffe2cc-e0b1-4143-a99c-ee3d47ec52a5)


**Terminal Output for Testing of DHT sensor after boot:**

<img width="621" alt="image" src="https://github.com/user-attachments/assets/5845c604-6bc8-4302-82d4-77ab03a2bb04" />

## Videos:
https://drive.google.com/drive/folders/1waN7OHmKIWquPgET8MfcERc4bK_sVRkE?usp=sharing

## Acknowledgments
- https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf?    
- https://blog.embeddedexpert.io/?p=646
- STM32F091RC technical reference manual
- Embedded Systems Fundamentals with ARM Cortex-M based Microcontrollers: A Practical Approach, Nucleo-F091RC Edition, Alexander G. Dean, 2021, ARM Education Media UK.    Available from Amazon (paperback or Kindle). Also available as an e-book from the publisher for different fees; see https://www.arm.com/resources/education/books/efficient-embedded-systems. 
- I would like to acknowledge SAs Mohit Chaudhari and Trapti Balgi for their help in debugging. 
 
