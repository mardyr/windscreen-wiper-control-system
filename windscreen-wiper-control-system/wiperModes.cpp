
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart0.h"
#include "timer2.h"
#include "GPIO.h"
#include "can_driv.h"
#include <util/delay.h>
#include "Init.h"

 GPIO level1('B', 0);
 GPIO level2('B', 1);
 GPIO level3('B', 2);
 GPIO level4('B', 3);
 GPIO washMotor('B', 5);
 GPIO wiperMotor('B', 6);

void Mode1() // 0,125Hz
{				
	MOb.number = 1;
	MOb.length = 2;	
	MOb.data[0] = 0x11;  		// data to activate wiper
	MOb.data[1]	= 0x23;
	_delay_ms(8000);   			// wait for 8 sec
	if(counter > 3)	
	{
		washMotor.SetHigh();    // clean windscreen
		_delay_ms(500);
		counter = 0;
	}
	wiperMotor.SetHigh();
	counter++;
}
void Mode2()    // 0,5 Hz
{ 				
	MOb.number = 1;
	MOb.length = 2;	
	MOb.data[0] = 0x11;  		// data to activate wiper
	MOb.data[1]	= 0x23;
	_delay_ms(2000);    		// wait for 2 sec
	
	if(counter > 5)	
	{
		washMotor.SetHigh();     // clean windscreen
		_delay_ms(500);
		counter = 0;
	}
	wiperMotor.SetHigh();
	counter++;
}
void Mode3()  // 0,8Hz
{
	  					
	MOb.number = 1;
	MOb.length = 2;		
	MOb.data[0] = 0x11;  			// data to activate wiper
	MOb.data[1]	= 0x23;
	_delay_ms(1250);     			// wait 1,25 s

	if(counter > 8)	
	{
		washMotor.SetHigh();		// clean windscreen
		_delay_ms(500);
		counter = 0;
	}
	wiperMotor.SetHigh();
	counter++;
}
void Mode4()  // 2Hz
{
	   				
	MOb.number = 1;
	MOb.length = 2;	
	MOb.data[0] = 0x11;  		// data to activate wiper
	MOb.data[1]	= 0x23;
	_delay_ms(500);      		// wait for 0,5 sec
	if(counter > 10)	
	{
		washMotor.SetHigh();    // clean windscreen
		_delay_ms(500);
		counter = 0;
	}
	wiperMotor.SetHigh();
	counter++;
				
}
	
