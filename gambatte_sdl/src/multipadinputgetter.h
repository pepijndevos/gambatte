#ifndef MULTIPAD_INPUTGETTER_H
#define MULTIPAD_INPUTGETTER_H

#include <gambatte.h>
#include <vector>

namespace gambatte {

	/**
	 * Provides an implementation for an input getter, combining
	 * multiple input getters into one.
	 */
	class MultipadInputGetter : public InputGetter {
	public:
		MultipadInputGetter(std::vector<InputGetter*> *inputs) {
			inputs_ = inputs;
		}

		virtual unsigned getState(int lane) {
			unsigned result = 0;
			for (int i = 0; i < inputs_->size(); i++) {
				result |= inputs_->at(i)->getState(lane);
			}
			return result;
		}

	private:
		std::vector<InputGetter*> *inputs_;
	};


}


#endif
