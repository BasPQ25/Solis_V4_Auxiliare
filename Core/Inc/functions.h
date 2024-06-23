

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include "main.h"
#include "stm32f3xx_hal.h"
//#include "stm32f3xx_hal_can.h"


void Update_Aux_State(void);
void Update_Buttons_State_Offline_Mode(void);
void Can_Transmit_Auxiliary_Activity_Check(void);

#define DASHBOARD_ID 0x333
#define SAFE_STATE 0xFF

typedef union
{
	uint8_t state;
	struct
	{
		uint8_t horn : 1;
		uint8_t sign_left : 1;
		uint8_t sign_right : 1;
		uint8_t avarie : 1;
		uint8_t camera : 1;
		uint8_t faruri : 1;
		uint8_t brake : 1;
		uint8_t fan : 1;
	};
}aux_state;

typedef enum
{
	OFF = 0,
	ON
}bool;

#endif /* INC_FUNCTIONS_H_ */
