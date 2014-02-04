#ifndef KTKLIB_H_
#define KTKLIB_H_

#include "WPILib.h"
#include "Support.h"

#define frontRightDrivePort 2
#define rearRightDrivePort 4
#define frontLeftDrivePort 1
#define rearLeftDrivePort 3

class robotDriver {
	Victor frontRightMotor;
	Victor frontLeftMotor;
	Victor rearRightMotor;
	Victor rearLeftMotor;

public:
	robotDriver(void);
	void tankDrive(float leftStick, float rightStick);
	void arcadeDrive(float stickx, float sticky);
	void Turn(float speed);
	void Go(float speed);
	void mecanumDrive(float leftStickx, float leftSticky, float rightStickx, float rightSticky, bool squared);
};
#endif
