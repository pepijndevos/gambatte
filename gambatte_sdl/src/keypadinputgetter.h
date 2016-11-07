#ifndef KEYPAD_INPUTGETTER_H
#define KEYPAD_INPUTGETTER_H

#include <gambatte.h>
#include <time.h>

namespace gambatte {

	class KeypadInputGetter : public InputGetter {
	public:
		KeypadInputGetter();
		virtual unsigned getState(int lane);

		bool isFreezed() {
			return freezed_;
		}

		void freezeLaneSelect() {
			freezed_ = true;
		}

		void selectLane(int lane) {
			selectedLane_ = lane;
		}

		void unfreezeLaneSelect() {
			freezed_ = false;
		}

	private:
		clock_t start_;
		bool freezed_;
		int selectedLane_;
		int delay_;
	};

}

#endif
