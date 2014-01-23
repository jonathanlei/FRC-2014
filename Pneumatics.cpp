#include "WPILib.h"
#include "Pneumatics.h"

Kicker::Kicker(void):
	shooterL(SHOOTERL_MOTOR_PORT),
	shooterR(SHOOTERR_MOTOR_PORT)
{
	this->pCompressor = new Compressor(1,1); // the args here are the pressure switch on the compressor and the spike and that controls it
	this->pSolenoid = new Solenoid(KICKER_PORT); // connect solenoid to proper channel on pneumatics card
	this->pCompressor->Start();
	this->pSolenoid->Set(false);
}
Kicker::~Kicker()
{
}
void Kicker::Extend()
{
	this->pSolenoid->Set(true);
}

void Kicker::Retract()
{
	this->pSolenoid->Set(false);
}

void Kicker::Shoot()
{
	// Spin up shooter wheels
	shooterL.Set(-1);
	shooterR.Set(1); // Not sure which motor needs to turn backward
	Wait(1); // wait for it...
	 // Kick puck into shooter wheels
	this->Extend(); 
	Wait(1); // wait for it...
	this->Retract();
	// Spin down shooter wheels
	shooterL.Set(0);
	shooterR.Set(0);
	
}
