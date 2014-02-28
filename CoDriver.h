#ifndef CODRIVER_H_
#define CODRIVER_H_

#include "WPILib.h"
#include "BigBlueBallShooter.h"
#include "Support.h"

#define codriverStickPort 3
#define BTN_SHOOT 10
#define BTN_FORK_UP 2
#define BTN_FORK_DN 3
#define BTN_WIND 9

#define STOP 0
#define RAISE 1
#define LOWER 2

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
