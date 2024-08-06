/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define FEEDBACK_LED_UNUSED_Pin GPIO_PIN_1
#define FEEDBACK_LED_UNUSED_GPIO_Port GPIOA
#define FEEDBACK_LED2_UNUSED_Pin GPIO_PIN_2
#define FEEDBACK_LED2_UNUSED_GPIO_Port GPIOA
#define FAN_Pin GPIO_PIN_7
#define FAN_GPIO_Port GPIOA
#define SIGN_LEFT_Pin GPIO_PIN_0
#define SIGN_LEFT_GPIO_Port GPIOB
#define SIGN_RIGHT_Pin GPIO_PIN_1
#define SIGN_RIGHT_GPIO_Port GPIOB
#define BRAKE_Pin GPIO_PIN_2
#define BRAKE_GPIO_Port GPIOB
#define BACK_LIGHT_Pin GPIO_PIN_10
#define BACK_LIGHT_GPIO_Port GPIOB
#define FRONT_LIGHT_Pin GPIO_PIN_11
#define FRONT_LIGHT_GPIO_Port GPIOB
#define CAMERA_Pin GPIO_PIN_12
#define CAMERA_GPIO_Port GPIOB
#define HORN_Pin GPIO_PIN_13
#define HORN_GPIO_Port GPIOB
#define SENZOR_CURENT_Pin GPIO_PIN_14
#define SENZOR_CURENT_GPIO_Port GPIOB
#define FRONT_LIGHT_OFFLINE_MODE_Pin GPIO_PIN_15
#define FRONT_LIGHT_OFFLINE_MODE_GPIO_Port GPIOB
#define BACK_LIGHT_OFFLINE_MODE_Pin GPIO_PIN_8
#define BACK_LIGHT_OFFLINE_MODE_GPIO_Port GPIOA
#define ENABLE_OFFLINE_MODE_Pin GPIO_PIN_9
#define ENABLE_OFFLINE_MODE_GPIO_Port GPIOA
#define BRAKE_OFFLINE_MODE_Pin GPIO_PIN_10
#define BRAKE_OFFLINE_MODE_GPIO_Port GPIOA
#define RESERVE_OFFLINE_MODE_Pin GPIO_PIN_4
#define RESERVE_OFFLINE_MODE_GPIO_Port GPIOB
#define CAMERA_OFFLINE_MODE_Pin GPIO_PIN_5
#define CAMERA_OFFLINE_MODE_GPIO_Port GPIOB
#define HORN_OFFLINE_MODE_Pin GPIO_PIN_6
#define HORN_OFFLINE_MODE_GPIO_Port GPIOB
#define SIGN_RIGHT_OFFLINE_MODE_Pin GPIO_PIN_7
#define SIGN_RIGHT_OFFLINE_MODE_GPIO_Port GPIOB
#define FAN_OFFLINE_MODE_Pin GPIO_PIN_8
#define FAN_OFFLINE_MODE_GPIO_Port GPIOB
#define SIGN_LEFT_OFFLINE_MODE_Pin GPIO_PIN_9
#define SIGN_LEFT_OFFLINE_MODE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
