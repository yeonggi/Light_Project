#ifndef HomeAutoLight_h
#define HomeAutoLight_h

#include "Arduino.h"

#define 	DARK_STATE 		1
#define 	BRIGHT_STATE 	2

class CCDSensor //: public SleepMode
{
	public:
		CCDSensor(int sensing_pin, int interrupt_pin);
		int get_anal_light_val();
		int get_digit_light_val();
		void print_Value();
		int check_state_go_sleep();

		int _light_val;
		int _digit_val;
		int _before_sleep_state;

		int Bright_State;
		int Dark_State;

	private:
		int _interrupt_pin;
		int _sensing_pin;
};

class SleepMode
{
	public:
		SleepMode(int led_pin);
		void sleepNow();
		int _sleep_status = 0;
	private:
		int _led_pin; //for check sleep mode

};

class LedOut
{
	public:
		LedOut(int led_pin);
		void flash();

};


#endif
