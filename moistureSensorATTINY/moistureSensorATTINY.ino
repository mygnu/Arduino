/*mostureSensorATTINY.ino --- detects moisture from the soil and turns the pump on and off accordingly
 */

/*     Filename: mostureSensorATTINY.ino
**     Description: detects moisture from the soil and turns the pump on and off accordingly
**     Author: harry <harry@Ubuntu-STA>
**     Maintainer: harry <harry@Ubuntu-STA>
**     Copyright (C) 2013, harry, all rights reserved.
**     Created: 02-09-2013 11:40:37
**     Version: 0.1
**     Last-Updated: 02-09-2013
**               By: harry
**    // TODO
**           
**    
**    
**    
*/
// AMTEL ATTINY45 / ARDUINO PIN-MAP
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc +5V
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2)  Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//                  +----+

// Code:

//define macros
#define redLed 2
#define greenLed 3
#define sensorPin A0
#define relayPin  4
#define potMPin A2
#define sensorRead (sensorVal(sensorPin))
#define pumpOn (digitalWrite(relayPin, HIGH))
#define pumpOff (digitalWrite(relayPin, LOW))
#define pMinutes (poten2minutes(potMPin))


// global variables



// end global variables

//function defs

int sensorVal(byte pin);
void waitBlink(byte pin, int numBlinks, int mins);
int poten2minutes(byte Pin);
//end funtcion defs

/* following code runs only once at startup */
void setup()
{
	// put your setup code here, to run once:
	analogRead(sensorPin);
	analogRead(potMPin);
	pinMode(redLed, OUTPUT);
	pinMode(greenLed, OUTPUT);
	pinMode(relayPin, OUTPUT);
}

/* following code runs again and again during the power on */
void loop()
{
	// put your main code here, to run repeatedly:

	if (sensorRead < 250) // not connected or faulty value
		{
			pumpOff;
			waitBlink(redLed, 10, 0); //blink 10
		}
	

	else if((sensorRead >= 250) && (sensorRead < 600))
	 
		{
			waitBlink(redLed, 10, 0); //blink 10 times
			pumpOn;
			waitBlink(redLed, 0, ((pMinutes) * 2)); // its dry run it for double the time
		}
	else if((sensorRead >= 600) && (sensorRead <= 800))
		{
			waitBlink(redLed, 3, 0);
			pumpOn;
			waitBlink(redLed, 0, pMinutes);
		}

	else if((sensorRead > 800) && (sensorRead < 850))
		{
			pumpOff;
			waitBlink(greenLed, 10 , 0);
			waitBlink(greenLed, 0, 20); // wait for 20 minutes
		}
	else
		{
			pumpOff;
			waitBlink(greenLed, 0, 120); // wait for 2 hours before readig the sensor value again
		}
	
}


void waitBlink(byte pin, int numBlinks, int mins) 
{
	byte i;
	if(mins > 0)
		{
		for (i = 0; i < mins; ++i)
			{
			digitalWrite(pin, HIGH);
			delay(500); // led on for half a second
			digitalWrite(pin, LOW);
			delay(59500); //delay for one minute
			
			}
		} else{
		for(i = 0; i < numBlinks; i++ )
			{
				digitalWrite(pin, HIGH); // turns on the pin on to 5v 
				delay(250);             // keeps the led on for one quater second 
				digitalWrite(pin, LOW);  // turn off the led
				delay(250);
				
			}
		}
	
}

// reads the moisture sensor 
int sensorVal(byte pin) // takes the pin number as an argument
{
	int val0 = analogRead(pin);
	delay(100);
	int val1 = analogRead(pin); // reads the value three times 
	delay(100);
	int val2 = analogRead(pin);

	int sensorValue = (val1 + val0 + val2) /3;

	return sensorValue; // returns the average value (0 to 1023)
}


// reads the potentiometer and returns int from 1 to 30
int poten2minutes(byte pin)
{
	
	//unsigned int sensorVal = 0;// variable to store the value coming from the potentiometer
	unsigned int sensorVal1 = 0;
	unsigned int sensorVal2 = 0;
	unsigned int sensorVal3 = 0;
	int Mins = 0;
	
	sensorVal1 = analogRead(pin);
	delay(100);
	sensorVal2 = analogRead(pin);
	delay(100);
	sensorVal3 = analogRead(pin);
	sensorVal1 = (sensorVal1 + sensorVal2 + sensorVal3) /3;
	Mins = sensorVal1 / 34;

	if (Mins < 1)
		{
			Mins = 1;
		} else if(Mins > 30)
		{
			Mins = 30;
		}
	return Mins; 
}

// mostureSensorATTINY.ino ends here






