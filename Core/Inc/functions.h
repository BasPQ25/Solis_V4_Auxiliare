#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include "main.h"
#include "stm32f3xx_hal.h"
//#include "stm32f3xx_hal_can.h"

#define DASHBOARD_ID 0x701
#define AUXILIARY_ID 0x700
#define SAFE_STATE 0x00

#define AUXILIARY_WORKS 0xFF
#define AUXILIARY_ERROR 0x00

typedef union
{
    uint8_t state;
    struct
    {
        uint8_t sign_left : 1;
        uint8_t sign_right : 1;
        uint8_t fan : 1;
        uint8_t brake : 1;
        uint8_t horn : 1;
        uint8_t avarie : 1;
        uint8_t camera : 1;
        uint8_t faruri : 1;
    };
} aux_state;

typedef struct
{
    uint32_t Sign_Left_Current;
    uint32_t Sign_Right_Current;
    uint32_t Fan_Current;
    uint32_t Brake_Current;
    uint32_t Horn_Current;
    uint32_t Avarie_Current;
    uint32_t Camera_Current;
    uint32_t Faruri_Current;
} Aux_Error;

typedef enum
{
    OFF = 0,
    ON
} bool;

void Update_Aux_State(aux_state* auxiliary, bool Toggle_State_Right, bool Toggle_State_Left, uint8_t Sign_Left_500ms_Timer, uint8_t Sign_Right_500ms_Timer);

void Update_Buttons_State_Offline_Mode(aux_state* Offline_Mode);

void Can_Transmit_Auxiliary_Activity_Check(CAN_HandleTypeDef hcan, uint8_t* Activity_Check);

void Get_Adc_Value(ADC_HandleTypeDef hadc4, aux_state* auxiliary, bool Toggle_State_Right, bool Toggle_State_Left, uint32_t adc_value, uint8_t* Activity_Check);

#endif /* INC_FUNCTIONS_H_ */

