#ifndef CODRIVER_H_
#define CODRIVER_H_

#include "WPILib.h"
#include "BigBlueBallShooter.h"
#include "Support.h"

#define codriverStickPort 3
#define Trigger 10
#define ForkUp 2
#define ForkDn 3
#define windBtn 9

class coDriver {
	Joystick codriverStick; // stick for the co-driver
	robotOut *coDriverOut;
public:
	coDriver(void);
	float returnJoystick(int);
	void triggerCheck(BigBlueBallShooter *);
	void forkCheck(ForkLift *);
	void winderCheck(BigBlueBallShooter *);
};
#endif
