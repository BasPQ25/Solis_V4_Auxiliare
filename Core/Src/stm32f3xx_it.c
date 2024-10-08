/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "functions.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


extern CAN_HandleTypeDef hcan;
extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef hadc4;


//auxiliary state variables when in NORMAL MODE OR OFFLINE MODE
	aux_state aux = {.state = 0x00};
	aux_state* auxiliary = &aux;

	aux_state Offline = {.state = 0x00};
	aux_state* Offline_Mode = &Offline;

//Signal left and right SWITCH STATE
	bool Toggle_State_Right = OFF;
	bool Toggle_State_Left = OFF;

	uint8_t Sign_Left_500ms_Timer = 0; // numaram pana la 10 ca sa avem 500ms intre toggle, STANDARD SEMNALIZARI
	uint8_t Sign_Right_500ms_Timer = 0;

//adc value
	uint16_t adc_Value = 0;

//Dashboard Activity variable
	uint8_t Dash_Activity = 0;

//Offline MODE SWITCH
	bool Offline_Mode_Switch = OFF;

//Activity Check for Auxiliary
	uint8_t Activity_Check[1];


/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles USB low priority or CAN_RX0 interrupts.
  */
void USB_LP_CAN_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN USB_LP_CAN_RX0_IRQn 0 */

	static CAN_RxHeaderTypeDef Rx_Dash_Header;
	static uint8_t Rx_Dash_Data[1];

  /* USER CODE END USB_LP_CAN_RX0_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan);
  /* USER CODE BEGIN USB_LP_CAN_RX0_IRQn 1 */

  //Get CAN message
  	  HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &Rx_Dash_Header, Rx_Dash_Data);

  //Get CAN message only if Offline Mode Switch is OFF
  	  if(Offline_Mode_Switch == OFF)
  	  {
  		  auxiliary->state = Rx_Dash_Data[0];
  		  Dash_Activity = 0;
  	  }

  /* USER CODE END USB_LP_CAN_RX0_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void) // 56 ms
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

    //Check if Offline mode switch is ON/OFF
    	  Offline_Mode_Switch = HAL_GPIO_ReadPin(GPIOA, ENABLE_OFFLINE_MODE_Pin);

    //Dashboard CAN works
    	  if(Dash_Activity <= 100 && Offline_Mode_Switch == OFF) // 5.6 secunde daca nu se trimite niciun semnal de CAN
    	   {
    		  Dash_Activity++;
    	   }
    //Dashboard CAN does not work
    	  else if(Dash_Activity > 100 && Offline_Mode_Switch == OFF)
    	   {
    		   auxiliary->state = SAFE_STATE;
    	   }
    //Offline Mode Switch ENABLED
    	  else if(Offline_Mode_Switch == ON)
    	   {
    		   Update_Buttons_State_Offline_Mode( Offline_Mode );
    		   auxiliary->state = Offline_Mode->state;

    		   //Reactivam Comunicarea CAN DUPA CE IESIM DIN OFFLINE MODE???Intreaba baietii
    		   	   Dash_Activity = 0;
    	   }

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void) //76 ms
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  //Update auxiliary state based on TIM3 logic
    	  Update_Aux_State( auxiliary , Toggle_State_Right , Toggle_State_Left , Sign_Left_500ms_Timer, Sign_Right_500ms_Timer );

  //Check if Auxiliary works just as planned
    	  Get_Adc_Value( hadc4 , auxiliary, Toggle_State_Right , Toggle_State_Left,  adc_Value, Activity_Check);

  //Transmit Activity Check CAN frame
    	  Can_Transmit_Auxiliary_Activity_Check( hcan , Activity_Check );

  /* USER CODE END TIM3_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
