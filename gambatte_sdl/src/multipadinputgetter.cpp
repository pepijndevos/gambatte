#include "multipadinputgetter.h"

namespace gambatte {

	MultipadInputGetter::getState(int lane) {
		unsigned result = 0;

		for (int i = 0; i < inputs_.size(); i++) {
			result |= inputs_[i]->getState(lane);
		}
	}

}