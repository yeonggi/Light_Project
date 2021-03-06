#include <Arduino.h>
#include <HomeAutoLight.h>
#include <avr/sleep.h>




HALS light_app;
CCDSensor Sensor(Sensing_pin, Interrupt_pin);

#define Print_only_CCDSensor_Value 		0
#define Print_Data 						0

/////
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


#if(Transe_mode == 1)
	light_app.Autolight_Sender();
#else
	light_app.Autolight_Body();

	//Serial.printf("hello");

#endif

}

