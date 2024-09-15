
#include "functions.h"


void Update_Aux_State( aux_state* auxiliary)
{
	static uint8_t Sign_Left_500ms_Timer = 9;
	static uint8_t Sign_Right_500ms_Timer = 9;

	static bool Toggle_State_Right = OFF;
	static bool Toggle_State_Left = OFF;


	//iesire sunt negate - Tranzistori tip P
		//avarie
		if( auxiliary->sign_left == ON && auxiliary->sign_right == ON && Toggle_State_Left == Toggle_State_Right)
			{
				Sign_Right_500ms_Timer = Sign_Left_500ms_Timer;
			}
		else if( Toggle_State_Left == ON && Toggle_State_Right == OFF) auxiliary->sign_right = OFF;
		else if( Toggle_State_Left == OFF && Toggle_State_Right == ON) auxiliary->sign_left = OFF;

		//semnalizare stanga
		if( auxiliary->sign_left == ON)
		{
			if(++Sign_Left_500ms_Timer == 10)
			{
				HAL_GPIO_TogglePin(GPIOB, SIGN_LEFT_Pin);
				Toggle_State_Left = !Toggle_State_Left;
				Sign_Left_500ms_Timer = 0;
			}
		}
		else
			{
		//oprire semnalizare
				HAL_GPIO_WritePin(GPIOB, SIGN_LEFT_Pin, !(auxiliary->sign_left) );
				Sign_Left_500ms_Timer = 9;
				Toggle_State_Left = OFF;
			}

		//semanlizare dreapta
		if( auxiliary->sign_right == ON)
		{
			if(++Sign_Right_500ms_Timer == 10)
			{
				HAL_GPIO_TogglePin(GPIOB, SIGN_RIGHT_Pin);
				Toggle_State_Right = !Toggle_State_Right;
				Sign_Right_500ms_Timer = 0;
			}
		}
		else
			{
				//oprire semnalizare
				HAL_GPIO_WritePin(GPIOB, SIGN_RIGHT_Pin, !(auxiliary->sign_right) );
				Sign_Right_500ms_Timer = 9;
				Toggle_State_Right = OFF;
			}

		HAL_GPIO_WritePin(GPIOB, HORN_Pin, !auxiliary->horn);
		HAL_GPIO_WritePin(GPIOA, CAMERA_Pin, !auxiliary->camera);
		HAL_GPIO_WritePin(GPIOB, BACK_LIGHT_Pin, !auxiliary->read_lights);
		HAL_GPIO_WritePin(GPIOB, BRAKE_Pin, !auxiliary->brake);
		HAL_GPIO_WritePin(GPIOA, FAN_Pin, !auxiliary->fan);

		TIM2->CCR4 = 75; //FRONT LIGHT DIMMING, 425 = 75% / 566
}

void Update_Buttons_State_Offline_Mode(aux_state* Offline_Mode)
{
	Offline_Mode->brake = HAL_GPIO_ReadPin(GPIOA, BRAKE_OFFLINE_MODE_Pin);
	Offline_Mode->camera = HAL_GPIO_ReadPin(GPIOB, CAMERA_OFFLINE_MODE_Pin);
	Offline_Mode->fan = HAL_GPIO_ReadPin(GPIOB, FAN_OFFLINE_MODE_Pin);
	Offline_Mode->horn = HAL_GPIO_ReadPin(GPIOB, HORN_OFFLINE_MODE_Pin);
	Offline_Mode->sign_left = HAL_GPIO_ReadPin(GPIOB, SIGN_LEFT_OFFLINE_MODE_Pin);
	Offline_Mode->sign_right = HAL_GPIO_ReadPin(GPIOB, SIGN_RIGHT_OFFLINE_MODE_Pin);
	Offline_Mode->head_lights = HAL_GPIO_ReadPin(GPIOB, FRONT_LIGHT_OFFLINE_MODE_Pin);
	Offline_Mode->read_lights = HAL_GPIO_ReadPin(GPIOB, BACK_LIGHT_OFFLINE_MODE_Pin);

	//avarie
	if( HAL_GPIO_ReadPin(GPIOB, SIGN_LEFT_OFFLINE_MODE_Pin) && HAL_GPIO_ReadPin(GPIOB, SIGN_RIGHT_OFFLINE_MODE_Pin) )
	{
		Offline_Mode->head_lights = ON;
		Offline_Mode->read_lights = ON;
	}
	else
	{
		Offline_Mode->head_lights = OFF;
		Offline_Mode->read_lights = OFF;
	}

}

void Can_Transmit_Auxiliary_Activity_Check(CAN_HandleTypeDef hcan, uint8_t* Activity_Check) //trimite mesaj la 50ms la dash
{

	static const CAN_TxHeaderTypeDef TxHeader = {AUXILIARY_ID, 0x00, CAN_RTR_DATA, CAN_ID_STD, 1, DISABLE };

	static uint32_t TxMailBox;

	HAL_CAN_AddTxMessage(&hcan, &TxHeader, Activity_Check, &TxMailBox);
}



