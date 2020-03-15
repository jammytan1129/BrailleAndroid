#include "BrailleSolenoid.h"
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
#define BLUETOOTH_DEBUG_RX 8
#define BLUETOOTH_DEBUG_TX 9
#define BLUETOOTH_DEBUG_BAUD 9600
BrailleBluetooth bluetooth(BLUETOOTH_DEBUG_BAUD, true, BLUETOOTH_DEBUG_RX, BLUETOOTH_DEBUG_TX);
#else
BrailleBluetooth bluetooth(HARDWARE_SERIAL_RATE, false, 0, 0);
#endif
#define DOT0 36
#define DOT1 40
#define DOT2 44
#define DOT3 52
#define DOT4 47
#define DOT5 A6
#define RETURN 48
#define SPACE 32 
#define BACKSPACE A8
#define SHIFT 28
BrailleSolenoid solenoid;
#define LEFT 39
#define RIGHT 43
#define S0 2
#define S1 5
#define S2 6
#define S3 3
#define S4 4
#define S5 7
void setup()
{
  Serial.begin(HARDWARE_SERIAL_RATE);
  //Serial.begin(9600);
  Serial.println("Setup started");
  Serial3.begin(19200);
  pinMode(DOT0, INPUT);
  pinMode(DOT1, INPUT);
  pinMode(DOT2, INPUT);
  pinMode(DOT3, INPUT);
  pinMode(DOT4, INPUT);
  pinMode(DOT5, INPUT);
  pinMode(RETURN, INPUT);
  pinMode(SPACE, INPUT);
  pinMode(BACKSPACE, INPUT);
   pinMode(SHIFT, INPUT);
    pinMode(LEFT, INPUT);
   pinMode(RIGHT, INPUT);
   pinMode(S0,OUTPUT);
   pinMode(S1,OUTPUT);
   pinMode(S2,OUTPUT);
   pinMode(S3,OUTPUT);
   pinMode(S4,OUTPUT);
   pinMode(S5,OUTPUT);
}
String str;
String text = " ";
String pre = " ";
char output[7] = {'1','1','1','1','1','1','\0'};
void loop()
{
  BT();
  char dots[7] = {'0','0','0','0','0','0','\0'};
  uint8_t extend = 0;
//  dots[6]='\0';
  int d0, d1, d2, d3, d4, d5, count, ret, space, backspace, shift, left, right;
  d0 = d1 = d2 = d3 = d4 = d5  = count = ret = space = backspace = shift = left = right = 0;
  while(1){
    d0 = digitalRead(DOT0);
    d1 = digitalRead(DOT1);
    d2 = digitalRead(DOT2);
    d3 = digitalRead(DOT3);
    d4 = digitalRead(DOT4);
    d5 = digitalRead(DOT5);
    ret = digitalRead(RETURN);
    space = digitalRead(SPACE);
    backspace = digitalRead(BACKSPACE);
    shift = digitalRead(SHIFT);
    left = digitalRead(LEFT);
    right = digitalRead(RIGHT);
    if(d0 == HIGH) dots[0] = '1';
    if(d1 == HIGH) dots[1] = '1';
    if(d2 == HIGH) dots[2] = '1';
    if(d3 == HIGH) dots[3] = '1';
    if(d4 == HIGH) dots[4] = '1';
    if(d5 == HIGH) dots[5] = '1';
    if(ret == HIGH) extend = 1;
    if(space == HIGH) extend = 2;
    if(backspace == HIGH) extend = 3;
    if(shift == HIGH) extend = 4;
    
    if((dots[0]=='1' && dots[1]=='1' && dots[2]=='1' && dots[3]=='1' && dots[4]=='1' && dots[5]=='1')|| extend != 0 || left == HIGH || right == HIGH)
    {
      delay(300);
      break;
    }
    if (Serial3.available()) {
      break;
    }
    count++;
    if(count==26000) break; 
  }
  if(left == HIGH){
    if(solenoid.previous()){
        setSolenoidOff(); 
        strcpy(output,solenoid.getPrintCode());
        solenoid.startTimeoutCtr();
        setSolenoidOn();
        Serial.println(output);
    }
    left = 0;
  }
  if(right == HIGH){
    if(solenoid.next()){
        setSolenoidOff();
        strcpy(output,solenoid.getPrintCode());
        solenoid.startTimeoutCtr();
        setSolenoidOn();
        Serial.println(output);
    }
    right = 0;
  }
  if(myKeyboard.available(dots, extend)){
    bluetooth.sendKeyboardState(myKeyboard.getBTModifiers(), myKeyboard.getKeysPressed());
//    Serial.println(myKeyboard.getBTCodes(),HEX);
    delay(50);
  }
  if(solenoid.hasTimedOut()){
    setSolenoidOff();
  }
}

void BT(){
 if (Serial3.available()) {
    text = Serial3.readString();
     Serial.println(text);
    if(solenoid.determine(text)){
      strcpy(output,solenoid.getPrintCode());
      solenoid.startTimeoutCtr();
      setSolenoidOn();
      Serial.println(output);
    }
  }
}

void setSolenoidOn(){
  if(output[0]=='0')
    digitalWrite(S0,1);
  if(output[1]=='0')
    digitalWrite(S1,1);
  if(output[2]=='0')
    digitalWrite(S2,1);
  if(output[3]=='0')
    digitalWrite(S3,1);
  if(output[4]=='0')
    digitalWrite(S4,1);
  if(output[5]=='0')
    digitalWrite(S5,1);
}
void setSolenoidOff(){
  for(int i=0;i<6;i++)
    output[i] = '1';
  digitalWrite(S0,0);
  digitalWrite(S1,0);
  digitalWrite(S2,0);
  digitalWrite(S3,0);
  digitalWrite(S4,0);
  digitalWrite(S5,0);
}

