#include <Arduino.h>
#include <HomeAutoLight.h>
#include <avr/sleep.h>
#include <Time.h>

#define Power_saving mode;

#define 	Sensing_pin  		0
#define 	check_sleep_pin 	12
#define 	Interrupt_pin		2
#define 	Interrupt_pin1		3
#define		led_out_pin			5

enum date_string {YY, MM, DD, TT, mm};
char date_buffer[10];
char input_recog_flag;


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

	int input =0;
	int i=0;
	int data_input=0;

    Serial.println(" put date YY-MM-DD-TT-mm: ");
    while(1)
    {
    	if(Serial.available())
    	{
    		//Serial.print(Serial.read());
    		date_buffer[input] = Serial.read() - '0';
    		input++;
    		if(Serial.read() == '\r')
    			Serial.print(date_buffer);
    	}
    	if(input == 10 )
    	{
    		for(i=0; i<5; i++)
    		{
    			data_input = (date_buffer[i] << 8) | date_buffer[i+1];
    			Serial.println(data_input);
    			//if(data_input >0 && data_input)
    		}
    	}

    }

	//attachInterrupt(0, wakeUpNow, LOW);
}

///
void loop() {

	int state = 0;
	int sleep_state =0;
	int i =0;

	Sensor.print_Value();
	state = Sensor.check_state_go_sleep();

	Serial.println(state);
	//Sensor._before_sleep_state == BRIGHT_STATE &&
	if(Sensor._before_sleep_state == 0 && state>0)
	{
		if(state == DARK_STATE)
			Sensor._before_sleep_state = BRIGHT_STATE;
		else
			Sensor._before_sleep_state = DARK_STATE;
	}

	if(state ==  BRIGHT_STATE && Sensor._before_sleep_state == DARK_STATE)
	{
		Sensor._before_sleep_state = BRIGHT_STATE;
		for(i=0; i<5; i++)
		{
			digitalWrite(led_out_pin,HIGH);
			delay(500);
			digitalWrite(led_out_pin,LOW);
			delay(500);
		}
	}

	if(state ==  DARK_STATE && Sensor._before_sleep_state == BRIGHT_STATE)
	{
		Sensor._before_sleep_state = DARK_STATE;
		Serial.println("Get Darked Turn on LED");
		digitalWrite(led_out_pin,HIGH);
		delay(5000);
		digitalWrite(led_out_pin,LOW);
	}

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


	//Serial.println("Normal Mode ");
	delay(5);
}

