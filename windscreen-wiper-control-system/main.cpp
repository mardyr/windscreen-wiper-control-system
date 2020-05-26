
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart0.h"
#include "timer2.h"
#include "GPIO.h"
#include "can_driv.h"
#include <util/delay.h>
#include "Init.h"
void WDT_off();
 
int main()
{
	
	WDT_off();
	DDRB = 0;	// all pins inputs
	/*
	 *SET PB0 as 1 level of wiper gear
	 PB1 -2 level of wiper gear
	 PB2 - 3 level of wiper gear
	 PB3 - 4 level of wiper gear
	 */

	
	level1.SetInput();
	level2.SetInput();
	level3.SetInput();
	level4.SetInput();
	washMotor.SetOutput();
	wiperMotor.SetOutput();
	
	Uart0 serial0(115200);   // set baudrate
	
	CAN t_CAN;    // transmitter
	CAN r_CAN;     //receive
	
	uint8_t tmob = 4;
	uint8_t tmode = TX_DATA; // mode
	uint32_t tID_Low = 0x7F2; // mask to achieve 4 different state
	uint32_t tID_High = 0x7F5;// 
	
	uint8_t  rmob = 4;
	uint8_t	 rmode = RX_DATA;  // mode
	uint32_t rID_Low = 0x0F0;  // mask to achieve 4 different state
	uint32_t rID_High = 0x0F4; //
	CTimer2 rtc();
	t_CAN.SetupMOb(tmob, tmode, tID_Low, tID_High);  // setup transmitter
	r_CAN.SetupMOb(rmob, rmode, rID_Low, rID_High);
	while (1)
	{
		if (!(PINB&(1 << PB0)))		// mode 1 - on
			{
				uint16_t id = 0x11111111011;
				MOb.id = id;
				Mode1();
				serial0.write(id);      			// send ID
				serial0.read(id);   				// receive by wiper node
			}
		if (!(PINB&(1 << PB1)))			// mode 2 - on
			{
				uint16_t id = 0x11111111010;
				MOb.id = id;
				Mode2();
				serial0.write(id);       			// send ID
				serial0.read(id);    				// receive by wiper node
				
			}
		if (!(PINB&(1 << PB2)))			// mode 3 - on
			{
				uint16_t id = 0x11111111001;
				MOb.id = id;
				Mode3();
				serial0.write(id);       			// send ID
				serial0.read(id);    				// receive by wiper node
				
			}
		if (!(PINB&(1 << PB3)))			// mode 4- on
			{
				uint16_t id = 0x11111111000;
				MOb.id = id;
				Mode4();
				serial0.write(id);       			// send ID
				serial0.read(id);    				// receive by wiper node
			}
	}
	return 0;
}

void WDT_off()
{
	/* Write logical one to WDCE and WDE */
	WDTCR = (1 << WDCE) | (1 << WDE);
	/* Turn off WDT */
	WDTCR = 0x00; 
}
