#ifndef KEYPAD_INPUTGETTER_H
#define KEYPAD_INPUTGETTER_H

#include <gambatte.h>

namespace gambatte {

	class KeypadInputGetter : public InputGetter {
	public:
		KeypadInputGetter();
		virtual unsigned getState(int lane);
	};

}

#endif
