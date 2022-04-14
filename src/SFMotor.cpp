// ------------------------------------------------------------------------
// Telescope SF Motor Class
// Handle the control of a stepper motor using AccelStepper library
// ------------------------------------------------------------------------
#include "SFMotor.h"

float maxSpeed = 1000.0;
float minSpeed = 0.00027777;

// -------------------------------------------------------------
// Init
// -------------------------------------------------------------

SFMotor::SFMotor(byte imotorport, byte encoder_PPR) {
	stepper = new AccelStepper(HALFSTEP, MOTORS[imotorport][0], MOTORS[imotorport][1], MOTORS[imotorport][2], MOTORS[imotorport][3]);
    for (byte i=0;i<4;i++) {
        digitalWrite(MOTORS[imotorport][i], LOW);
    }
    stepper->disableOutputs();
    stepper->setMaxSpeed(maxSpeed);
    motor_max_byte_speed = MOTORS[imotorport][4];
}

void SFMotor::setSpeed(byte newByteSpeed) {
    // Mapping the 0-255 range values to steps per second.
    // if 0 is minimumMotorSpeed and max is _RA_MOTOR_MAX_SPEED
    // a value between those two values must be:
    // AS_speed = newSpeed * ((_RA_MOTOR_MAX_SPEED-minimumMotorSpeed)/max)
    currentSpeed = newByteSpeed * ((maxSpeed-minSpeed)/motor_max_byte_speed);
    stepper->setSpeed(currentSpeed);
}

void SFMotor::run(byte direction) {
    if (direction == RELEASE) {
        stepper->stop();
        stepper->disableOutputs();
    } else {
        stepper->setSpeed(currentSpeed*direction);
        stepper->runSpeed();
    }
}

long SFMotor::getPosition() {
    return stepper->currentPosition();
}
