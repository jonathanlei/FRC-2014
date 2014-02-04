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
