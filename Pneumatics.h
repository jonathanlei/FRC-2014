#ifndef PNEUMATICS_H_
#define PNEUMATICS_H_

#include "Compressor.h"
#include "Solenoid.h"

#define KICKER_PORT 1
#define KICKER_MODULE 1
#define SHOOTERL_MOTOR_PORT 5
#define SHOOTERR_MOTOR_PORT 6

class Kicker
{
	Victor shooterL;
	Victor shooterR;
public:
	Kicker();
	~Kicker();
	void Shoot();
private:
	Compressor* pCompressor;
	Solenoid* pSolenoid;
	void Extend();
	void Retract();
};

#endif
