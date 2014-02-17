#include "WPILib.h"
#include "MainDriver.h"
#include "ktkLib.h"
 
mainDriver::mainDriver(void):
leftStick(leftStickPort),		// as they are declared above.
rightStick(rightStickPort),
gamePad(GAMEPADPORT)
{
}
void mainDriver::teleopDrive(void){

	// CRE: FIXME - Would be nice to have a run-time toggle to switch between drive modes. SendableChooser?
	myRobot.mecanumDrive(leftStick.GetX(), leftStick.GetY(), rightStick.GetX(), rightStick.GetY(), true); // last argument squares the inputs, which is better for percise control
	/*
	int driveMode = JOYSTICK_TANK;

bp	if (driveMode == XBOX_TANK) {
		myRobot.tankDrive(gamePad.GetRawAxis(2), gamePad.GetRawAxis(5), true);
	} else if (driveMode == JOYSTICK_TANK){
		myRobot.tankDrive(leftStick.GetY(), rightStick.GetY(), true); // last argument squares the inputs, which is better for percise control
	} /* */
}
/*
void mainDriver::arcadeDrive(void){
	myRobot.ArcadeDrive(-1 * leftStick.GetY(), true);
void mainDriver::killDrive(void){
	myRobot.StopMotor();
}
*/
void mainDriver::Go(float speed, float angle){
	myRobot.Go(speed);
}
void mainDriver::Turn(float speed){
	myRobot.Turn(speed);
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
