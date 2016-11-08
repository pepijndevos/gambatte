#ifndef KEYPAD_INPUTGETTER_H
#define KEYPAD_INPUTGETTER_H

#include <gambatte.h>
#include <time.h>

namespace gambatte {

	/**
	 * Provides an implementation for an input getter, receiving 
	 * the input state from a GameBoy keypad.
	 */
	class KeypadInputGetter : public InputGetter {
	public:
		KeypadInputGetter();

		virtual unsigned getState(int lane);
	};

}

#endif
