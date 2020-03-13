#ifndef  BRAILLEBLUETOOTH_H
#define BRAILLEBLUETOOTH_H

#include <Arduino.h>

class BrailleBluetooth
{
public:
	BrailleBluetooth(uint32_t baudRate, bool useSoftwareSerial, uint8_t softwareRXPin, uint8_t softwareTXPin);
	~BrailleBluetooth();
	void sendKeyboardState(uint8_t modifiers, uint8_t * keysPressed);
	void getKeyboardLEDState();
	
private:
	bool _useSoftwareSerial;
	Stream * _serialStream;
};

#endif // ! BRAILLEBLUETOOTH_H
