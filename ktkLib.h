#ifndef KTKLIB_H_
#define KTKLIB_H_

#include "WPILib.h"
#include "Support.h"

#define frontLeftDrivePort 1
#define frontRightDrivePort 2
#define rearLeftDrivePort 3
#define rearRightDrivePort 4

class robotDriver {
	Jaguar frontRightMotor; // Testbed uses Victors, Aerial Panic uses Jaguars
	Jaguar frontLeftMotor;
	Jaguar rearRightMotor;
	Jaguar rearLeftMotor;

public:
	robotDriver(void);
	void tankDrive(float leftStick, float rightStick, bool squared);
	void arcadeDrive(float stickx, float sticky);
	void Turn(float speed);
	void Go(float speed);
	void mecanumDrive(float leftStickx, float leftSticky, float rightStickx, float rightSticky, bool squared);
};
#endif
