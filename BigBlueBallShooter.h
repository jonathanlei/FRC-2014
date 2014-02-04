#ifndef BIGBLUEBALLSHOOTER_H_
#define BIGBLUEBALLSHOOTER_H_

#include "Solenoid.h"

// Pneumatic port definitions
#define CYLINDER_PORT1 1
#define CYLINDER_PORT2 2
#define CYLINDER_MODULE 1

// PWM port definitions
#define WINDER_MOTOR_PORT 5

// Digital I/O port definitions
#define WINDER_LIMIT_PORT 2

class BigBlueBallShooter
{
	Victor winderMotor;
	DigitalInput winderLimit;

public:
	BigBlueBallShooter();
	void Shoot();
	
private:
	Solenoid* pSolenoid1;
	Solenoid* pSolenoid2;
	void Release();
	void Engage();
	void Wind();
};

#endif
