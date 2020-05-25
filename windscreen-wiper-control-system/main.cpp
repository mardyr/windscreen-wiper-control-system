#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart0.h"
#include "timer2.h"
#include "GPIO.h"
#include "can_driv.h"
#include <util/delay.h>

void WDT_off();
int main(void)
{
	WDT_off();
	DDRB = 0;	// all pins inputs
	/*
	 *SET PB0 as 1 level of wiper gear
	 PB1 -2 level of wiper gear
	 PB2 - 3 level of wiper gear
	 PB3 - 4 level of wiper gear
	 */
	GPIO level1('B', 0);
	level1.SetOutput();
	GPIO level2('B', 1);
	level1.SetOutput();
	GPIO level3('B', 2);
	level1.SetOutput();
	GPIO level4('B', 3);
	level1.SetOutput();
	
	Uart0 serial0(115200);
	
	CAN t_CAN;
	uint8_t mob = 7;
	uint8_t mode = TX_DATA; // mode
	uint32_t ID_Low = 0x7F8; //
	uint32_t ID_High = 0x7FF;
	t_CAN.SetupMOb(mob, mode, ID_Low, ID_High);
	
	
	return 0;
}

void WDT_off()
{
	/* Write logical one to WDCE and WDE */
	WDTCR = (1 << WDCE) | (1 << WDE);
	/* Turn off WDT */
	WDTCR = 0x00; 
}