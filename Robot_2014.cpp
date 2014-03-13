#include "WPILib.h"
#include "BigBlueBallShooter.h"
#include "MainDriver.h"
#include "Support.h"

#define PRESSURE_SWITCH_PORT 3
#define SPIKE_RELAY_PORT 3
#define FRONT_SONAR_PORT 6

/*
 *	Team 1740
 *	Aerial Assist Code
 *	Programming Staff:
 *	Brian Healy: Team Captain and Labview / TI84 guy
 *	Kevin Konrad: Programming Captain and Python / C++ guy
 *	Charles Estabooks: Programming Mentor and C/C++ Guy
 *	Test string to see if changes to the code are going into svn properly or not
 */
class Robot_2014 : public SimpleRobot
{
	mainDriver *Driver;
	DriverStationLCD *DsLCD;
	Task *coDriveTask;
	BigBlueBallShooter *shooter;
	rangeFinder *rangeFront;
//	Gyro *gyro;
	Compressor *compressor;
	
public:
	Robot_2014(void){
		Driver = new mainDriver;
		shooter = new BigBlueBallShooter();
		DsLCD = DriverStationLCD::GetInstance();
		rangeFront = new rangeFinder(FRONT_SONAR_PORT);
//		gyro = new Gyro(1);
		compressor = new Compressor(PRESSURE_SWITCH_PORT, SPIKE_RELAY_PORT);
//		compressor->Start();
		
	}
	~Robot_2014(void) {
		delete DsLCD;
		delete Driver;
		delete shooter;
//		delete gyro;
		delete compressor;
		delete rangeFront;
	}
	void RobotInit()
	{
		printf("Entering RobitInit()!\n");
		printf("We cannot start the compressor until robot is enabled.\n");
		compressor->Start();
	}
	void Disabled()
	{
		printf("I'm disabled!\n");
		stopTasks();
	}
	/**
	 * CRE 01-11-14 Attempting to add test code.
	 */
	void Test() {
		while (IsTest() && IsEnabled())
		{
			float range;
			printf("Entering Test()\n");
//			gyro->Reset();
			
			while (IsTest() && IsEnabled())
			{
//				float angle = gyro->GetAngle();
//				printf("Gyro angle = %f\n", angle);
				range = rangeFront->getRangeFt();
				printf("RangeFront (ft): %f\n", range);
				range = rangeFront->getVoltage();
				printf("RangeFront (v): %f\n", range);
				range = rangeFront->getFtFactor();
				printf("FtFactor = %f\n",range);
				/* 
				 * 
				 * Gyro proof-of-concept code 
				 */ 
	//			static const float Kp=0.03;
/*				if (angle < -45 || angle > 45)
				{
	//				Driver->Go(.1, -angle*Kp); // turn to correct heading
					shooter->Shoot();
					printf("Completed shooting cycle\n");
				}
				else
				{
	//				Driver->Go(0.0, 0.0);
				}
				*/
				Wait(.5);			
			}
		}
	}
	
	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
//		gyro->Reset();
		float range = rangeFront->getRangeFt();

		if (IsAutonomous() && IsEnabled()) { // Kevin's Kludgy code fixed by Henry 01-11-14
			while (range > 2.5)
			{
				Driver->Go(0.5, 0.0); // Go forward half speed
				range = rangeFront->getRangeFt();
			}
			printf("RangeFront: %f\n", range);
			// Brake
			Driver->Go(-1.0, 0.0);
			Wait(0.01);
			Driver->Go(0.0, 0.0);
			shooter->Shoot();
		}
	}
	void OperatorControl(void)
	{
		
		Wait(.5); //let teleop finish before we start teleop
		printf("Entering Teleop!\n");
		startTasks();
		DsLCD->PrintfLine(DsLCD->kUser_Line1, "Entering Teleop mode");
		DsLCD->UpdateLCD();
//		Driver->disableSafety();
//		SmartDashboard::PutBoolean("In Teleop", true);
		while (IsOperatorControl()){
			Driver->teleopDrive();
			Wait(0.005);
		}
		stopTasks();
	}
	static int notifierTask(Robot_2014 *robot){
		// This task manages putting joystick values on to the dashboard
		while (true){  //  Being a task, we loop forever (or until Task::Stop() is used)
				for (int count = 1; count < 11; count++){ // for each button on a joystick
					char location [5]; // create a sting that has a buffer 5 characters long for brian cryptic button names
					bool buttonValue; // create a bool that we will feed the current value of the button in to
					// next we check what joystick we are on and feed that value into buttonValue
					buttonValue = robot->Driver->returnMainJoystick(count);
					sprintf(location, "%d_%d", 1, count); // make a "joystick#_button#" string to appease brians dashboard
					SmartDashboard::PutBoolean(location, buttonValue); // put the finished value on the dashboard
			
			}
			SmartDashboard::PutBoolean("inRange", robot->rangeFront->inRange());
			SmartDashboard::PutBoolean("Range", robot->rangeFront->getRangeFt());
			// the following lines cannot be put on the dashboard by my loop, so i threw them here
			SmartDashboard::PutNumber("Y-Axis1", robot->Driver->Lefty());
			SmartDashboard::PutNumber("X-Axis1", robot->Driver->Leftx());
			SmartDashboard::PutNumber("Y-Axis2", robot->Driver->Righty());
			SmartDashboard::PutNumber("X-Axis2", robot->Driver->Rightx());
			SmartDashboard::PutNumber("Right Drive Motor", robot->Driver->Lefty());
			SmartDashboard::PutNumber("Left Drive Motor", robot->Driver->Righty());
//			SmartDashboard::PutNumber("Throttle2", robot->Driver->rightThrottle());
//			SmartDashboard::PutNumber("Throttle1", robot->Driver->leftThrottle());
			Wait(.02);  // lets not starve the crio doing tasks
		}
		return 0;
	}
	static int coDriverTask(Robot_2014 *robot){
		while (true){
			robot->Driver->forkCheck(robot->shooter);
			robot->Driver->winderCheck(robot->shooter);
			robot->Driver->triggerCheck(robot->shooter);
			Wait(.01);
		}
		return 0;
	}
	void startTasks(void){
		char name[30];
		sprintf(name, "coDriverThread-%ld", GetFPGATime());
		coDriveTask = new Task(name, (FUNCPTR)this->coDriverTask);
		coDriveTask->Start((INT32)this);
	}
	void stopTasks(void){
		coDriveTask->Stop();
	}
};

START_ROBOT_CLASS(Robot_2014);

