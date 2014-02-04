#include "WPILib.h"
#include "BigBlueBallShooter.h"

BigBlueBallShooter::BigBlueBallShooter(void):
	winderMotor(WINDER_MOTOR_PORT),
	winderLimit(WINDER_LIMIT_PORT)
{
	this->pSolenoid1 = new Solenoid(CYLINDER_PORT1); // connect solenoid to proper channel on pneumatics card
	this->pSolenoid2 = new Solenoid(CYLINDER_PORT2); // connect solenoid to proper channel on pneumatics card
	this->Release();
	this->winderMotor.Set(0);
}
void BigBlueBallShooter::Release()
{
	this->pSolenoid1->Set(false);
	this->pSolenoid2->Set(true);
}

void BigBlueBallShooter::Engage()
{
	this->pSolenoid1->Set(true);
	this->pSolenoid2->Set(false);
}

void BigBlueBallShooter::Shoot()
{
	// Engage winder gear
	this->Engage();
	// Wait until the limit switch is pressed
	while (winderLimit.Get() == 0)
	{
		// wind
		winderMotor.Set(1.0);
		Wait(.01);
	}
	// disengage winder gear to shoot
	this->Release();
	// Reverse motor briefly to jar the cylinder loose and allow spring to retract
	winderMotor.Set(-1.0);
	Wait(.05);
	// stop_winder
	winderMotor.Set(0.0);
}


