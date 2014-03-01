#include "WPILib.h"
#include "MainDriver.h"
#include "math.h"

mainDriver::mainDriver(void):
leftStick(leftStickPort),		// as they are declared above.
rightStick(rightStickPort),
coDriverStick(coDriverStickPort),
//gamePad(GAMEPADPORT),
frontRightMotor(frontRightDrivePort),
frontLeftMotor(frontLeftDrivePort),
rearRightMotor(rearRightDrivePort),
rearLeftMotor(rearLeftDrivePort)
{
}
void mainDriver::teleopDrive(void){

	// CRE: FIXME - Would be nice to have a run-time toggle to switch between drive modes. SendableChooser?
	this->mecanumDrive(leftStick.GetX(), leftStick.GetY(), rightStick.GetX(), rightStick.GetY(), true); // last argument squares the inputs, which is better for percise control
	/*
	int driveMode = JOYSTICK_TANK;

bp	if (driveMode == XBOX_TANK) {
		myRobot.tankDrive(gamePad.GetRawAxis(2), gamePad.GetRawAxis(5), true);
	} else if (driveMode == JOYSTICK_TANK){
		myRobot.tankDrive(leftStick.GetY(), rightStick.GetY(), true); // last argument squares the inputs, which is better for percise control
	} //sorry estabrooks, i hate compilier warnings */
}
double mainDriver::Lefty(void){
	return leftStick.GetY();
}
double mainDriver::Righty(void){
	return rightStick.GetY();
}
double mainDriver::Leftx(void){
	return leftStick.GetX();
}
double mainDriver::Rightx(void){
	return rightStick.GetX();
}
double mainDriver::rightThrottle(void){
	return rightStick.GetThrottle();
}
double mainDriver::leftThrottle(void){
	return leftStick.GetThrottle();
}
float mainDriver::returnLeftJoystick(int port){
	return leftStick.GetRawButton(port);
}
float mainDriver::returnRightJoystick(int port){
	return rightStick.GetRawButton(port);
}
float mainDriver::returnCoJoystick(int port){
	return coDriverStick.GetRawButton(port);
}
void mainDriver::tankDrive(float leftStick, float rightStick, bool squared){

	if (squared) {
		int rsign=1, lsign=1;
		if (leftStick < 0)
			lsign*=-1;
		if (rightStick < 0)
			rsign*=-1;

		rightStick = rsign * pow(rightStick, 2);
		leftStick = lsign * pow(leftStick, 2);
	}
	frontRightMotor.Set(rightStick);
	rearRightMotor.Set(rightStick);
	frontLeftMotor.Set(-leftStick);
	rearLeftMotor.Set(-leftStick);
}
void mainDriver::Go(float speed, float direction){
	frontRightMotor.Set(-1 * speed);
	rearRightMotor.Set(-1 * speed);
	frontLeftMotor.Set(speed);
	rearLeftMotor.Set(speed);
}
void mainDriver::Turn(float speed){
	frontRightMotor.Set(speed);
	rearRightMotor.Set(speed);
	frontLeftMotor.Set(speed);
	rearLeftMotor.Set(speed);
}
void mainDriver::arcadeDrive(float stickx, float sticky){
	frontRightMotor.Set(stickx - sticky);
	rearRightMotor.Set(stickx - sticky);
	frontLeftMotor.Set(stickx + sticky);
	rearLeftMotor.Set(stickx + sticky);
}
void mainDriver::mecBoxDrive(Joystick controller){
//	frontRightMotor.Set(rightSticky + rightStickx);
//	rearRightMotor.Set(rightSticky - rightStickx);
//	frontLeftMotor.Set(-1 * (leftSticky - leftStickx));
//	rearLeftMotor.Set(-1 * (leftSticky + leftStickx));
}
void mainDriver::mecanumDrive(float leftStickx, float leftSticky, float rightStickx, float rightSticky, bool squared){
	if (squared){
		// If we want to square the inputs, we have to make sure to preserve the sign, because otherwise its impossible to drive backwards (all axies would be zero or positive)
		if (rightSticky < 0){
			rightSticky = -pow(rightSticky, 2);
		}
		else {
			rightSticky = pow(rightSticky, 2);
		}
		if (rightStickx < 0){
			rightStickx = -pow(rightStickx, 2);
		}
		else {
			rightStickx = pow(rightStickx, 2);
		}
		if (leftSticky < 0){
			leftSticky = -pow(leftSticky, 2);
		}
		else {
			leftSticky = pow(leftSticky, 2);
		}
		if (leftStickx < 0){
			leftStickx = -pow(leftStickx, 2);
		}
		else {
			leftStickx = pow(leftStickx, 2);
		}
		frontRightMotor.Set(rightSticky + rightStickx);
		rearRightMotor.Set(rightSticky - rightStickx);
		frontLeftMotor.Set(-1 * (leftSticky - leftStickx));
		rearLeftMotor.Set(-1 * (leftSticky + leftStickx));
	}
	else {
		frontRightMotor.Set(rightSticky + rightStickx);
		rearRightMotor.Set(rightSticky - rightStickx);
		frontLeftMotor.Set(-1 * (leftSticky - leftStickx));
		rearLeftMotor.Set(-1 * (leftSticky + leftStickx));
	}
}

void mainDriver::triggerCheck(BigBlueBallShooter *shooter){
	if(coDriverStick.GetRawButton(BTN_SHOOT)){
		shooter->Shoot();
	}
}

void mainDriver::forkCheck(ForkLift *fork)
{
	if (fork->getMode() != FORK_GOING_UP) {
		fork->setMode(FORK_STOPPED);
	}

	if(coDriverStick.GetRawButton(BTN_FORK_UP)) {
		fork->setMode(FORK_GOING_UP);
	}
	else if (coDriverStick.GetRawButton(BTN_FORK_DN)) {
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
void mainDriver::winderCheck(BigBlueBallShooter *winder){
	if(coDriverStick.GetRawButton(BTN_WIND))
	{
		winder->Wind();
	}
	else{
		winder->stopWind();
	}
}
