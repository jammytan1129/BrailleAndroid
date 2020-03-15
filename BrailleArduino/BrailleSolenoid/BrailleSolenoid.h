#ifndef BRAILLESOLENOID_H
#define BRAILLESOLENOID_H

#include <Arduino.h>
#define TIMEOUT_WAIT 2000
//Note: there are 1,000 microseconds in a millisecond and 1,000,000 microseconds in a second.

class BrailleSolenoid
{
public:
	BrailleSolenoid();
	~BrailleSolenoid();
	char* getPrintCode();
	bool next();
	bool previous();
	bool determine(String str);
	void startTimeoutCtr();
	bool hasTimedOut();
	
private:
 	char _currentWord[7] = {'1','1','1','1','1','1','\0'};
 	char _preCode[7] = {'1','1','1','1','1','1','\0'};
 	char _nextCode[7] = {'1','1','1','1','1','1','\0'};
 	char _printCode[7] = {'1','1','1','1','1','1','\0'};
 	char _buffer[600] = {'\0'};
 	String temp;
 	int _textSize;
 	int _currentLocation;
 	int _preLocation;
 	int _nextLocation;
 	char* string2char(String command);
 	bool search(char buffer);
 	bool searchDigit(char buffer);
 	bool searchAlpha(char buffer);
 	bool searchPunct(char buffer);
 	bool _isOpened;
	bool _isCapital;
	bool _isPunct;
	bool _isNumber;
	uint64_t _timeoutStartCtr;
	bool _timedOut;
};

#endif //BRAILLESOLENOID_H
