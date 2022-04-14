// ------------------------------------------------------------------------
// Telescope Axis Class
// Handle The control, positioning and upkeep of a telescope axis
// equiv methods for ra and dec variants are paired up here
// ------------------------------------------------------------------------

#pragma once

#ifndef _sfmotor_h_
#define _sfmotor_h_

#include <Arduino.h>
#define __ARDUINO__

#include "settings.h"
#include "types.h"
#include <AccelStepper.h>

#define HALFSTEP 8

#define MOTOR12_1KHZ 0
#define RELEASE 0
#define BACKWARD -1
#define FORWARD 1

class SFMotor
{
	// Constructor
	// -----------
	public:
		// imotorport is used to identify the first or the second motor driver
		// I need to add into the settings.h the two set of pins to be used by the drivers
		SFMotor(byte imotorport, byte _a_value);
		void setSpeed(byte);
		void run(byte);
		long getPosition();
	private:
		AccelStepper 	*stepper;
		float			currentSpeed;
		byte			motor_max_byte_speed;
		int MOTORS[2][5] = {
    {motorPin1, motorPin3, motorPin2, motorPin4, _RA_MOTOR_MAX_SPEED+1}, 
    {motorPin5, motorPin7, motorPin6, motorPin8, _DEC_MOTOR_MAX_SPEED+1}
};

};

#endif
