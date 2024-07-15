
#include "functions.h"


void Update_Aux_State( aux_state* auxiliary ,
					   bool Toggle_State_Right , bool Toggle_State_Left,
					   uint8_t Sign_Left_500ms_Timer, uint8_t Sign_Right_500ms_Timer )
{
	//iesire sunt negate - Tranzistori tip P
		//avarie
		if( auxiliary->avarie == ON && Toggle_State_Left == Toggle_State_Right )
			{
				Sign_Right_500ms_Timer = Sign_Left_500ms_Timer; //sincronizare semnalizari
				auxiliary->sign_left = ON;
				auxiliary->sign_right = ON;
			}

		//semnalizare stanga
		if( auxiliary->sign_left == ON)
		{
			if(++Sign_Left_500ms_Timer == 10)
			{
				HAL_GPIO_TogglePin(GPIOB, SIGN_LEFT_Pin);
				Toggle_State_Left = (!Toggle_State_Left);
				Sign_Left_500ms_Timer = 0;
			}
		}
		else
			{
				//oprire semnalizare
				HAL_GPIO_WritePin(GPIOB, SIGN_LEFT_Pin, !(auxiliary->sign_left) );
				Sign_Left_500ms_Timer = 0;
				Toggle_State_Left = OFF;
			}

		//semanlizare dreapta
		if( auxiliary->sign_right == ON)
		{
			if(++Sign_Right_500ms_Timer == 10)
			{
				HAL_GPIO_TogglePin(GPIOB, SIGN_RIGHT_Pin);
				Sign_Right_500ms_Timer = 0;
				Toggle_State_Right = (!Toggle_State_Right);
			}
		}
		else
			{
				//oprire semnalizare
				HAL_GPIO_WritePin(GPIOB, SIGN_RIGHT_Pin, !(auxiliary->sign_right) );
				Sign_Left_500ms_Timer = 0;
				Toggle_State_Right = OFF;
			}



		HAL_GPIO_WritePin(GPIOB, HORN_Pin, (!auxiliary->horn) );
		HAL_GPIO_WritePin(GPIOB, CAMERA_Pin, (!auxiliary->camera) );
		HAL_GPIO_WritePin(GPIOB, BACK_LIGHT_Pin | FRONT_LIGHT_Pin, (!auxiliary->faruri) );
		HAL_GPIO_WritePin(GPIOB, BRAKE_Pin, (!auxiliary->brake) );
		HAL_GPIO_WritePin(GPIOA, FAN_Pin, (!auxiliary->fan) );



}

void Update_Buttons_State_Offline_Mode(aux_state* Offline_Mode)
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

void Can_Transmit_Auxiliary_Activity_Check(CAN_HandleTypeDef hcan, uint8_t* Activity_Check) //trimite mesaj la 50ms la dash
{

	static const CAN_TxHeaderTypeDef TxHeader = {AUXILIARY_ID, 0x00, CAN_RTR_DATA, CAN_ID_STD, 1, DISABLE };

	static uint32_t TxMailBox;

	HAL_CAN_AddTxMessage(&hcan, &TxHeader, Activity_Check, &TxMailBox);
}

void Get_Adc_Value( ADC_HandleTypeDef hadc4 , aux_state* auxiliary,
					bool Toggle_State_Right , bool Toggle_State_Left,
					uint32_t adc_value, uint8_t* Activity_Check)
{

	static Aux_Error Auxiliary_Error_Mapping = { .Sign_Right_Current = 0,
												 .Sign_Left_Current = 0,
												 .Avarie_Current = 0,
												 .Horn_Current = 0 ,
												 .Faruri_Current = 0,
												 .Fan_Current = 0,
												 .Camera_Current = 0,
												 .Brake_Current = 0,
											    };

	static Aux_Error* Aux_Map  = &Auxiliary_Error_Mapping;
	static uint8_t Tolerance = 100; // units

	uint8_t Error_Mask = 0x01;
	uint32_t Total_current = 0;



      if(    (auxiliary->sign_left == ON && Toggle_State_Left == ON )
    	  || (auxiliary->sign_right == ON && Toggle_State_Right == ON)
		  || (auxiliary->avarie == ON && Toggle_State_Left == ON && Toggle_State_Right == ON)
		  || (auxiliary->sign_left == OFF && auxiliary->sign_right == OFF && auxiliary->avarie == OFF) )

      {
    	  //ADC conversion Sequence
    	  	  HAL_ADC_Start(&hadc4);
    	  	  HAL_ADC_PollForConversion(&hadc4, HAL_MAX_DELAY);
    	  	  adc_value = HAL_ADC_GetValue(&hadc4);
    	  	  HAL_ADC_Stop(&hadc4);

    	  //Sum everything that is ON
    	  	  for(int i = 0; i < 8 ; i++)
    	  	  {
    	  		  Total_current += ( auxiliary->state && Error_Mask ) * *( (uint32_t*)Aux_Map + i);
    	  		  Error_Mask = Error_Mask << 1;
    	  	  }

    	  	//in 0 ai valoarea 2035 - 1.64V = 0 A.
    	  	//se aduna cu 328 - 1A
    	  	  	  if(Total_current - Tolerance <= adc_value && adc_value <= Total_current + Tolerance)
    	  	  	  {
    	  	  		  Activity_Check[0] =  AUXILIARY_WORKS;
    	  	  	  }
    	  	  	  else Activity_Check[0] = AUXILIARY_ERROR;

      }

}


