#ifndef BRAILLEKEYBOARD_H
#define BRAILLEKEYBOARD_H

#include <Arduino.h>
#define TIMEOUT_WAIT 1000
#define MAX_KEYS_PRESSED 6

class BrailleKeyboard
{
public:
	BrailleKeyboard();
	~BrailleKeyboard();
	bool readCodes(char* dots);
	bool available(char* dots, uint8_t extend);
	uint8_t getBTCodes();
	uint8_t getBTModifiers();
	uint8_t * getKeysPressed(); 
	void startTimeoutCtr();
	bool hasTimedOut(uint64_t usecsToTimeOut);
	
private:
	bool findNumber(char* dots);
	bool findSign4(char* dots);
	bool findSign5(char* dots);
	bool findSign45(char* dots);
	bool findSign46(char* dots);
	bool findSign456(char* dots);
	bool findAlphabets(char* dots);
	bool check(char* dots);
	uint8_t _keyPressed[MAX_KEYS_PRESSED];	//stored as btCodes
	uint8_t _BTKeyCodes;
	uint8_t _BTModifiers;
	char* _previousCode;
	bool _isNumber;
	int _isCapital;
	bool _isSS4;
	bool _isSS5;
	bool _isSS45;
	bool _isSS46;
	bool _isSS456;
	
	uint64_t _timeoutStartCtr;
	bool _timedOut;
};

#endif //BRAILLEKEYBOARD_H
