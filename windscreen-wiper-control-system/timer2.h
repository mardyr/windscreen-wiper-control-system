#pragma once
#include <avr/io.h>

extern "C" void TIMER2_OVF_vect(void) __attribute__((signal));

extern class CTimer2 t_Timer2;

class CTimer2 {
public:
	CTimer2(void);
	void get_timer(uint32_t &time);
private:

	friend void TIMER2_OVF_vect();
	uint32_t m_time;
};