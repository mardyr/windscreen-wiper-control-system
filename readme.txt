//-------------------------------------------
// Author : Marcin Dyrdół
//-------------------------------------------
// Version of windscreen wiper control system implemented in AT90CAN32 using Visual Studio with VisualGDB.

Assumes 4 level of manual steering with different frequencies:
- 0,125 Hz
- 0,5 Hz
- 0,8 Hz
- 2 Hz
Automatic steering is performed by Rain Sensor, which change voltage of relfected wavelength
3 level of automatic steering depends on voltage
- 0,125 Hz 1 V <= U < 2 V
- 0,5 Hz 0,7 V <=U < 1 V
- 0,8 Hz  U < 0,7 V

Using CAN interface manual steering force work on windscreen wiper 
( wins arbitration)
