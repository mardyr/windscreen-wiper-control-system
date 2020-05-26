#include <avr/io.h>
#include <avr/interrupt.h>
#include "fifo.h"
#include "uart0.h"
#include "can_driv.h"
static CBuffer<uint16_t, 20> TxBuffer;
static CBuffer<uint16_t, 20> RxBuffer;

bool Uart0::read(uint16_t &c)
{
	if (RxBuffer.isEmpty()) {
		return false;
	}
	else {
		RxBuffer.Get(c);
	}
	return true;
}

bool Uart0::write(uint16_t &c)
{
	if (!TxBuffer.isFull()) {
		TxBuffer.Put(c);

		UCSR0B |= (1 << UDRIE0);

	}
	else {
		return false;
	}
	return true;
}


ISR(USART0_UDRE_vect)
{
	cli();
	uint16_t c;
	if (!TxBuffer.isEmpty()) {
		TxBuffer.Get(c);
		UDR0 = c;
	}
	else {
		UCSR0B &= ~(1 << UDRIE);
	}
	sei();
}

ISR(USART0_RX_vect)
{
	cli();
	uint16_t data = UDR0;
	RxBuffer.Put(data);
	sei();
}