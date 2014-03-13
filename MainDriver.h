#ifndef MAINDRIVER_H_
#define MAINDRIVER_H_
#include "BigBlueBallShooter.h"
// these are the pwn ports for the left and right motors respectively
#define frontRightDrivePort 2
#define rearRightDrivePort 4
#define frontLeftDrivePort 1
#define rearLeftDrivePort 3

// these are the ports for the joysticks on the PC
#define rightStickPort 2
#define leftStickPort 1
#define GAMEPADPORT 4

#define coDriverStickPort 3
#define BTN_SHOOT 10
#define BTN_FORK_UP 2
#define BTN_FORK_DN 3
#define BTN_WIND 9

#define TRIGGER 1

#define STOP 0
#define RAISE 1
#define LOWER 2

// Driver Controller Mode
#define JOYSTICK_TANK 0
#define JOYSTICK_MECANUM 1
#define XBOX_TANK 2
#define XBOX_ARCADE 3
#define XBOX_MECANUM 4

class mainDriver {
	Joystick leftStick; // left joystick
	Joystick rightStick; // right joystick
	Joystick coDriverStick; // Where "1" is the index of the joystick (you can set this in the Driver Station software).
	Joystick gamePad;
	int driveMode;
	Jaguar frontRightMotor; // Testbed uses Victors, Aerial Panic uses Jaguars
	Jaguar frontLeftMotor;
	Jaguar rearRightMotor;
	Jaguar rearLeftMotor;
public:
	void tankDrive(float leftStick, float rightStick, bool squared);
	void arcadeDrive(float stickx, float sticky);
	void Turn(float speed);
	void mecanumDrive(float leftStickx, float leftSticky, float rightStickx, float rightSticky, bool squared);
	void mecBoxDrive(bool squared);
	void triggerCheck(BigBlueBallShooter *);
	mainDriver(void);
	void Go(float, float);
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
	float returnMainJoystick(int);
	void forkCheck(BigBlueBallShooter *);
	void winderCheck(BigBlueBallShooter *);
};
#endif
