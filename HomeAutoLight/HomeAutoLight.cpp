#include "Arduino.h"
#include "HomeAutoLight.h"
#include <avr/sleep.h>


//////////
extern "C" {
	void wakeUpNow();
}

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
	Serial.print("CCD Sensing Value (10Kohm) = ");
	Serial.println(get_anal_light_val());

	Serial.print("Bright Digital value = ");
	Serial.println(get_digit_light_val());

	Serial.println();
	Serial.print("   Bright state == ");
	Serial.print(Bright_State);
	Serial.print("   Dark State == " );
	Serial.print(Dark_State);
	Serial.println();
}

int CCDSensor::check_state_go_sleep()
{
	if(get_anal_light_val() > 100 && get_anal_light_val() < 400)
	{
		// ���⼭ Bright Digital value �� 1�� �Ǿ�� �Ѵ�.
		Bright_State++;

		if(Bright_State > 20)
		{
			Serial.println("Sleep mode Bright");

			Bright_State = 0;
			Dark_State = 0;
			_before_sleep_state = BRIGHT_STATE;
			return BRIGHT_STATE;
			//Sleep.sleepNow();
		}
	}

	else if(get_anal_light_val() > 0 && get_anal_light_val() < 100)
	{
		Dark_State++;
		if(Dark_State > 20)
		{
			Serial.println("Sleep mode Bright");
			Bright_State =0;
			Dark_State = 0;
			_before_sleep_state = DARK_STATE;
			return DARK_STATE;
			//sleepNow();
		}
	}
	delay(50);

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
	attachInterrupt(0, wakeUpNow, CHANGE); // use interrupt 0 (pin 2) and run function
	sleep_mode(); // here the device is actually put to sleep!!
	sleep_disable();    // first thing after waking from sleep:
	detachInterrupt(0);      // disables interrupt 0 on pin 2 so the

}

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
