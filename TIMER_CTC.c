/*
 * main.c
 *
 *  Created on: Jul 22, 2025
 *      Author: seifg
 */
#include <avr/io.h>
#include <avr/delay.h>

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/timers/timers_init.h"
#include "../MCAL/timers/timer_cfg.h"
#include "../MCAL/timers/timers_prv.h"
#include "../MCAL/GIE/GIE_init.h"

u8 motor_state=0;
u16 counter=0;

void Motor(void)
{
	counter++;

	switch(motor_state)
	{
	case 0:
		if(counter == 1)
		{
			// Forward
			MDIO_SetPinVal(MDIO_PORTA,0,MDIO_high);
			MDIO_SetPinVal(MDIO_PORTA,1,MDIO_low);
		}
		if(counter == 19531)
		{
			motor_state = 1;
		}
		break;

	case 1:
		if(counter == 19532)
		{
			// Reverse
			MDIO_SetPinVal(MDIO_PORTA,0,MDIO_low);
			MDIO_SetPinVal(MDIO_PORTA,1,MDIO_high);
		}
		if(counter == (19531 + 11719))
		{
			motor_state = 2;
		}
		break;

	case 2:
		if(counter == (19531 + 11719 + 1))
		{
			// Stop
			MDIO_SetPinVal(MDIO_PORTA,0,MDIO_low);
			MDIO_SetPinVal(MDIO_PORTA,1,MDIO_low);
		}
		if(counter == (19531 + 11719 + 19531))
		{
			// Reset loop
			motor_state = 0;
			counter = 0;
		}
		break;
	}
}



int main(){
	MGIE_vEnableInterrupt();
	MTIMERS_vInit();
	MTIMERS_vEnableInterrupt(TIM_0, CTC);

	MDIO_SetPinDir(MDIO_PORTA,0,MDIO_output);
	MDIO_SetPinDir(MDIO_PORTA,1,MDIO_output);

	MTIMERS_vSetInterval_CTC(Motor,1, 256);

	MTIMERS_vStartTimer(TIM_0);
	while(1)
	{

	}
	return 0;
}
