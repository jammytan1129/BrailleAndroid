#include "BrailleKeyboard.h"
#include "BrailleKeyboardCodes.h"
#include "BTKeyCodes.h"

BrailleKeyboard::BrailleKeyboard(){
	_BTKeyCodes = BTKC_NONE;
	_BTModifiers = BTKC_NONE;
	_previousCode = NULL;
	_isNumber = _isSS4 = _isSS5 = _isSS45 = _isSS46 = _isSS456 = false;
	_isCapital = 0;
	for (uint8_t i = 0; i < MAX_KEYS_PRESSED; ++i)
		_keyPressed[i] = BTKC_NONE;
}

BrailleKeyboard::~BrailleKeyboard(){};

bool BrailleKeyboard::available(char* dots, uint8_t extend){
	_BTModifiers = BTKC_NONE;
	
	if(extend == BKC_RETURN){
		_BTKeyCodes = BTKC_RETURN;
		_BTModifiers = BTKC_NONE;
		_isNumber = _isSS4 = _isSS5 = _isSS45 = _isSS46 = _isSS456 = false;
		_isCapital = 0;
		return true;
	}
	if(extend == BKC_SPACE){
		_BTKeyCodes = BTKC_SPACE;
		_BTModifiers = BTKC_NONE;
		_isNumber = _isSS4 = _isSS5 = _isSS45 = _isSS46 = _isSS456 = false;
		_isCapital = 0;
		return true;
	}
	if(extend == BKC_BACKSPACE){
		_BTKeyCodes = BTKC_BACKSPACE;
		return true;
	}
	if(!strcmp(dots, BTKC_NONE)){
		return false;
	}
	return readCodes(dots);
}

uint8_t * BrailleKeyboard::getKeysPressed(){
	/*int8_t btCodeIndex = -1;
		int8_t nextAvailableSlot = -1;
		for (uint8_t i = 0; i < MAX_KEYS_PRESSED; ++i)
		{
			if (_keyPressed[i] == _BTKeyCodes)
			{
				btCodeIndex = i;
			}
			if (_keyPressed[i] == BTKC_NONE)
			{
				nextAvailableSlot = i;
			}
		}

		//if is pressed and not already in _keyPressed, then add to _keyPressed
		if (btCodeIndex == -1 && nextAvailableSlot !=-1)
		{
			_keyPressed[nextAvailableSlot] = _BTKeyCodes;
		}

		//else if is released and is in _keyPressed, then remove it from _keyPressed
		else if (btCodeIndex != -1)
		{
			_keyPressed[btCodeIndex] = BTKC_NONE;
		}*/
		_keyPressed[0]=_BTKeyCodes;
	return _keyPressed;
}

uint8_t BrailleKeyboard::getBTCodes(){
	return _BTKeyCodes;
}

uint8_t BrailleKeyboard::getBTModifiers(){
	return _BTModifiers;
}

bool BrailleKeyboard::readCodes(char* dots){
	//Serial.println(dots);
	if(check(dots)){
		if(_isNumber){ //if is number code, the next inputs are numbers. 
			_isNumber = false;
			return findNumber(dots);
		}
		else if(_isSS4){
			return findSign4(dots);
		}
		else if(_isSS5){
			return findSign5(dots);
		}
		else if(_isSS45){
			return findSign45(dots);
		}
		else if(_isSS46){
			return findSign46(dots);
		}
		else if(_isSS456){
			return findSign456(dots);
		}
		else return findAlphabets(dots);
	}
	else return false;
}

void BrailleKeyboard::startTimeoutCtr(){
	_timeoutStartCtr = micros();
	_timedOut = false;
}

bool BrailleKeyboard::hasTimedOut(uint64_t usecsToTimeOut){
	uint64_t deltaTime = micros() - _timeoutStartCtr;
	if (deltaTime > usecsToTimeOut)
	{
		_timedOut = true;
		return true;
	}

	return false;
}

bool BrailleKeyboard::check(char* dots){
	if(!strcmp(dots,BKC_NUMBER)){ //if is number code, read the next inputs.
		_isNumber = true;
		_isCapital = 0;
		_isSS4 = _isSS5 = _isSS45 = _isSS46 = _isSS456 = false;
		return false;
	}
	if(!strcmp(dots,BKC_CAPITAL)){ //if pressed twice, the whole words will be in capital letters
		_isCapital += 1;			
		_isNumber = _isSS4 = _isSS5 = _isSS45 = _isSS46 = _isSS456 = false;
		return false;
	}
	if(!strcmp(dots,BKCSS_4)){ //for some signs
		_isSS4 = true;
		_isCapital = 0;
		_isNumber = _isSS5 = _isSS45 = _isSS46 = _isSS456 = false;
		return false;
	}
	if(!strcmp(dots,BKCSS_5)){ //for some signs
		_isSS5 = true;
		_isCapital = 0;
		_isNumber = _isSS4 = _isSS45 = _isSS46 = _isSS456 = false;
		return false;
	}
	if(!strcmp(dots,BKCSS_45)){ //for some signs
		_isSS45 = true;
		_isCapital = 0;
		_isNumber = _isSS5 = _isSS4 = _isSS46 = _isSS456 = false;
		return false;
	}
	if(!strcmp(dots,BKCSS_46)){ //for some signs
		_isSS46 = true;
		_isCapital = 0;
		_isNumber = _isSS5 = _isSS45 = _isSS4 = _isSS456 = false;
		return false;
	}
	if(!strcmp(dots,BKCSS_456)){ //for some signs
		_isSS456 = true;
		_isCapital = 0;
		_isNumber = _isSS5 = _isSS45 = _isSS46 = _isSS4 = false;
		return false;
	}
	return true;
}

bool BrailleKeyboard::findNumber(char* dots){
	if(!strcmp(dots,BKC_1)){
		_BTKeyCodes = BTKC_1;
		return true;
	}
	if(!strcmp(dots,BKC_2)){
		_BTKeyCodes = BTKC_2;
		return true;
	}
	if(!strcmp(dots,BKC_3)){
		_BTKeyCodes = BTKC_3;
		return true;
	}
	if(!strcmp(dots,BKC_4)){
		_BTKeyCodes = BTKC_4;
		return true;
	}
	if(!strcmp(dots,BKC_5)){
		_BTKeyCodes = BTKC_5;
		return true;
	}
	if(!strcmp(dots,BKC_6)){
		_BTKeyCodes = BTKC_6;
		return true;
	}
	if(!strcmp(dots,BKC_7)){
		_BTKeyCodes = BTKC_7;
		return true;
	}
	if(!strcmp(dots,BKC_8)){
		_BTKeyCodes = BTKC_8;
		return true;
	}
	if(!strcmp(dots,BKC_9)){
		_BTKeyCodes = BTKC_9;
		return true;
	}
	if(!strcmp(dots,BKC_0)){
		_BTKeyCodes = BTKC_0;
		return true;
	}
	return false;
}

bool BrailleKeyboard::findSign4(char* dots){
	if(!strcmp(dots,BKC_AMPERSAND)){ // &
		_BTKeyCodes = BTKC_7;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS4 = false;
		return true;
	}
	if(!strcmp(dots,BKC_BRACKET_OPEN)){ // <
		_BTKeyCodes = BTKC_COMMA;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS4 = false;
		return true;
	}
	if(!strcmp(dots,BKC_BRACKET_CLOSE)){ // >
		_BTKeyCodes = BTKC_PERIOD;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS4 = false;
		return true;
	}
	if(!strcmp(dots,BKC_AT)){ // @
		_BTKeyCodes = BTKC_2;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS4 = false;
		return true;
	}
	if(!strcmp(dots,BKC_DOLLAR)){ //$
		_BTKeyCodes = BTKC_4;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS4 = false;
		return true;
	}
	if(!strcmp(dots,BKC_TILDE)){ // ~
		_BTKeyCodes = BTKC_GRAVE;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS4 = false;
		return true;
	}
	return false;
}

bool BrailleKeyboard::findSign5(char* dots){
	if(!strcmp(dots,BKC_ASTERISK)){ // *
		_BTKeyCodes = BTKC_8;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS5 = false;
		return true;
	}
	if(!strcmp(dots,BKC_BRACKET_OPEN)){ // (
		_BTKeyCodes = BTKC_9;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS5 = false;
		return true;
	}
	if(!strcmp(dots,BKC_BRACKET_CLOSE)){ // )
		_BTKeyCodes = BTKC_0;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS5 = false;
		return true;
	}
	if(!strcmp(dots,BKC_MINUS)){ // -
		_BTKeyCodes = BTKC_MINUS;
		_isSS5 = false;
		return true;
	}
	if(!strcmp(dots,BKC_PLUS)){ //+
		_BTKeyCodes = BTKC_EQUAL;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS5 = false;
		return true;
	}
	if(!strcmp(dots,BKC_EQUAL)){ // =
		_BTKeyCodes = BTKC_EQUAL;
		_isSS5 = false;
		return true;
	}
	return false;
}

bool BrailleKeyboard::findSign456(char* dots){
	if(!strcmp(dots,BKC_VERTICAL_LINE)){ // |
		_BTKeyCodes = BTKC_BACKSLASH;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS456 = false;
		return true;
	}
	if(!strcmp(dots,BKC_BRACKET_OPEN)){ // {
		_BTKeyCodes = BTKC_BRACKET_LEFT;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS456 = false;
		return true;
	}
	if(!strcmp(dots,BKC_BRACKET_CLOSE)){ // }
		_BTKeyCodes = BTKC_BRACKET_RIGHT;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS456 = false;
		return true;
	}
	if(!strcmp(dots,BKC_BACKSLASH)){ // \ 
		_BTKeyCodes = BTKC_BACKSLASH;
		_isSS456 = false;
		return true;
	}
	if(!strcmp(dots,BKC_CROSSHATCH)){ // #
		_BTKeyCodes = BTKC_3;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS456 = false;
		return true;
	}
	if(!strcmp(dots,BKC_SLASH)){ // /
		_BTKeyCodes = BTKC_SLASH;
		_isSS456 = false;
		return true;
	}
	return false;
}

bool BrailleKeyboard::findSign46(char* dots){
	if(!strcmp(dots,BKC_PERCENT)){ // %
		_BTKeyCodes = BTKC_5;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS46 = false;
		return true;
	}
	if(!strcmp(dots,BKC_BRACKET_OPEN)){ // [
		_BTKeyCodes = BTKC_BRACKET_LEFT;
		_isSS46 = false;
		return true;
	}
	if(!strcmp(dots,BKC_BRACKET_CLOSE)){ // ]
		_BTKeyCodes = BTKC_BRACKET_RIGHT;
		_isSS46 = false;
		return true;
	}
	if(!strcmp(dots,BKC_LOWLINE)){ //_
		_BTKeyCodes = BTKC_MINUS;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS46 = false;
		return true;
	}
	return false;
}

bool BrailleKeyboard::findSign45(char* dots){
	if(!strcmp(dots,BKC_QUOTE_OPEN)){ // "
		_BTKeyCodes = BTKC_APOSTROPHE;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS45 = false;
		return true;
	}
	if(!strcmp(dots,BKC_QUOTE_CLOSE)){ // "
		_BTKeyCodes = BTKC_APOSTROPHE;
		_BTModifiers = BTKC_MODIFIERS;
		_isSS45 = false;
		return true;
	}
	if(!strcmp(dots,BKC_GRAVE)){ // `
		_BTKeyCodes = BTKC_GRAVE;
		_isSS45 = false;
		return true;
	}
	return false;
}

bool BrailleKeyboard::findAlphabets(char* dots){
	if(!strcmp(dots,BKC_A)){
		_BTKeyCodes = BTKC_A;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_B)){
		_BTKeyCodes = BTKC_B;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_C)){
		_BTKeyCodes = BTKC_C;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_D)){
		_BTKeyCodes = BTKC_D;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_E)){
		_BTKeyCodes = BTKC_E;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_F)){
		_BTKeyCodes = BTKC_F;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_G)){
		_BTKeyCodes = BTKC_G;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_H)){
		_BTKeyCodes = BTKC_H;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_I)){
		_BTKeyCodes = BTKC_I;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_J)){
		_BTKeyCodes = BTKC_J;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_K)){
		_BTKeyCodes = BTKC_K;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_L)){
		_BTKeyCodes = BTKC_L;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_M)){
		_BTKeyCodes = BTKC_M;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_N)){
		_BTKeyCodes = BTKC_N;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_O)){
		_BTKeyCodes = BTKC_O;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_P)){
		_BTKeyCodes = BTKC_P;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_Q)){
		_BTKeyCodes = BTKC_Q;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_R)){
		_BTKeyCodes = BTKC_R;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_S)){
		_BTKeyCodes = BTKC_S;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_T)){
		_BTKeyCodes = BTKC_T;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_U)){
		_BTKeyCodes = BTKC_U;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_V)){
		_BTKeyCodes = BTKC_V;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_W)){
		_BTKeyCodes = BTKC_W;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_X)){
		_BTKeyCodes = BTKC_X;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_Y)){
		_BTKeyCodes = BTKC_Y;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_Z)){
		_BTKeyCodes = BTKC_Z;
		if(_isCapital>0){
			_BTModifiers = BTKC_MODIFIERS;
			if(_isCapital == 1) _isCapital = 0;
		}
		return true;
	}
	if(!strcmp(dots,BKC_COMMA)){ //,
		_BTKeyCodes = BTKC_COMMA;
		return true;
	}
	if(!strcmp(dots,BKC_PERIOD)){ //.
		_BTKeyCodes = BTKC_PERIOD;
		return true;
	}
	if(!strcmp(dots,BKC_SEMICOLON)){ //;
		_BTKeyCodes = BTKC_SEMICOLON;
		return true;
	}
	if(!strcmp(dots,BKC_APOSTROPHE)){ //'
		_BTKeyCodes = BTKC_APOSTROPHE;
		return true;
	}
	if(!strcmp(dots,BKC_QUESTION)){ // ?
		_BTKeyCodes = BTKC_SLASH;
		_BTModifiers = BTKC_MODIFIERS;
		return true;
	}
	if(!strcmp(dots,BKC_EXCLAMATION)){ // !
		_BTKeyCodes = BTKC_1;
		_BTModifiers = BTKC_MODIFIERS;
		return true;
	}
	if(!strcmp(dots,BKC_COLON)){ //:
		_BTKeyCodes = BTKC_SEMICOLON;
		_BTModifiers = BTKC_MODIFIERS;
		return true;
	}
	return false;
}