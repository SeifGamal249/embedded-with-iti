#include <util/delay.h>
#include <avr/io.h>

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO/DIO_int.h"

#include "../MCAL/I2C/I2C_interface.h"
#include "../MCAL/I2C/I2C_config.h"

#include "../MCAL/USART/USART_int.h"

#include <util/delay.h>
#include <avr/io.h>

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/I2C/I2C_interface.h"
#include "../MCAL/USART/USART_int.h"

int main(void)
{
	MUSART_vInit();
	I2C_voidInitMaster();

	u8 data_to_send = 'E';
	u8 received_data = 0;

	// Write to EEPROM at address 0x01
	if (I2C_I2C_stateSendStartCondition() != no_error) MUSART_vTransmit('S');
	if (I2C_SendSlaveAdressWithWrite(0x51) != no_error) MUSART_vTransmit('A');
	I2C_MasterWriteDataByte(0x01);           // EEPROM memory address
	I2C_MasterWriteDataByte(data_to_send);   // Data
	I2C_SendStopCondition();
	_delay_ms(10); // EEPROM needs write time

	// Read from EEPROM at address 0x01
	I2C_I2C_stateSendStartCondition();
	I2C_SendSlaveAdressWithWrite(0x51);
	I2C_MasterWriteDataByte(0x01);
	I2C_I2C_stateSendRepeatedStart();
	I2C_SendSlaveAdressRead(0x51);
	I2C_MasterReadDataByte(&received_data);
	I2C_SendStopCondition();

	// Send data over UART
	MUSART_vTransmit(received_data);

	while (1) {}
}

