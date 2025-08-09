/*
 * main.c
 *
 *  Created on: Aug 9, 2025
 *      Author: seifg
 */
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/SPI/SPI_int.h"
#include "../MCAL/USART/USART_int.h"

int main(){
	MSPI_vInit();
	MUSART_vInit();

	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN4,DIO_INPUT);

	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN0,DIO_OUTPUT);
	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN1,DIO_OUTPUT);

	MDIO_vSetPinVal(DIO_PORTB,DIO_PIN0,DIO_LOW);
	MDIO_vSetPinVal(DIO_PORTB,DIO_PIN1,DIO_LOW);

	u16 recieved_val;
	while(1){
		recieved_val=MSPI_u8Receive();
		//MUSART_vTransmit(recieved_val);

		if(recieved_val>26){
			MDIO_vSetPinVal(DIO_PORTB,DIO_PIN0,DIO_HIGH);
		}
		else{
			MDIO_vSetPinVal(DIO_PORTB,DIO_PIN0,DIO_LOW);
		}

	}
	return 0;
}

