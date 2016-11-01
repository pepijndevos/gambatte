#ifndef MULTIPAD_INPUTGETTER_H
#define MULTIPAD_INPUTGETTER_H

#include <gambatte.h>

namespace gambatte {

	class MultipadInputGetter : public InputGetter {
	public:
		MultipadInputGetter(std::vector<InputGetter*> inputs) {
			inputs_ = inputs;
		}

		virtual ~InputGetter() {}

		virtual unsigned operator()() {
			return 0;
		}

		virtual unsigned getState(int lane);

	private: 
		std::vector<InputGetter*> inputs_;
	};
}

#endif