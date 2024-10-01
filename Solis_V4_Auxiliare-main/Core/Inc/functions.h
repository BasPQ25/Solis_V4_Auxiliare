#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include "main.h"
#include "stm32f3xx_hal.h"
//#include "stm32f3xx_hal_can.h"

#define DASHBOARD_ID 0x701
#define AUXILIARY_ID 0x100
#define SAFE_STATE 0xFF

typedef union
{
    uint8_t state;
    struct
    {
        uint8_t sign_left : 1;
        uint8_t sign_right : 1;
        uint8_t safe_state : 1;
        uint8_t brake : 1;
        uint8_t horn : 1;
        uint8_t read_lights : 1;
        uint8_t camera : 1;
        uint8_t head_lights : 1;
    };
} aux_state;

typedef enum
{
    OFF = 0,
    ON
} bool;

void Update_Aux_State(aux_state* auxiliary);

void Update_Buttons_State_Offline_Mode(aux_state* Offline_Mode);

#endif /* INC_FUNCTIONS_H_ */

