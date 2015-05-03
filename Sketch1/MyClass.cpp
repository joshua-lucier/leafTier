/*
 * MyClass.cpp
 *
 * Created: 4/29/2015 12:27:48 PM
 * Author: jmluc_000
 */ 

#include "MyClass.h"

#define PING_PIN  12  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(PING_PIN, PING_PIN, MAX_DISTANCE); // NewPing setup of pin and maximum distance.
//extern "C" uint16_t _asmMain(void);


void MyClass::setup()
{
	Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void MyClass::loop()
{
  Serial.print("Started...Testing Analog");
  uint16_t light16 = analogueReadL(); //only uses PORTD0 analogue
  Serial.print("Completed Analog");
  int light = (int)light16;
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Range");
  Serial.print(" ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.print("\n");
  Serial.flush();
  Serial.print("Light");
  Serial.print(" ");
  Serial.print(light);
  Serial.print("\n");
  
}

uint16_t MyClass::analogueReadL(void)
{
	uint16_t myresult;
	asm(
		"\n\t"
		"ADC_Init:" "\n\t"
		"ldi r16,0" "\n\t" //setup for pin 0
		"ori r16, 0x60" "\n\t"
		"sts 0x7C, r16" "\n\t"//load settings into ADMUX
		"ldi r16, 0xC7" "\n\t"//enable ADC single mode conversion 11000111
		"sts 0x7A, r16" "\n\t" //load settings
		"lds r18, 0x7A" "\n\t"
		"sbr r18, 0x06" "\n\t"//ADC to ADCSRA ADSC bit
		"sei" "\n\t"
		"sts 0x7A, r18" "\n\t"
		"Wait:" "\n\t"
		"lds r18, 0x7A" "\n\t"
		"sbrs r18,4" "\n\t"//Set ADIF bit if set skip loop
		"rjmp Wait" "\n\t" //loop
		"Ret:" "\n\t" //break loop
		"lds r24,0x78"  "\n\t"//ADCL to r16
		"lds r25,0x79"  "\n\t"//ADCH to r17
		"mov %A0, r24" "\n\t"
		"mov %B0, r25" "\n\t"
		"ret" "\n\t"//*/
		:"=&r"(myresult):
	);
/*
	asm volatile(
	"\n"
	//initialize ADC
	"init:" "\n\t"
	"ldi r24, 0" //ready for input
	"sts 0x07, r24" //set port to input
	"ldi r24, 0B01000000" "\n\t" //Save 0 to register. ADC ADMUX setting
	"sts 0x7C, r24" "\n\t" //Load 0 to 0x7C analog reference = 0 and channel = 0  ADLAR = 0
	//start conversion
	"conv:" "\n\t"
	"lds r24, 0x7A" "\n\t"//get data from 0x7A (ADCSRA)
	"ldi r25, 0" "\n\t"//load 0 for or
	"or r24, r25" "\n\t"//or conversion
	"sts 0x7A, r24" "\n\t"//store the value in 0x7A
	//clear the ADSC
	"clearADSC:" "\n\t"
	"lds r24, 0x7A"  "\n\t"//load 0x7A data
	"sbrc r24, 6" "\n\t"//checks bit 6 is cleared.  If it is, skip next line (loop)
	"rjmp clearADSC" "\n\t"//loop
	//load from ADC
	"lds r18, 0x78" "\n\t"//load first 8 bytes from ADC data
	"lds r20, 0x79" "\n\t"//load second 8 bytes from ADC data
	"mov r25, r20" "\n\t"//copy 0x79 data
	"ldi r24, 0" "\n\t"//load 0 for conversion
	"ldi r19, 0" "\n\t"//load 0 for conversion
	"or r18, r24" "\n\t"//convert 0x78 data
	"or r19, r25" "\n\t"//convert 0x79 data
	//combine the two bytes for return
	"sts %A0, r18" "\n\t"
	"sts %B0, r19" "\n\t"
	//"sts %A0, r18" "\n\t"
	//"sts %B0, r19" "\n\t"
	"ret"
	:"=M"(_SFR_IO_ADDR(myresult))
	::
	);
*/
	return myresult;
}
MyClass myClass;

