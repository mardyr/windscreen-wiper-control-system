#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart0.h"
#include "timer2.h"
#include "GPIO.h"
#include "can_driv.h"
#include <util/delay.h>
#include "Init.h"

CAN t_CAN;     // transmitter
Uart0 serial0(115200);
MOb_struct MOb;
void SetupADC()
{
	ADMUX = (1 << REFS1) | (1 << REFS0) | (1<< MUX0);  // set internal voltage reference and ADC1 as input channel
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // enable conversion , enable interrupt, set prescaler
	DIDR0 = (1 << ADC7D); // digital input disable
}

void startConversion()
{
	ADCSRA = (1 << ADSC);
}

ISR(ADC_vect)
{
	// sensor data
	
	uint8_t tmob = 3;
	uint8_t tmode = TX_DATA;  // mode
	uint32_t tID_Low = 0x7F6;  // mask to achieve 3 different state
	uint32_t tID_High = 0x7F8; // 
	t_CAN.SetupMOb(tmob, tmode, tID_Low, tID_High);   // setup transmitter
	cli();
	// INFORMATION ABOUT RAIN SENSOR FROM AN-CM-219 IR Windshield Rain Sensor
	if(ADC < 800) // sensor have 2V nominal voltage, which decrease with water contact
	{
		
		uint16_t id = 0x11111111111; // the lowest priority from wiper control 
		MOb.id = id;
		Mode1();
		serial0.write(id);       			// send ID
		serial0.read(id);    				// receive by wiper node
		
	}
	else if (ADC < 400) // 75% Light reflection
	{
		uint16_t id = 0x11111111110; // only bigger than autocontrol 
		MOb.id = id;
		Mode2();
		serial0.write(id);       			// send ID
		serial0.read(id);    				// receive by wiper node
	}
	else if (ADC < 280) // 50 % Light reflection
	{
		uint16_t id = 0x11111111101;  // most important from autocontrol system , the biggest rain
		MOb.id = id;
		Mode3();
		serial0.write(id);       			// send ID
		serial0.read(id);    				// receive by wiper node
	}
	
	sei();
}