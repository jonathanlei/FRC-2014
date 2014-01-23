#include "CoDriver.h"

coDriver::coDriver(void):
	codriverStick(codriverStickPort)
{	
	coDriverOut = new robotOut;
}

float coDriver::returnJoystick(int port){
	return codriverStick.GetRawButton(port);
}

void coDriver::triggerCheck(Kicker *puckKicker){
	if(codriverStick.GetRawButton(Trigger)){
		puckKicker->Shoot();
	}
}
