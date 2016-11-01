#ifndef KEYPADINPUTGETTER_H
#define KEYPADINPUTGETTER_H

#include <inputgetter.h>

class KeypadInputGetter : public InputGetter {
public:
	KeypadInputGetter();
	~KeypadInputGetter();

	virtual unsigned operator()();
private:
	unsigned currentLane_;
}

#endif