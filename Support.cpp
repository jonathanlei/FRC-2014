#include "WPILib.h"
#include "Support.h"

void robotOut::printDebug(char *output, int message_type){
	if (message_type == NORMAL || message_type == SAME_LINE_NORMAL){
		if (message_type == SAME_LINE_NORMAL){
			printf(output);
		}
		else{
			printf("[NORMAL] %s", output);
		}
	}
	else if (message_type == EMERGENCY){
		fprintf(stderr, "[ERROR] %s", output);
	}
	else if ((message_type == DEBUG || message_type == SAME_LINE_DEBUG) && DEBUG_MODE){
		if (message_type == SAME_LINE_DEBUG){
			fprintf(stderr, output);
		}
		else{
			fprintf(stderr, "[DEBUG] %s", output);
		}
	}
}
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
	return this->sonar->GetVoltage();
}
float rangeFinder::getInFactor()
{
	return this->inFactor;
}
float rangeFinder::getFtFactor()
{
	return this->ftFactor;
}
