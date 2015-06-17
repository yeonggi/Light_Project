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
int date_buffer[11];
char input_recog_flag;
char max_value[] = {99, 12, 32, 24, 60};

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

	int input;
	int i=0;
	int data_input=0;
	int ch=0;
  	restart :

	input = 0;
  	memset(date_buffer,0,sizeof(date_buffer));
  	Serial.println(" put date YY-MM-DD-TT-mm (No line ending mdoe): ");

  	while(1)
  	{
  		if(Serial.available())
  		{
  			// ascii 48 -> 0
  			date_buffer[input] = Serial.read() - (int)48;
  			ch = Serial.read();
  			Serial.print(date_buffer[input]);
  			if(input%2 == 0 && input > 0)
  				Serial.print("-");

  			input++;
  			//\r == 13 \n == 10
  			//only behind code work
  			if(date_buffer[input-1] == -35 || date_buffer[input-1] == -38 || input == 10)
  			{
  				Serial.println();
  				for(i=0; i<10; i=i+2)
  				{
  					data_input = (date_buffer[i]*10) + date_buffer[i+1];
  					if(data_input > 0 && data_input <= max_value[(int)(i/2)])
  					{
  						Serial.print("---");
  						Serial.print(data_input);
  					}
  					else
  					{
  						Serial.println("error retype date please");
  						goto restart;
  					}
  				}
  				if(i == 10)
  				{
  					Serial.println();
  					Serial.println("Time set done - go to program");
  					break;
  				}

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

