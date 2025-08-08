#define F_CPU 	8000000UL
#include <util/delay.h>
#include <avr/io.h>

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/GIE/GIE_int.h"
//#include "../MCAL/I2C/I2C_interface.h"
//#include "../MCAL/I2C/I2C_config.h"
//
//#include "../MCAL/USART/USART_int.h"


//int main(void)
//{
//	MUSART_vInit();
//	I2C_voidInitMaster();
//
//	u8 data_to_send = 'E';
//	u8 received_data = 0;
//
//	// Write to EEPROM at address 0x01
//	if (I2C_I2C_stateSendStartCondition() != no_error) MUSART_vTransmit('S');
//	if (I2C_SendSlaveAdressWithWrite(0x51) != no_error) MUSART_vTransmit('A');
//	I2C_MasterWriteDataByte(0x01);           // EEPROM memory address
//	I2C_MasterWriteDataByte(data_to_send);   // Data
//	I2C_SendStopCondition();
//	_delay_ms(10); // EEPROM needs write time
//
//	// Read from EEPROM at address 0x01
//	I2C_I2C_stateSendStartCondition();
//	I2C_SendSlaveAdressWithWrite(0x51);
//	I2C_MasterWriteDataByte(0x01);
//	I2C_I2C_stateSendRepeatedStart();
//	I2C_SendSlaveAdressRead(0x51);
//	I2C_MasterReadDataByte(&received_data);
//	I2C_SendStopCondition();
//
//	// Send data over UART
//	MUSART_vTransmit(received_data);
//
//	while (1) {}
//}

//int main(){
//	MDIO_vSetPinDir(DIO_PORTD,DIO_PIN5,DIO_OUTPUT);
//	MTIMERS_vInit();
//	MTIMERS_vStartTimer(TIM_1);
//
//	for(int i=0;i<=180;i+=10){
//		MTIMERS_vSetCompareMatch(TIM_1_A, (1000+(1000*i)/180));
//		_delay_ms(1000);
//	}
//	for(int i=180;i>=0;i-=10){
//		MTIMERS_vSetCompareMatch(TIM_1_A, (1000+(1000*i)/180));
//		_delay_ms(1000);
//	}
//	while(1){
//
//	}
//}

void Toggle_Motor(void){
	MDIO_vTogPinVal(DIO_PORTA,DIO_PIN0);
}

int main(){
	//SWITCH ON INT0 PULLED HIGH
	MDIO_vSetPinDir(DIO_PORTD,DIO_PIN2,DIO_INPUT);
	MDIO_vSetPinVal(DIO_PORTD,DIO_PIN2,DIO_HIGH);
	//MOTOR PINS
	MDIO_vSetPinDir(DIO_PORTA,DIO_PIN0,DIO_OUTPUT);
	MDIO_vSetPinDir(DIO_PORTA,DIO_PIN1,DIO_OUTPUT);

	MEXTI_vInit();
	MGIE_vEnableGlobalInterrupt();
	MEXTI_vCallBackFunction(Toggle_Motor,0);


	while(1){

	}
	return 0;
}
