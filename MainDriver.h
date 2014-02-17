#ifndef MAINDRIVER_H_
#define MAINDRIVER_H_
// these are the pwn ports for the left and right motors respectively
#include "ktkLib.h"
#define frontRightDrivePort 2
#define rearRightDrivePort 4
#define frontLeftDrivePort 1
#define rearLeftDrivePort 3

// these are the ports for the joysticks on the PC
#define rightStickPort 2
#define leftStickPort 1
#define GAMEPADPORT 3

// Driver Controller Mode
#define JOYSTICK_TANK 0
#define JOYSTICK_MECANUM 1
#define XBOX_TANK 2
#define XBOX_ARCADE 3
#define XBOX_MECANUM 4

class mainDriver {
	robotDriver myRobot; // robot drive system
	Joystick leftStick; // left joystick
	Joystick rightStick; // right joystick
	Joystick gamePad; // Where "1" is the index of the joystick (you can set this in the Driver Station software).
	int driveMode;
public:
	mainDriver(void);
	void Go(float, float);
	void Turn(float);
	void teleopDrive(void);
//	void arcadeDrive(void);
//	void disableSafety(void);
//	void killDrive(void);
	double Lefty(void);
	double Righty(void);
	double Leftx(void);
	double Rightx(void);
	double leftThrottle(void);
	double rightThrottle(void);
	float returnLeftJoystick(int);
	float returnRightJoystick(int);

};
#endif
