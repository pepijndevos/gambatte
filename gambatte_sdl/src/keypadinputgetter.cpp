#include "keypadinputgetter.h"
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define PIN_B_OR_LEFT 		0
#define PIN_SELECT_OR_UP 	1 
#define PIN_START_OR_DOWN 	2
#define PIN_A_OR_RIGHT 		3

#define PIN_LANE_0 			4
#define PIN_LANE_1 			5


namespace gambatte {

KeypadInputGetter::KeypadInputGetter() {
	wiringPiSetup();

	pinMode(PIN_B_OR_LEFT, INPUT);
	pinMode(PIN_SELECT_OR_UP, INPUT);
	pinMode(PIN_START_OR_DOWN, INPUT);
	pinMode(PIN_A_OR_RIGHT, INPUT);

	pinMode(PIN_LANE_0, OUTPUT);
	pinMode(PIN_LANE_1, OUTPUT);

	digitalWrite(PIN_LANE_0, HIGH);
	digitalWrite(PIN_LANE_1, LOW);
}

unsigned KeypadInputGetter::getState(int lane) {
	unsigned result = 0;
	if (lane == 1) {
	        digitalWrite(PIN_LANE_0, HIGH);
        	digitalWrite(PIN_LANE_1, LOW);
	} else if (lane == 0) {
                digitalWrite(PIN_LANE_0, LOW);
                digitalWrite(PIN_LANE_1, HIGH);
	}
	
//	unsigned int microseconds=100;
//	usleep(microseconds);
	
	
	
	if (digitalRead(PIN_B_OR_LEFT) == LOW) {
		result |= (lane == 1 ? InputGetter::LEFT : InputGetter::B);
	}
        if (digitalRead(PIN_SELECT_OR_UP) == LOW) {
//		printf("SELECT OR UP! (lane=%d) \n", lane);
                result |= (lane == 1 ? InputGetter::UP : InputGetter::SELECT);
        }
        if (digitalRead(PIN_START_OR_DOWN) == LOW) {
//		printf("START OR DOWN! (lane=%d) \n", lane);
                result |= (lane == 1 ? InputGetter::DOWN : InputGetter::START);
        }
        if (digitalRead(PIN_A_OR_RIGHT) == LOW) {
		result |= (lane == 1 ? InputGetter::RIGHT : InputGetter::A);
        }

	return result;
}

//     | D13    | D14
// ----+--------+-----
// D9  | B      | Left
// D10 | Select | Up
// D11 | Start  | Down
// D12 | A      | Right

}


