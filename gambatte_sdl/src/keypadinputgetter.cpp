#ifndef KEYPADINPUT_H
#define KEYPADINPUT_H

#include "keypadinputgetter.h"
#include <wiringPi.h>

#define PIN_B_OR_LEFT 		0
#define PIN_SELECT_OR_UP 	1 
#define PIN_START_OR_DOWN 	2
#define PIN_A_OR_RIGHT 		0

#define PIN_LANE_0 			4
#define PIN_LANE_1 			5

KeypadInputGetter::KeypadInputGetter() {
	wiringPiSetup();
	
	pinMode(PIN_B_OR_LEFT, INPUT);
	pinMode(PIN_SELECT_OR_UP, INPUT);
	pinMode(PIN_START_OR_DOWN, INPUT);
	pinMode(PIN_A_OR_RIGHT, INPUT);

	pinMode(PIN_LANE_0, OUTPUT);
	pinMode(PIN_LANE_1, OUTPUT);

	digitalWrite(PIN_LANE_0, HIGH);
}

KeypadInputGetter::~KeypadInputGetter() {

}


virtual unsigned KeypadInputGetter::getState(int lane) {
	unsigned result = 0;

	if (lane == 0) {
		digitalWrite(PIN_LANE_0, HIGH);
		digitalWrite(PIN_LANE_1, LOW);
	} else {
		digitalWrite(PIN_LANE_0, LOW);
		digitalWrite(PIN_LANE_1, HIGH);
	}

	if (digitalRead(PIN_B_OR_LEFT) == LOW) {
		result |= (lane ? Button.B : Button.LEFT);
	}

	if (digitalRead(PIN_SELECT_OR_UP) == LOW) {
		result |= (lane ? Button.SELECT : Button.UP);
	}

	if (digitalRead(PIN_START_OR_DOWN) == LOW) {
		result |= (lane ? Button.START : Button.DOWN);
	}

	if (digitalRead(PIN_A_OR_RIGHT) == LOW) {
		result |= (lane ? Button.A: Button.RIGHT);
	}

	return result;
}

//     | D13    | D14
// ----+--------+-----
// D9  | B      | Left
// D10 | Select | Up
// D11 | Start  | Down
// D12 | A      | Right

#endif