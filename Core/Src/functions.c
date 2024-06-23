
#include "functions.h"

aux_state aux = {0x00};
aux_state* auxiliary = &aux;

aux_state Offline = {0x00};
aux_state* Offline_Mode = &Offline;

extern CAN_HandleTypeDef hcan;

void Update_Aux_State()
{
		static uint8_t Sign_Left_500ms_Timer = 0; // numaram pana la 10 ca sa avem 500ms intre toggle, STANDARD SEMNALIZARI
		static uint8_t Sign_Right_500ms_Timer = 0;

		static bool Toggle_State_Right = OFF;
		static bool Toggle_State_Left = OFF;

		//avarie
		if(auxiliary->avarie == ON && Toggle_State_Left == Toggle_State_Right )
			{
				Sign_Right_500ms_Timer = Sign_Left_500ms_Timer; //sincronizare semnalizari
				auxiliary->sign_left = auxiliary->sign_right = ON;
			}

		//semnalizare stanga
		if(auxiliary->sign_left == ON)
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
				HAL_GPIO_WritePin(GPIOB, SIGN_LEFT_Pin, OFF);
				Sign_Left_500ms_Timer = 0;
				Toggle_State_Left = OFF;
			}

		//semanlizare dreapta
		if(auxiliary->sign_right == ON)
		{
			if(++Sign_Right_500ms_Timer == 10)
			{
				HAL_GPIO_TogglePin(GPIOB, SIGN_RIGHT_Pin);
				Sign_Right_500ms_Timer = 0;
				Toggle_State_Right = !Toggle_State_Right;
			}
		}
		else
			{
				HAL_GPIO_WritePin(GPIOB, SIGN_RIGHT_Pin, auxiliary->sign_right);
				Sign_Left_500ms_Timer = 0;
				Toggle_State_Right = OFF;
			}



		HAL_GPIO_WritePin(GPIOB, HORN_Pin, auxiliary->horn);
		HAL_GPIO_WritePin(GPIOB, CAMERA_Pin, auxiliary->camera);
		HAL_GPIO_WritePin(GPIOB, BACK_LIGHT_Pin | FRONT_LIGHT_Pin, auxiliary->faruri);
		HAL_GPIO_WritePin(GPIOB, BRAKE_Pin, auxiliary->brake);
		HAL_GPIO_WritePin(GPIOA, FAN_Pin, auxiliary->fan);

}
void Update_Buttons_State_Offline_Mode()
{
	Offline_Mode->brake = HAL_GPIO_ReadPin(GPIOA, BRAKE_OFFLINE_MODE_Pin);
	Offline_Mode->camera = HAL_GPIO_ReadPin(GPIOB, CAMERA_OFFLINE_MODE_Pin);
	Offline_Mode->fan = HAL_GPIO_ReadPin(GPIOB, FAN_OFFLINE_MODE_Pin);
	Offline_Mode->horn = HAL_GPIO_ReadPin(GPIOB, HORN_OFFLINE_MODE_Pin);
	Offline_Mode->sign_left = HAL_GPIO_ReadPin(GPIOB, SIGN_LEFT_OFFLINE_MODE_Pin);
	Offline_Mode->sign_right = HAL_GPIO_ReadPin(GPIOB, SIGN_RIGHT_OFFLINE_MODE_Pin);

	//avarie
	if( HAL_GPIO_ReadPin(GPIOB, SIGN_LEFT_OFFLINE_MODE_Pin) && HAL_GPIO_ReadPin(GPIOB, SIGN_RIGHT_OFFLINE_MODE_Pin) )
	{
		Offline_Mode->avarie = ON;
	}
	else Offline_Mode->avarie = OFF;

	//faruri fata si spate
	if( HAL_GPIO_ReadPin(GPIOB, FRONT_LIGHT_OFFLINE_MODE_Pin) || HAL_GPIO_ReadPin(GPIOB, BACK_LIGHT_OFFLINE_MODE_Pin) )
	{
		Offline_Mode->faruri = ON;
	}
	else Offline_Mode->faruri = OFF;
}
void Can_Transmit_Auxiliary_Activity_Check() //trimite mesaj la 50ms la dash
{

	static const CAN_TxHeaderTypeDef TxHeader = {0x103, 0x00, CAN_RTR_DATA, CAN_ID_STD, 1, DISABLE };
	static const uint8_t Activity_Check[1] = {0xFF};
	static uint32_t TxMailBox;

	HAL_CAN_AddTxMessage(&hcan, &TxHeader, Activity_Check, &TxMailBox);
}

