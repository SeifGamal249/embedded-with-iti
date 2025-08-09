#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

#include "../MCAL/ADC/ADC_int.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/SPI/SPI_int.h"

int main(){
	u16 adc_value;
	u16 temperature;

	MSPI_vInit();
	MADC_vInit();

	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN4,DIO_OUTPUT);
	MDIO_vSetPinVal(DIO_PORTB,DIO_PIN4,DIO_LOW);

	while(1){
        adc_value = MADC_u16AnalogRead(CHANNEL_0);
        temperature = (adc_value * 5) / 10;
		MSPI_vTransmit(temperature);
		_delay_ms(600);

	}
	return 0;
}
