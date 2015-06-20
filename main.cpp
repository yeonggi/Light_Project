#include <Arduino.h>
#include <HomeAutoLight.h>
#include <avr/sleep.h>
#include <Time.h>

CCDSensor Sensor(Sensing_pin, Interrupt_pin);
SleepMode Sleep(check_sleep_pin);
LedOut Led;

int time[5];
//fff
// auto light app
/*photo transistor */
//
// 6V ~ 7.2 V battery ,
//�sdfsdf��� 16�ð� ��� ( 565mAh / 35mA )
// have an
//analog signal level close to VCC/2.

/*pin config
 * A1, D0 ---- CCD beteen Register
 *
 *
 *
 *
 *
 */

void setup() {
	memset(time,0,sizeof(time));
	Serial.begin(9600);  //Begin serial communcation
	//Get_Time_Data(time);
	//setTime(time[3],time[4],0,time[2],time[1],time[0]);
	//attachInterrupt(0, wakeUpNow, LOW);
}

///
void loop() {

	int state = 0;
	int sleep_state =0;

#if(print_only_CCDSensor_value == 1)
	while(1)
	{
		Serial.println(Sensor.get_anal_light_val());
		Serial.println(Sensor.get_digit_light_val());
	}
#endif

#if(Print_Data  ==  1)
	Sensor.print_Value();
#endif

	state = Sensor.check_state_go_sleep();

	if(Sensor._before_sleep_state == 0 && state > 0)
	{
		//Serial.println(" =============== Before state is 0 =============== ");
		if(state == DARK_STATE)
			Sensor._before_sleep_state = BRIGHT_STATE;
		else
			Sensor._before_sleep_state = DARK_STATE;
	}

	if(state ==  BRIGHT_STATE && Sensor._before_sleep_state == DARK_STATE)
	{
		Sensor._before_sleep_state = BRIGHT_STATE;
		Led.flash(500,5);
	}

	if(state ==  DARK_STATE && Sensor._before_sleep_state == BRIGHT_STATE)
	{
		Sensor._before_sleep_state = DARK_STATE;
		//Serial.println("Get Darked Turn on LED");
		Led.flash(3000,2);
	}

#if 1
	if(state > 0)
	{
		while(1){
			sleep_state = Sensor.check_state_go_sleep();
			if(sleep_state>0)
				break;
		}
		if(sleep_state == state)
			Sleep.sleepNow();
		else
			Sensor._before_sleep_state = 0;

	}
#else
	if(state>0)
		Sleep.sleepNow();
#endif


	//Serial.println("Normal Mode ");
	delay(5);
}

