#include "BrailleSolenoid.h"
#include "BrailleKeyboardCodes.h"
#include "BTKeyCodes.h"

BrailleSolenoid::BrailleSolenoid(){
	_textSize = 0;
	_currentLocation = 0;
	_preLocation = 0;
	_nextLocation = 0;
	_isOpened = false;
	_isCapital = false;
	_isPunct = false;
	_isNumber = false;
}

BrailleSolenoid::~BrailleSolenoid(){};

char* BrailleSolenoid::getPrintCode(){
	return _printCode;
}

void BrailleSolenoid::startTimeoutCtr(){
	_timeoutStartCtr = micros();
	_timedOut = false;
}

bool BrailleSolenoid::hasTimedOut(){
	uint64_t deltaTime = micros() - _timeoutStartCtr;
	if (deltaTime > TIMEOUT_WAIT)
	{
		_timedOut = true;
		return true;
	}
	return false;
}

bool BrailleSolenoid::determine(String str){
 	strcpy(_buffer,string2char(str));
 	_isOpened = false;
	_isCapital = false;
	_isPunct = false;
	_isNumber = false;
	strcpy(_nextCode, BKC_NULL);
	strcpy(_preCode, BKC_NULL);
	strcpy(_currentWord, BKC_NULL);
	strcpy(_printCode, BKC_NULL);
	_currentLocation = -1;
// 	_preLocation = _currentLocation;
// 	_nextLocation = _currentLocation+1;
	return next();
}

char* BrailleSolenoid::string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}

bool BrailleSolenoid::next(){
	_preLocation = _currentLocation;
	_currentLocation = _currentLocation+1;
	_nextLocation = _currentLocation+1;
	if(_currentLocation >= (sizeof(_buffer)-1)) {
		_currentLocation = _currentLocation-1;
		_nextLocation = _currentLocation-1;
		//Serial.println("here");
	}
	//Serial.println(sizeof(_buffer));
	
	//Serial.println(_buffer[_currentLocation]);
	bool s = search(_buffer[_currentLocation]);
	
	if(strcmp(_preCode, BKC_NULL)){
		strcpy(_printCode, _preCode);
		strcpy(_preCode, _nextCode);
		strcpy(_nextCode, BKC_NULL);
		_currentLocation = _preLocation;
		_nextLocation = _currentLocation+1;
		return true;
	}
	
	if(strcmp(_currentWord, BKC_NULL)){
		strcpy(_printCode, _currentWord);
		strcpy(_currentWord, BKC_NULL);
		return true;
	}
	return false;
}

bool BrailleSolenoid::previous(){
	_preLocation = _currentLocation;
	if(_currentLocation > 0){
		_currentLocation = _currentLocation-1;
		_nextLocation = _currentLocation+1;
	}                                                                                                                                                                              
	bool s = search(_buffer[_currentLocation]);
	
	if(strcmp(_preCode, BKC_NULL)){
		strcpy(_printCode, _preCode);
		strcpy(_preCode, _nextCode);
		strcpy(_nextCode, BKC_NULL);
		_currentLocation = _preLocation;
		_nextLocation = _currentLocation+1;
		return true;
	}
	if(strcmp(_currentWord, BKC_NULL)){
		strcpy(_printCode, _currentWord);
		strcpy(_currentWord, BKC_NULL);
		return true;
	}
	return false;
}

bool BrailleSolenoid::search(char buffer){
	if(isDigit(buffer)){
		_isCapital = false;
		return searchDigit(buffer);
	}
	if(isAlpha(buffer)){
		return searchAlpha(buffer);
	}
	if(isPunct(buffer)){
		_isCapital = false;
	 	return searchPunct(buffer);
	}
	if(isSpace(buffer)){
		_isCapital = false;
		_isNumber = false;
	 	strcpy(_printCode, BKC_SPACEBAR);
		return true;
	}
	return false;
}

bool BrailleSolenoid::searchDigit(char buffer){
	if(!_isNumber)strcpy(_preCode, BKC_NUMBER);
	_isNumber = true;
	if(buffer == '1'){
		strcpy(_currentWord, BKC_1);
		return true;
	}
	if(buffer == '2'){
		strcpy(_currentWord, BKC_2);
		return true;
	}
	if(buffer == '3'){
		strcpy(_currentWord, BKC_3);
		return true;
	}
	if(buffer == '4'){
		strcpy(_currentWord, BKC_4);
		return true;
	}
	if(buffer == '5'){
		strcpy(_currentWord, BKC_5);
		return true;
	}
	if(buffer == '6'){
		strcpy(_currentWord, BKC_6);
		return true;
	}
	if(buffer == '7'){
		strcpy(_currentWord, BKC_7);
		return true;
	}
	if(buffer == '8'){
		strcpy(_currentWord, BKC_8);
		return true;
	}
	if(buffer == '9'){
		strcpy(_currentWord, BKC_9);
		return true;
	}
	if(buffer == '0'){
		strcpy(_currentWord, BKC_0);
		return true;
	}
	return false;
}

bool BrailleSolenoid::searchAlpha(char buffer){
	if(_isNumber){
		strcpy(_preCode, BKC_SPACEBAR);
// 		_currentLocation = _preLocation; // 思考這項
		_isNumber = false;
// 		Serial.println(_preCode);
		return true;
	}
	Serial.println(buffer);//comment
	if(isUpperCase(buffer) && !_isCapital){
		strcpy(_preCode, BKC_CAPITAL);
		_isCapital = true;
		if(isUpperCase(_buffer[_nextLocation])){
			strcpy(_nextCode, BKC_CAPITAL);
		}
	}
	if(isLowerCase(buffer) && _isCapital){
		_isCapital = false;
		strcpy(_preCode, BKC_SPACEBAR);
	}
	if(buffer == 'a' || buffer == 'A'){
		strcpy(_currentWord, BKC_A);
		return true;
	}
	if(buffer == 'b' || buffer == 'B'){
		strcpy(_currentWord, BKC_B);
		return true;
	}
	if(buffer == 'c' || buffer == 'C'){
		strcpy(_currentWord, BKC_C);
		return true;
	}
	if(buffer == 'd' || buffer == 'D'){
		strcpy(_currentWord, BKC_D);
		return true;
	}
	if(buffer == 'e' || buffer == 'E'){
		strcpy(_currentWord, BKC_E);
		return true;
	}
	if(buffer == 'f' || buffer == 'F'){
		strcpy(_currentWord, BKC_F);
		return true;
	}
	if(buffer == 'g' || buffer == 'G'){
		strcpy(_currentWord, BKC_G);
		return true;
	}
	if(buffer == 'h' || buffer == 'H'){
		strcpy(_currentWord, BKC_H);
		return true;
	}
	if(buffer == 'i' || buffer == 'I'){
		strcpy(_currentWord, BKC_I);
		return true;
	}
	if(buffer == 'j' || buffer == 'J'){
		strcpy(_currentWord, BKC_J);
		return true;
	}
	if(buffer == 'k' || buffer == 'K'){
		strcpy(_currentWord, BKC_K);
		return true;
	}
	if(buffer == 'l' || buffer == 'L'){
		strcpy(_currentWord, BKC_L);
		return true;
	}
	if(buffer == 'm' || buffer == 'M'){
		strcpy(_currentWord, BKC_M);
		return true;
	}
	if(buffer == 'n' || buffer == 'N'){
		strcpy(_currentWord, BKC_N);
		return true;
	}
	if(buffer == 'o' || buffer == 'O'){
		strcpy(_currentWord, BKC_O);
		return true;
	}
	if(buffer == 'p' || buffer == 'P'){
		strcpy(_currentWord, BKC_P);
		return true;
	}
	if(buffer == 'q' || buffer == 'Q'){
		strcpy(_currentWord, BKC_Q);
		return true;
	}
	if(buffer == 'r' || buffer == 'R'){
		strcpy(_currentWord, BKC_R);
		return true;
	}
	if(buffer == 's' || buffer == 'S'){
		strcpy(_currentWord, BKC_S);
		return true;
	}
	if(buffer == 't' || buffer == 'T'){
		strcpy(_currentWord, BKC_T);
		return true;
	}
	if(buffer == 'u' || buffer == 'U'){
		strcpy(_currentWord, BKC_U);
		return true;
	}
	if(buffer == 'v' || buffer == 'V'){
		strcpy(_currentWord, BKC_V);
		return true;
	}
	if(buffer == 'w' || buffer == 'W'){
		strcpy(_currentWord, BKC_W);
		return true;
	}
	if(buffer == 'x' || buffer == 'X'){
		strcpy(_currentWord, BKC_X);
		return true;
	}
	if(buffer == 'y' || buffer == 'Y'){
		strcpy(_currentWord, BKC_Y);
		return true;
	}
	if(buffer == 'z' || buffer == 'Z'){
		strcpy(_currentWord, BKC_Z);
		return true;
	}
	return false;
}

bool BrailleSolenoid::searchPunct(char buffer){
	if(_isNumber){
		strcpy(_preCode, BKC_SPACEBAR);
// 		_currentLocation = _preLocation;
		_isNumber = false;
		return true;
	}
	//Special code
	if((buffer == '&' || buffer == '<' || buffer == '>' || buffer == '@' || buffer == '$' || buffer == '~') && !_isPunct){
		strcpy(_preCode, BKCSS_4);
		_isPunct = true;
		return true;
	}
	if((buffer == '*' || buffer == '(' || buffer == ')' || buffer == '-' || buffer == '+' || buffer == '=') && !_isPunct){
		strcpy(_preCode, BKCSS_5);
		_isPunct = true;
		return true;
	}
	if((buffer == '\\' || buffer == '/' || buffer == '{' || buffer == '}' || buffer == '#' || buffer == '|') && !_isPunct){
		strcpy(_preCode, BKCSS_456);
		_isPunct = true;
		return true;
	}
	if((buffer == '[' || buffer == ']' || buffer == '%' || buffer == '_') && !_isPunct){
		strcpy(_preCode, BKCSS_46);
		_isPunct = true;
		return true;
	}
	if((buffer == '"' || buffer == '`') && !_isPunct){
		strcpy(_preCode, BKCSS_45);
		_isPunct = true;
		return true;
	}
	
	//signs
	if(buffer == ','){
		strcpy(_currentWord, BKC_COMMA);
		_isPunct = false;
		return true;
	}
	if(buffer == '.'){
		strcpy(_currentWord, BKC_PERIOD);
		_isPunct = false;
		return true;
	}
	if(buffer == ';'){
		strcpy(_currentWord, BKC_SEMICOLON);
		_isPunct = false;
		return true;
	}
	if(buffer == '\''){
		strcpy(_currentWord, BKC_APOSTROPHE);
		_isPunct = false;
		return true;
	}
	if(buffer == '\\'){
		strcpy(_currentWord, BKC_BACKSLASH);
		_isPunct = false;
		return true;
	}
	if(buffer == '/'){
		strcpy(_currentWord, BKC_SLASH);
		_isPunct = false;
		return true;
	}
	if(buffer == '-'){
		strcpy(_currentWord, BKC_MINUS);
		_isPunct = false;
		return true;
	}
	if(buffer == '='){
		strcpy(_currentWord, BKC_EQUAL);
		_isPunct = false;
		return true;
	}
	if(buffer == '`'){
		strcpy(_currentWord, BKC_GRAVE);
		_isPunct = false;
		return true;
	}
	if(buffer == '?'){
		strcpy(_currentWord, BKC_QUESTION);
		_isPunct = false;
		return true;
	}
	if(buffer == '!'){
		strcpy(_currentWord, BKC_EXCLAMATION);
		_isPunct = false;
		return true;
	}
	if(buffer == ':'){
		strcpy(_currentWord, BKC_COLON);
		_isPunct = false;
		return true;
	}
	if(buffer == '"'){
		_isPunct = false;
		if(_isOpened){
			strcpy(_currentWord, BKC_QUOTE_CLOSE);
			_isOpened = false;
			return true;
		}
		strcpy(_currentWord, BKC_QUOTE_OPEN);
		_isOpened = true;
		return true;
	}
	if(buffer == '&'){
		strcpy(_currentWord, BKC_AMPERSAND);
		_isPunct = false;
		return true;
	}
	if(buffer == '(' || buffer == '[' || buffer == '{' || buffer == '<'){
		strcpy(_currentWord, BKC_BRACKET_OPEN);
		_isPunct = false;
		return true;
	}
	if(buffer == ')' || buffer == ']' || buffer == '}' || buffer == '>'){
		strcpy(_currentWord, BKC_BRACKET_CLOSE);
		_isPunct = false;
		return true;
	}
	if(buffer == '*'){
		strcpy(_currentWord, BKC_ASTERISK);
		_isPunct = false;
		return true;
	}
	if(buffer == '@'){
		strcpy(_currentWord, BKC_AT);
		_isPunct = false;
		return true;
	}
	if(buffer == '#'){
		strcpy(_currentWord, BKC_CROSSHATCH);
		_isPunct = false;
		return true;
	}
	if(buffer == '|'){
		strcpy(_currentWord, BKC_VERTICAL_LINE);
		_isPunct = false;
		return true;
	}
	if(buffer == '~'){
		strcpy(_currentWord, BKC_TILDE);
		_isPunct = false;
		return true;
	}
	if(buffer == '$'){
		strcpy(_currentWord, BKC_DOLLAR);
		_isPunct = false;
		return true;
	}
	if(buffer == '%'){
		strcpy(_currentWord, BKC_PERCENT);
		_isPunct = false;
		return true;
	}
	if(buffer == '_'){
		strcpy(_currentWord, BKC_LOWLINE);
		_isPunct = false;
		return true;
	}
	if(buffer == '+'){
		strcpy(_currentWord, BKC_PLUS);
		_isPunct = false;
		return true;
	}
	return false;
}
