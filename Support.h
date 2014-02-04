#ifndef SUPPORT_H_
#define SUPPORT_H_


#define DEBUG_MODE true
#define EMERGENCY 0
#define NORMAL 1
#define DEBUG 2
#define SAME_LINE_DEBUG 3
#define SAME_LINE_NORMAL 4

class robotOut {
public:
	void printDebug(char *output, int message_type);
};

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
};
#endif
