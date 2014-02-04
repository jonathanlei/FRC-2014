#include "WPILib.h"
#include "BigBlueBallShooter.h"
#include "MainDriver.h"
#include "CoDriver.h"
#include "ktkLib.h"
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
	mainDriver *Driver1;
	robotOut *terminalOut;
	coDriver *Driver2;
	DriverStationLCD *DsLCD;
	Task *notificationTask;
	BigBlueBallShooter *shooter;
	rangeFinder *rangeFront;
	Gyro *gyro;
	Compressor *c;
	
public:
	Robot_2014(void){
		Driver1 = new mainDriver;
		Driver2 = new coDriver;
		terminalOut = new robotOut;
		shooter = new BigBlueBallShooter();
		DsLCD = DriverStationLCD::GetInstance();
		rangeFront = new rangeFinder(FRONT_SONAR_PORT);
		gyro = new Gyro(1);
		c = new Compressor(PRESSURE_SWITCH_PORT, SPIKE_RELAY_PORT);
	}
	~Robot_2014(void) {
		delete DsLCD;
		delete terminalOut;
		delete Driver2;
		delete Driver1;
	}
	void RobotInit()
	{
		printf("Entering RobitInit()!\n");
		printf("We cannot start the compressor until robot is enabled.\n");
	}
	void Disabled()
	{
		printf("I'm disabled!\n");
	}
	/**
	 * CRE 01-11-14 Attempting to add test code.
	 */
	void Test() {
		while (IsTest() && IsEnabled())
		{
			float range;
			printf("Entering Test()\n");
			gyro->Reset();
			
			while (IsTest() && IsEnabled())
			{
				float angle = gyro->GetAngle();
				printf("Gyro angle = %f\n", angle);
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
				if (angle < -45 || angle > 45)
				{
	//				Driver1->Go(.1, -angle*Kp); // turn to correct heading
					shooter->Shoot();
					printf("Completed shooting cycle\n");
				}
				else
				{
	//				Driver1->Go(0.0, 0.0);
				}
				Wait(.5);			
			}
		}
	}
	
	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		c->Start();
		gyro->Reset();
		float range = rangeFront->getRangeFt();

		if (IsAutonomous() && IsEnabled()) { // Kevin's Kludgy code fixed by Henry 01-11-14
			while (range > 6)
			{
				Driver1->Go(0.1, 0.0); // Go forward half speed
				range = rangeFront->getRangeFt();
			}
			printf("RangeFront: %f\n", range);
			// Brake
			Driver1->Go(-1.0, 0.0);
			Wait(0.01);
			Driver1->Go(0.0, 0.0);
			shooter->Shoot();
		}
	}
	void OperatorControl(void)
	{
		Wait(.5); //let teleop finish before we start teleop
		startTasks();
		terminalOut->printDebug("starting Teleop\n", 1);
		DsLCD->PrintfLine(DsLCD->kUser_Line1, "Entering Teleop mode");
		DsLCD->UpdateLCD();
//		Driver1->disableSafety();
		terminalOut->printDebug("Teleop initalziation completed\n", 2);
		SmartDashboard::PutBoolean("In Teleop", true);
		while (IsOperatorControl()){
			Driver1->teleopDrive();
			Driver2->triggerCheck(shooter);
			Wait(0.005);
		}
		stopTasks();
	}
	static int notifierTask(Robot_2014 *robot){
		// This task manages putting joystick values on to the dashboard
		while (true){  //  Being a task, we loop forever (or until Task::Stop() is used)
			for (int differentJoysticks = 1; differentJoysticks < 4; differentJoysticks++){ // for each of our three joysticks
				for (int count = 1; count < 12; count++){ // for each button on a joystick
					char location [5]; // create a sting that has a buffer 5 characters long for brian cryptic button names
					bool buttonValue; // create a bool that we will feed the current value of the button in to
					// next we check what joystick we are on and feed that value into buttonValue
					if (differentJoysticks == 1){ 
						buttonValue = robot->Driver1->returnLeftJoystick(count);
					}
					if (differentJoysticks == 2){
						buttonValue = robot->Driver1->returnRightJoystick(count);
					}
					if (differentJoysticks == 3){
						buttonValue = robot->Driver2->returnJoystick(count);
					}
					sprintf(location, "%d_%d", differentJoysticks, count); // make a "joystick#_button#" string to appease brians dashboard
					SmartDashboard::PutBoolean(location, buttonValue); // put the finished value on the dashboard
				}
			}
			// the following lines cannot be put on the dashboard by my loop, so i threw them here
			SmartDashboard::PutNumber("Y-Axis1", robot->Driver1->Lefty());
			SmartDashboard::PutNumber("X-Axis1", robot->Driver1->Leftx());
			SmartDashboard::PutNumber("Y-Axis2", robot->Driver1->Righty());
			SmartDashboard::PutNumber("X-Axis2", robot->Driver1->Rightx());
			SmartDashboard::PutNumber("Right Drive Motor", robot->Driver1->Lefty());
			SmartDashboard::PutNumber("Left Drive Motor", robot->Driver1->Righty());
			SmartDashboard::PutNumber("Throttle2", robot->Driver1->rightThrottle());
			SmartDashboard::PutNumber("Throttle1", robot->Driver1->leftThrottle());
			Wait(.02);  // lets not starve the crio doing tasks
		}
		return 0;
	}
	void startTasks(void){
		char name[30];
		sprintf(name, "notificationThread-%ld", GetFPGATime());
		notificationTask = new Task(name, (FUNCPTR)this->notifierTask);
		notificationTask->Start((INT32)this);	
	}
	void stopTasks(void){
		notificationTask->Stop();
	}
};

START_ROBOT_CLASS(Robot_2014);

