#include <Arduino.h>
#include <HomeAutoLight.h>
#include <avr/sleep.h>
#include <Time.h>

CCDSensor Sensor(Sensing_pin, Interrupt_pin);


//int time[5];
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
//가변저항 으로 할 걸

/**mode **/
#define Print_only_CCDSensor_Value 		0
#define Print_Data 						0


void setup() {
	Serial.begin(9600);  //Begin serial communcation
}

///
void loop() {


#if Print_only_CCDSensor_Value
	while(1)
	{
		Serial.println(Sensor.get_anal_light_val());
		Serial.println(Sensor.get_digit_light_val());
	}
#endif

#if(Print_Data  ==  1)
	Sensor.print_Value();
#endif


	Sensor.AutoLight_Power_Saving_Main();

	//Serial.println("Normal Mode ");

}

