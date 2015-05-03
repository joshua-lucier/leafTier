/*
 * MyClass.h
 *
 * Created: 4/29/2015 12:27:48 PM
 * Author: jmluc_000
 */ 

#ifndef _MYCLASS_h
#define _MYCLASS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <avr/io.h>

#include "NewPing.h"

class MyClass
{
 private:


 public:
	void setup();
	void loop();
	uint16_t analogueReadL();
};

extern MyClass myClass;

#endif

