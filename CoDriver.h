#ifndef CODRIVER_H_
#define CODRIVER_H_

#include "WPILib.h"
#include "BigBlueBallShooter.h"
#include "Support.h"

#define codriverStickPort 3
#define Trigger 1

class coDriver {
	Joystick codriverStick; // stick for the co-driver
	robotOut *coDriverOut;
public:
	coDriver(void);
	float returnJoystick(int);
	void triggerCheck(BigBlueBallShooter *);
};
#endif
