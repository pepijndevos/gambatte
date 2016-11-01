#ifndef KEYPADINPUTGETTER_H
#define KEYPADINPUTGETTER_H

#include <gambatte.h>

namespace gambatte {

class KeypadInputGetter : public InputGetter {
public:
	KeypadInputGetter();
	~KeypadInputGetter();

//	virtual unsigned operator()();
	virtual unsigned getState(int lane);
private:
	unsigned currentLane_;
};

}
#endif
