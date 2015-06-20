#ifndef HomeAutoLight_h
#define HomeAutoLight_h

#include "Arduino.h"

/** mode definition**/
#define Power_saving mode;
#define Print_only_CCDSensor_Value 		0
#define Print_Data 						0

/** Pin Definition **/
#define 	Sensing_pin  			0
#define 	check_sleep_pin 		12
#define 	Interrupt_pin			2
#define 	Interrupt_pin1			3
#define		led_out_pin1			4
#define		led_out_pin2			5
#define		led_out_pin3			6
#define		led_out_pin4			7


/**State Definition**/
#define 	DARK_STATE 		1
#define 	BRIGHT_STATE 	2

extern "C" {
	void wakeUpNow();
	int Get_Time_Data(int* time_data);


}

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
		LedOut();
		void flash(int delay_ms, int flash_time);


};


#endif
