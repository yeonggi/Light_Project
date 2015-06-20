#include "Arduino.h"
#include "HomeAutoLight.h"
#include <avr/sleep.h>


//////////


/***************************CCD Sensor Class**************************************/
CCDSensor::CCDSensor(int sensing_pin, int interrupt_pin)
{
	Serial.begin(9600);
	pinMode(sensing_pin, INPUT);
	pinMode(interrupt_pin, INPUT);
	_sensing_pin = sensing_pin;
	_interrupt_pin = interrupt_pin;

	Bright_State =0;
	Dark_State = 0;
	_light_val = 0;
	_digit_val = 0;
	_before_sleep_state = 0;

}

int CCDSensor::get_anal_light_val()
{
	_light_val = analogRead(_sensing_pin) / 2;
	if(_light_val>400)
	{
		//Serial.println("Strong Light Detected  --");
	}
	return _light_val;
	//analogWrite(ledPin, analogRead(lightPin)/2);  //send the value to the ledPin. Depending on value of resistor
}

int CCDSensor::get_digit_light_val()
{
	_digit_val = digitalRead(_interrupt_pin);
	return _digit_val;
	//analogWrite(ledPin, analogRead(lightPin)/2);  //send the value to the ledPin. Depending on value of resistor
}

void CCDSensor::print_Value()
{
	Serial.println("====================start====================");
	Serial.print("CCD Sensing Value (30Kohm) = ");
	Serial.println(get_anal_light_val());

	Serial.print("Bright Digital value = ");
	Serial.println(get_digit_light_val());

	Serial.print("Bright state = ");
	Serial.print(Bright_State);
	Serial.print(", Dark State == " );
	Serial.print(Dark_State);
	Serial.println();

	Serial.print("before state : ");
	Serial.println(_before_sleep_state);
	Serial.println("======================end======================");

}

int CCDSensor::check_state_go_sleep()
{
	if(get_anal_light_val() > 100 && get_anal_light_val() < 400)
	{
		Bright_State++;
		if(Bright_State > 5)
		{
			Serial.println("Sleep mode Bright");

			Bright_State = 0;
			Dark_State = 0;
			//_before_sleep_state = BRIGHT_STATE;
			return BRIGHT_STATE;
			//Sleep.sleepNow();
		}
	}

	else if(get_anal_light_val() > 0 && get_anal_light_val() < 100)
	{
		Dark_State++;
		if(Dark_State > 5)
		{
			Serial.println("Sleep mode Dark");
			Bright_State =0;
			Dark_State = 0;
			//_before_sleep_state = DARK_STATE;
			return DARK_STATE;
			//sleepNow();
		}
	}
	delay(5);

	return false;
}



/***************************Sleep Mode Class**************************************/
SleepMode::SleepMode(int led_pin)
{
	_led_pin = led_pin;
	_sleep_status = LOW;
}

void SleepMode::sleepNow()
{

	set_sleep_mode(SLEEP_MODE_PWR_SAVE);   // sleep mode is set here
	//SLEEP_MODE_PWR_DOWN -> external interrupt and WathchDog Timer
	sleep_enable();
	//Serial.println("Go Sleep Mode !!!!!");
	attachInterrupt(0, wakeUpNow, CHANGE); // use interrupt 0 (pin 2) and run function
	sleep_mode(); // here the device is actually put to sleep!!
	sleep_disable();    // first thing after waking from sleep:
	detachInterrupt(0);      // disables interrupt 0 on pin 2 so the

}
/***************************LED Function**************************************/
LedOut::LedOut()
{
	pinMode(led_out_pin1,OUTPUT);
	pinMode(led_out_pin2,OUTPUT);
	pinMode(led_out_pin3,OUTPUT);
	pinMode(led_out_pin4,OUTPUT);
}

void LedOut::flash(int delay_ms, int flash_time)
{
	int i;
	for(i=0; i<flash_time; i++)
	{
		digitalWrite(led_out_pin1,HIGH);
		digitalWrite(led_out_pin2,HIGH);
		digitalWrite(led_out_pin3,HIGH);
		digitalWrite(led_out_pin4,HIGH);
		delay(delay_ms);

		digitalWrite(led_out_pin1,LOW);
		digitalWrite(led_out_pin2,LOW);
		digitalWrite(led_out_pin3,LOW);
		digitalWrite(led_out_pin4,LOW);
		delay(delay_ms);
	}

}
/***************************C Function**************************************/
void wakeUpNow()       // LED DisPlay
{

	// execute code here after wake-up before returning to the loop() function
	// timers and code using timers (serial.print and more...) will not work here.
	// we don't really need to execute any special functions here, since we
	// just want the thing to wake up
	digitalWrite(12, HIGH);
	delay(1000);
	digitalWrite(12, LOW);
}

int Get_Time_Data(int *time_data)
{
	int input;
	int i=0;
	int data_input=0;
	int data_out[5];
	int ch=0;
	enum date_string {YY, MM, DD, TT, mm};
	int date_buffer[11];

	char max_value[] = {99, 12, 32, 24, 60};
	Serial.begin(9600);  //Begin serial communcation

 	restart :

	input = 0;
  	memset(date_buffer,0,sizeof(date_buffer));
  	memset(data_out,0,sizeof(data_out));
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
  						data_out[i/2] = data_input;
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
  	memcpy(time_data,data_out,sizeof(data_out));
  	return 1;

}




