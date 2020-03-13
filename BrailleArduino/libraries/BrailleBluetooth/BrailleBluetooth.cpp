#include <SoftwareSerial.h>

#include "BrailleBluetooth.h"
#include "BrailleKeyboard.h"

BrailleBluetooth::BrailleBluetooth(uint32_t baudRate, bool useSoftwareSerial, uint8_t softwareRXPin, uint8_t softwareTXPin)
{
	_useSoftwareSerial = useSoftwareSerial;
	if (_useSoftwareSerial)
	{
		_serialStream = new SoftwareSerial(softwareRXPin, softwareTXPin);
		((SoftwareSerial*)_serialStream)->begin(baudRate);
	}
	else
	{
		_serialStream = &Serial;
		((HardwareSerial*)_serialStream)->begin(baudRate);
	}
}

BrailleBluetooth::~BrailleBluetooth()
{
	if (_useSoftwareSerial)
	{
		delete(_serialStream);
		_serialStream = 0;
	}
}

void BrailleBluetooth::sendKeyboardState(uint8_t modifiers, uint8_t * keysPressed)
{
	_serialStream->write((uint8_t)0xFD);
	_serialStream->write((uint8_t)0x09); //keyboard length
	_serialStream->write((uint8_t)0x01); //descriptor
	_serialStream->write(modifiers); 
	_serialStream->write((uint8_t)0x00);
	for (uint8_t i = 0; i < MAX_KEYS_PRESSED; ++i)
	{
		_serialStream->write(keysPressed[i]);
		//Serial.println(keysPressed[i]);
		keysPressed[i] = 0x00;
	}
	modifiers = (uint8_t)0x00;
	//Release key manualy
	_serialStream->write((uint8_t)0xFD);
	_serialStream->write((uint8_t)0x09);
	_serialStream->write((uint8_t)0x01);
	_serialStream->write(modifiers);
	_serialStream->write((uint8_t)0x00);
	for (uint8_t i = 0; i < MAX_KEYS_PRESSED; ++i)
	{
		_serialStream->write(keysPressed[i]);
	}
}

void BrailleBluetooth::getKeyboardLEDState()
{
	_serialStream->write((uint8_t)0xFF);
	_serialStream->write((uint8_t)0x02);

	//TODO
	//what to read from BT device?
}
