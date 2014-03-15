#ifndef SUPPORT_H_
#define SUPPORT_H_

class rangeFinder {
	AnalogChannel *sonar;
	static const float ftFactor=1/(.0098*12);
	static const float inFactor=1/.0098;
public:
	rangeFinder(int);
	float getRangeFt();
	float getRangeIn();
	float getVoltage();
	float getInFactor();
	float getFtFactor();
	bool inRange();
};
#endif
