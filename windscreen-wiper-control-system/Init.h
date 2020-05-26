#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart0.h"
#include "timer2.h"
#include "GPIO.h"
#include "can_driv.h"
#include <util/delay.h>

void Mode1();
void Mode2();
void Mode3();
void Mode4();
static unsigned int counter = 0;  // count to activate washMotor, using with wiperMode fcn
extern Uart0 serial0;
extern uint16_t id;
extern MOb_struct MOb;
extern GPIO level1;
extern GPIO level2;
extern GPIO level3;
extern GPIO level4;
extern GPIO washMotor;
extern GPIO wiperMotor;
