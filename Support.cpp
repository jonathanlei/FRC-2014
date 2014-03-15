#include "WPILib.h"
#include "Support.h"

rangeFinder::rangeFinder(int channel)
{
	sonar = new AnalogChannel(channel);
}
float rangeFinder::getRangeFt()
{
	float range = this->getVoltage();
	return (range * this->ftFactor);
}
float rangeFinder::getRangeIn()
{
	float range = this->getVoltage();
	return (range * this->inFactor);
}
float rangeFinder::getVoltage()
{
	this->sonar->SetAverageBits(2);
	float rangeAvg = this->sonar->GetAverageVoltage();
	return rangeAvg;
}
bool rangeFinder::inRange(){
	return 2.2 < this->getRangeFt() < 2.8;
}
float rangeFinder::getInFactor()
{
	return this->inFactor;
}
float rangeFinder::getFtFactor()
{
	return this->ftFactor;
}
