#include "BrailleKeyboard.h"
#include "BrailleBluetooth.h"
#define _DEBUG 1

#if _DEBUG
#define HARDWARE_SERIAL_RATE 38400
#else
#define HARDWARE_SERIAL_RATE 115200
#endif
BrailleKeyboard myKeyboard;

#if _DEBUG
#define BLUETOOTH_DEBUG_RX 7  
#define BLUETOOTH_DEBUG_TX 8
#define BLUETOOTH_DEBUG_BAUD 9600
BrailleBluetooth bluetooth(BLUETOOTH_DEBUG_BAUD, true, BLUETOOTH_DEBUG_RX, BLUETOOTH_DEBUG_TX);
#else
BrailleBluetooth bluetooth(HARDWARE_SERIAL_RATE, false, 0, 0);
#endif
#define DOT0 2
#define DOT1 3
#define DOT2 4
#define DOT3 5
#define DOT4 10
#define DOT5 11
//#define RETURN 10
//#define SPACE 11 
//#define BACKSPACE 12
void setup()
{
  Serial.begin(HARDWARE_SERIAL_RATE);
  Serial.println("Setup started");
  pinMode(DOT0, INPUT);
  pinMode(DOT1, INPUT);
  pinMode(DOT2, INPUT);
  pinMode(DOT3, INPUT);
  pinMode(DOT4, INPUT);
  pinMode(DOT5, INPUT);
  //pinMode(RETURN, INPUT);
  //pinMode(SPACE, INPUT);
  //pinMode(BACKSPACE, INPUT);
}

void loop()
{
  char dots[6] = {'0','0','0','0','0','0'};
  uint8_t extend = 0;
  dots[6]='\0';
  int d0, d1, d2, d3, d4, d5, count;
  d0 = d1 = d2 = d3 = d4 = d5 = count = 0;
  while(1){
    d0 = digitalRead(DOT0);
    d1 = digitalRead(DOT1);
    d2 = digitalRead(DOT2);
    d3 = digitalRead(DOT3);
    d4 = digitalRead(DOT4);
    d5 = digitalRead(DOT5);
    if(d0 == HIGH) dots[0] = '1';
    if(d1 == HIGH) dots[1] = '1';
    if(d2 == HIGH) dots[2] = '1';
    if(d3 == HIGH) dots[3] = '1';
    if(d4 == HIGH) dots[4] = '1';
    if(d5 == HIGH) dots[5] = '1';
    //if(ret == HIGH) extend = 1;
    //if(space == HIGH) extend = 2;
    //if(backspace == HIGH) extend = 3;
    if(dots[0]=='1' && dots[1]=='1' && dots[2]=='1' && dots[3]=='1' && dots[4]=='1' && dots[5]=='1')
    {
      delay(300);
      break;
    }
    count++;
    if(count==30000) break; 
  }
  if(myKeyboard.available(dots, extend)){
    bluetooth.sendKeyboardState(myKeyboard.getBTModifiers(), myKeyboard.getKeysPressed());
    //Serial.println(myKeyboard.getBTCodes(),HEX);
    delay(50);
  }
}
