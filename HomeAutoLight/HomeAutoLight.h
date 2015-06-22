#ifndef HomeAutoLight_h
#define HomeAutoLight_h

#include "Arduino.h"

// about operation
#define power_saving_mode

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

class SleepMode
{
	public:
		SleepMode();
		void sleepNow();
		int _sleep_status;
	private:
		int _led_pin; //for check sleep mode

};

class LedOut
{
	public:
		LedOut();
		void flash(int delay_ms, int flash_time);


};

class CCDSensor
{
	//embedded object
	SleepMode sleepObj;
	LedOut	  LedObj;

	public:
		CCDSensor(int sensing_pin, int interrupt_pin);
		int get_anal_light_val();
		int get_digit_light_val();
		void print_Value();
		int check_state_go_sleep();
		void AutoLight_Power_Saving_Main();
		void AutoLight_Nomal_Main();


		int _light_val;
		int _digit_val;
		int _before_sleep_state;

		int Bright_State;
		int Dark_State;

	private:
		int _interrupt_pin;
		int _sensing_pin;
};



#endif
