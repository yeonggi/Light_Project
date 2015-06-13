#include <Arduino.h>
#include <HomeAutoLight.h>
#include <avr/sleep.h>

#define Power_saving mode;

#define 	Sensing_pin  		0
#define 	check_sleep_pin 	12
#define 	Interrupt_pin		2
#define 	Interrupt_pin1		3
#define		led_out_pin			5




///fghfghfgh
CCDSensor Sensor(Sensing_pin, Interrupt_pin);
SleepMode Sleep(check_sleep_pin);
//fff
// auto light app
/*photo transistor */
//
// 6V ~ 7.2 V battery ,
//�sdfsdf��� 16�ð� ��� ( 565mAh / 35mA )
// have an
//analog signal level close to VCC/2.


void setup() {
	Serial.begin(9600);  //Begin serial communcation
	pinMode(led_out_pin,OUTPUT);
	//attachInterrupt(0, wakeUpNow, LOW);
}

///
void loop() {

	int state = 0;
	int i =0;
//asdaaaaaaa
	Sensor.print_Value();
	state = Sensor.check_state_go_sleep();

	Serial.println(state);
	//Sensor._before_sleep_state == BRIGHT_STATE &&
	if(state ==  BRIGHT_STATE )
	{
		for(i=0; i<5; i++)
		{
			digitalWrite(led_out_pin,HIGH);
			delay(500);
			digitalWrite(led_out_pin,LOW);
			delay(500);
		}
	}
////
	if(state ==  DARK_STATE )
	{
		Serial.println("Get Darked Turn on LED");
		digitalWrite(led_out_pin,HIGH);
		delay(5000);
		digitalWrite(led_out_pin,LOW);
	}

	if(state > 0)
		Sleep.sleepNow();


	//Serial.println("Normal Mode ");
	delay(10);
}

