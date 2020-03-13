#ifndef BRAILLEKEYBOARDCODES_H
#define BRAILLEKEYBOARDCODES_H

#define MAX_KEYS_PRESSED 6

//Modifiers
#define BTKC_MODIFIERS 0x02

//Extend
#define BKC_RETURN 1
#define BKC_SPACE 2
#define BKC_BACKSPACE 3

//Alphabets
#define BKC_A "100000"
#define BKC_B "110000"
#define BKC_C "100100"
#define BKC_D "100110"
#define BKC_E "100010"
#define BKC_F "110100"
#define BKC_G "110110"
#define BKC_H "110010"
#define BKC_I "010100"
#define BKC_J "010110"
#define BKC_K "101000"
#define BKC_L "111000"
#define BKC_M "101100"
#define BKC_N "101110"
#define BKC_O "101010"
#define BKC_P "111100"
#define BKC_Q "111110"
#define BKC_R "111010"
#define BKC_S "011100"
#define BKC_T "011110"
#define BKC_U "101001"
#define BKC_V "111001"
#define BKC_W "010111"
#define BKC_X "101101"
#define BKC_Y "101111"
#define BKC_Z "101011"

//Numbers
#define BKC_NUMBER "001111"
#define BKC_0 "010110"
#define BKC_1 "100000"
#define BKC_2 "110000"
#define BKC_3 "100100"
#define BKC_4 "100110"
#define BKC_5 "100010"
#define BKC_6 "110100"    
#define BKC_7 "110110"
#define BKC_8 "110010"
#define BKC_9 "010100"
//Signs
#define BKC_COMMA "010000" // ,
#define BKC_PERIOD "010011" // .
#define BKC_SEMICOLON "011000" // ;
#define BKC_APOSTROPHE "001000"  // '
#define BKC_BACKSLASH "100001" // \ ss: 456
#define BKC_SLASH "001100" // / ss: 456
#define BKC_MINUS "001001" // - ss: 5
#define BKC_EQUAL "011011" // = ss: 5
#define BKC_GRAVE "100001" // + ss: 45

//require modifiers
#define BKC_QUESTION "011001"  // ? 
#define BKC_EXCLAMATION "011010" // ! 
#define BKC_COLON "010010" // : 
#define BKC_QUOTE_OPEN "011001" // " ss: 45
#define BKC_QUOTE_CLOSE "001011" // " ss:45
#define BKC_AMPERSAND "111101" // & ss: 4
#define BKC_BRACKET_OPEN "110001" // {[(<,, ss: 4,5,46,456, [] does not need modifiers
#define BKC_BRACKET_CLOSE "001110" // }])> ss: same as above
#define BKC_ASTERISK "001010" // * ss: 5
#define BKC_AT "100000" // @ ss: 4
#define BKC_CROSSHATCH "100111" // # ss: 456
#define BKC_VERTICAL_LINE "110011" // |  ss: 456
#define BKC_TILDE "001010" // ~ ss: 4
#define BKC_DOLLAR "011100" // $ ss: 4
#define BKC_PERCENT "001011" // % ss: 46
#define BKC_LOWLINE "001001" // _ ss: 46
#define BKC_PLUS "011010" // + ss: 5

//Special signs
#define BKCSS_4 "000100" //ampersand & ,angle bracket < > , AT @, dollar $, tilde ~
#define BKCSS_5 "000010" //asterisk *, round bracket ( ), minus - , plus + , equal =
#define BKCSS_456 "000111" //backslash \, slash / ,curly bracket {}, crosshatch #, vertical line |
#define BKCSS_46 "000101" //square bracket[], percent %, low line _  
#define BKCSS_45 "000110" // quote open/close "", grave `
#define BKC_CAPITAL "000001" // capital letter

#endif //BRAILLEKEYBOARDCODES_H
