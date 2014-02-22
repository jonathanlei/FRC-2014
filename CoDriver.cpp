#include "CoDriver.h"

coDriver::coDriver(void):
	codriverStick(codriverStickPort)
{	
	coDriverOut = new robotOut;
}

float coDriver::returnJoystick(int port){
	return codriverStick.GetRawButton(port);
}

void coDriver::triggerCheck(BigBlueBallShooter *shooter){
	if(codriverStick.GetRawButton(Trigger)){
		shooter->Shoot();
	}
}

void coDriver::forkCheck(ForkLift *fork)
{
	if(codriverStick.GetRawButton(ForkUp) && fork->getMode() != LOWER)
	{
		fork->raise();
	}
	else if (codriverStick.GetRawButton(ForkDn))
	{
		fork->lower();
	}
	else if (!codriverStick.GetRawButton(ForkDn) && fork->getMode() != RAISE)
	{
		fork->stop();
	}
/*	
	else {
		fork->stop();
		fork->setMode(false);
	}
*/
	if (fork->getMode() == STOP) {
		fork->stop();
	}
	else if (fork->getMode() == RAISE) {
		fork->raise();
	}
	/*
	else if (fork->getMode() == LOWER) {
		fork->lower();
	}
	*/
}
void coDriver::winderCheck(BigBlueBallShooter *winder){
	if(codriverStick.GetRawButton(windBtn))
	{
		winder->Wind();
	}
	else{
		winder->stopWind();
	}
}
