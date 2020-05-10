#include <avr/io.h>
#include "can_driv.h"
//==========================================================================================
bool CAN::SetupMOb(uint8_t&mob, uint8_t& mode, uint32_t &CAN_ID_Low, uint32_t   &CAN_ID_High)
{
	uint8_t temp_canpage;
	uint32_t maskId, canId;

	//verify that MOb is free
	if(mob > MAX_MOB) {
		return false;
	}
	temp_canpage = CANPAGE;

	//select MOb
	SET_CANPAGE(mob);

	//enable interrupt for MOb
	MOB_IRQ_ENABLE(mob);

	//calculate and set mask
	maskId = ~(CAN_ID_High - CAN_ID_Low);
	SET_EXTENDED_MASK(maskId);

	//calculate and set CAN ID
	canId = (maskId & CAN_ID_Low);
	SET_EXTENDED_ID(canId);

	//enable interrupt of MOb
	MOB_IRQ_ENABLE(mob);

	switch (mode)
	{
	case DISABLED:
		MOb_DISABLE;
		break;

	case TX_DATA:
		MOb_ENABLE_TX;
		break;

	case RX_DATA:
		MOb_ENABLE_RX;
		break;

	default:
		return false;
	}

	CANPAGE = temp_canpage;

	return true;
}
//==========================================================================================
bool CAN::set_canspeed(uint8_t& canspeed)
{
#if F_CPU	== 16000000
	switch (canspeed) {
	case CAN_BAUDRATE_1000K:
		CANBT1		= 0x00;
		CANBT2		= 0x0C;
		CANBT3		= 0x37;

		break;

	case CAN_BAUDRATE_500K:
		CANBT1		= 0x02;
		CANBT2		= 0x0C;
		CANBT3		= 0x37;

		break;

	case CAN_BAUDRATE_250K:
		CANBT1		= 0x06;
		CANBT2		= 0x0C;
		CANBT3		= 0x37;

		break;

	case CAN_BAUDRATE_200K:
		CANBT1		= 0x08;
		CANBT2		= 0x0C;
		CANBT3		= 0x37;

		break;

	case CAN_BAUDRATE_125K:
		CANBT1		= 0x0E;
		CANBT2		= 0x0C;
		CANBT3		= 0x37;

		break;

	case CAN_BAUDRATE_100K:
		CANBT1		= 0x12;
		CANBT2		= 0x0C;
		CANBT3		= 0x37;

		break;

	case CAN_BAUDRATE_50K:
		CANBT1		= 0x0E;
		CANBT2		= 0x0C;
		CANBT3		= 0x4C;

		break;

	default:

		break;
	}
#elif F_CPU	== 12000000
	switch (canspeed) {
	case CAN_BAUDRATE_1000K:
		CANBT1		= 0x00;
		CANBT2		= 0x08;
		CANBT3		= 0x25;

		break;

	case CAN_BAUDRATE_500K:
		CANBT1		= 0x02;
		CANBT2		= 0x08;
		CANBT3		= 0x25;

		break;

	case CAN_BAUDRATE_250K:
		CANBT1		= 0x04;
		CANBT2		= 0x0c;
		CANBT3		= 0x37;

		break;

	case CAN_BAUDRATE_200K:
		CANBT1		= 0x04;
		CANBT2		= 0x0E;
		CANBT3		= 0x4B;

		break;

	case CAN_BAUDRATE_125K:
		CANBT1		= 0x0A;
		CANBT2		= 0x0C;
		CANBT3		= 0x37;

		break;

	case CAN_BAUDRATE_100K:
		CANBT1		= 0x0A;
		CANBT2		= 0x0E;
		CANBT3		= 0x4B;

		break;

	default:

		break;
	}
#elif F_CPU	==  8000000
	switch (canspeed) {
	case CAN_BAUDRATE_1000K:
		CANBT1		= 0x00;
		CANBT2		= 0x04;
		CANBT3		= 0x13;

		break;

	case CAN_BAUDRATE_500K:
		CANBT1		= 0x00;
		CANBT2		= 0x0C;
		CANBT3		= 0x37;

		break;

	case CAN_BAUDRATE_250K:
		CANBT1		= 0x02;
		CANBT2		= 0x0c;
		CANBT3		= 0x37;

		break;

	case CAN_BAUDRATE_200K:
		CANBT1		= 0x02;
		CANBT2		= 0x0E;
		CANBT3		= 0x4B;

		break;

	case CAN_BAUDRATE_125K:
		CANBT1		= 0x06;
		CANBT2		= 0x0C;
		CANBT3		= 0x37;

		break;

	case CAN_BAUDRATE_100K:
		CANBT1		= 0x08;
		CANBT2		= 0x0C;
		CANBT3		= 0x37;

		break;

	default:
		break;
	}
#elif F_CPU	==  6000000
	switch (canspeed) {
	case CAN_BAUDRATE_1000K:
		break;

	case CAN_BAUDRATE_500K:
		CANBT1		= 0x00;
		CANBT2		= 0x08;
		CANBT3		= 0x25;

		break;

	case CAN_BAUDRATE_250K:
		CANBT1		= 0x02;
		CANBT2		= 0x08;
		CANBT3		= 0x25;

		break;

	case CAN_BAUDRATE_200K:
		CANBT1		= 0x02;
		CANBT2		= 0x0c;
		CANBT3		= 0x35;

		break;

	case CAN_BAUDRATE_125K:
		CANBT1		= 0x04;
		CANBT2		= 0x0C;
		CANBT3		= 0x37;

		break;

	case CAN_BAUDRATE_100K:
		CANBT1		= 0x04;
		CANBT2		= 0x0E;
		CANBT3		= 0x4B;

		break;

	default:
		break;
	}
#elif F_CPU	==  4000000
	switch (canspeed) {
	case CAN_BAUDRATE_1000K:
		break;

	case CAN_BAUDRATE_500K:
		CANBT1		= 0x00;
		CANBT2		= 0x04;
		CANBT3		= 0x13;

		break;

	case CAN_BAUDRATE_250K:
		CANBT1		= 0x02;
		CANBT2		= 0x04;
		CANBT3		= 0x13;

		break;

	case CAN_BAUDRATE_200K:
		CANBT1		= 0x00;
		CANBT2		= 0x0E;
		CANBT3		= 0x4B;

		break;

	case CAN_BAUDRATE_125K:
		CANBT1		= 0x02;
		CANBT2		= 0x0C;
		CANBT3		= 0x37;

		break;

	case CAN_BAUDRATE_100K:
		CANBT1		= 0x02;
		CANBT2		= 0x0E;
		CANBT3		= 0x4B;

		break;

	default:
		break;
	}
#else
#warning F_CPU has no correct frequency for canspeed settings
	return false;
#endif

}