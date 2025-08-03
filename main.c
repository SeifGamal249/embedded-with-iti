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

void MotorCw(void)
{
	MDIO_SetPinVal(MDIO_PORTA,0,MDIO_high);
	MDIO_SetPinVal(MDIO_PORTA,1,MDIO_low);
	//MTIMERS_vSetCompareMatch(TIM_0, 63);
}

void MotorCcw(void)
{
	MDIO_SetPinVal(MDIO_PORTA,1,MDIO_high);
	MDIO_SetPinVal(MDIO_PORTA,0,MDIO_low);
	//MTIMERS_vSetCompareMatch(TIM_0, 191);

}

void MotorStop(void)
{
	MDIO_SetPinVal(MDIO_PORTA,0,MDIO_low);
	MDIO_SetPinVal(MDIO_PORTA,1,MDIO_low);
	//MTIMERS_vSetCompareMatch(TIM_0, 63);
}

void MotorSequenceHandler(void)
{
	switch(motor_state)
	{
		case 0:  // CW
			MotorCw();
			MTIMERS_vSetInterval_CTC(MotorCw, 78125, 63);  // Set next timing
			motor_state++;
			break;

		case 1:  // CCW
			MotorCcw();
			MTIMERS_vSetInterval_CTC(MotorCcw, 15544, 191);
			motor_state++;
			break;

		case 2:  // Stop
			MotorStop();
			MTIMERS_vSetInterval_CTC(MotorStop, 78125, 63);
			motor_state = 0;  // Repeat cycle
			break;
	}
}



int main(){
	MGIE_vEnableInterrupt();
	MTIMERS_vInit();
	MTIMERS_vEnableInterrupt(TIM_0, CTC);

	MDIO_SetPinDir(MDIO_PORTA,0,MDIO_output);
	MDIO_SetPinVal(MDIO_PORTA,0,MDIO_low);
	MDIO_SetPinDir(MDIO_PORTA,1,MDIO_output);
	MDIO_SetPinVal(MDIO_PORTA,1,MDIO_low);

	MDIO_SetPinVal(MDIO_PORTB, 3, MDIO_high);

	MTIMERS_vSetInterval_CTC(MotorSequenceHandler,156250, 63);

	MTIMERS_vStartTimer(TIM_0);
	while(1)
	{

	}
	return 0;
}
