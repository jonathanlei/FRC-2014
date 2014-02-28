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
	if(codriverStick.GetRawButton(BTN_SHOOT)){
		shooter->Shoot();
	}
}

void coDriver::forkCheck(ForkLift *fork)
{
	if (fork->getMode() != FORK_GOING_UP) {
		fork->setMode(FORK_STOPPED);
	}
	
	if(codriverStick.GetRawButton(BTN_FORK_UP)) {
		fork->setMode(FORK_GOING_UP);
	}
	else if (codriverStick.GetRawButton(BTN_FORK_DN)) {
		fork->setMode(FORK_GOING_DN);
	}

	if (fork->getMode() == FORK_STOPPED) {
		fork->stop();
	}
	else if (fork->getMode() == FORK_GOING_UP) {
		fork->raise();
	}
	else if (fork->getMode() == FORK_GOING_DN) {
		fork->lower();
	}
}
void coDriver::winderCheck(BigBlueBallShooter *winder){
	if(codriverStick.GetRawButton(BTN_WIND))
	{
		winder->Wind();
	}
	else{
		winder->stopWind();
	}
}
