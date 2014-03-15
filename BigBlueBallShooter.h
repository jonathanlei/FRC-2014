#ifndef BIGBLUEBALLSHOOTER_H_
#define BIGBLUEBALLSHOOTER_H_

#include "Solenoid.h"

// Pneumatic port definitions
#define CYLINDER_PORT1 8 // Aerial Panic solenoid wired to port 8 on pneumatic break-out card
#define CYLINDER_PORT2 2
#define CYLINDER_MODULE 1

// PWM port definitions
#define WINDER_MOTOR_PORT 5
#define LIFTER_MOTOR_PORT 6

// Digital I/O port definitions
#define FORK_UPPER_LIMIT_PORT 1
#define FORK_LOWER_LIMIT_PORT 2
// port three used for Compressor Pressure Switch
#define WINDER_LIMIT_PORT 4

// Fork Motion Modes
#define FORK_STOPPED 0
#define FORK_GOING_UP 1
#define FORK_GOING_DN 2

class BigBlueBallShooter
{
	Victor winderMotor;
	DigitalInput winderLimit;
	Victor lifterMotor;
	DigitalInput upperLimit;
	DigitalInput lowerLimit;
	int raiseMode; 			// Forklift mode: 0=stop, 1=raise, 2=lower

public:
	BigBlueBallShooter();
	void Shoot();
	void Wind();
	void stopWind();
	void Kick();
	void Fire();
	void kickDown();
	void raiseFork();
	void lowerFork();
	void stopFork();
	void setMode(int); // Set fork mode: Raising
	bool returnUpperLimit();
	bool returnLowerLimit();
	bool returnWinderLimit();
	int getMode();
	
private:
	Solenoid* pSolenoid1;
//	Solenoid* pSolenoid2;  // Testbed has double solenoid, AerialPanic has 1x
	void Release();
	void Engage();
};
#endif

