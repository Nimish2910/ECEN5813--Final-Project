
/**
 ******************************************************************************
 * @file           : config.h
 * @author         : Nimish Sabnis
 * @brief          : Configuration file to toggle between release and debug mode
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>


#ifdef DEBUG
    #define LOG(...) printf(__VA_ARGS__)
#else
    #define LOG(...) /* No logging in Release */
#endif

#endif /* LOG_H_ */
