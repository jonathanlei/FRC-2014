#include "WPILib.h"
#include "ktkLib.h"
#include "math.h"
 
robotDriver::robotDriver(void):
frontRightMotor(frontRightDrivePort),
frontLeftMotor(frontLeftDrivePort),
rearRightMotor(rearRightDrivePort),
rearLeftMotor(rearLeftDrivePort)
{
}
void robotDriver::tankDrive(float leftStick, float rightStick){
	frontRightMotor.Set(rightStick);
	rearRightMotor.Set(rightStick);
	frontLeftMotor.Set(leftStick);
	rearLeftMotor.Set(leftStick);
}
void robotDriver::arcadeDrive(float stickx, float sticky){
	frontRightMotor.Set(stickx - sticky);
	rearRightMotor.Set(stickx - sticky);
	frontLeftMotor.Set(stickx + sticky);
	rearLeftMotor.Set(stickx + sticky);
}
void robotDriver::mecanumDrive(float leftStickx, float leftSticky, float rightStickx, float rightSticky, bool squared){
	if (squared){
		// If we want to square the inputs, we have to make sure to preserve the sign, because otherwise its impossible to drive backwords (all axies would be zero or positive)
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
