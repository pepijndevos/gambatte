#ifndef MONITOR_LISTENER_H
#define MONITOR_LISTENER_H

#include "video/ppu.h"
#include "memory.h"
#include <stdio.h>

namespace gambatte {

class MonitorListener {
public:
	//MonitorListener(Memory *memory) {
	//	memory_ = memory;
	//}

	//void update(unsigned long cycleCounter) {
	//	cycleCounter_ = cycleCounter;
	//}

	void startListening();

	void waitForVBlank();

	void dispatchVBlank();

	//unsigned long getCycleCounter() { return cycleCounter_; }

	//Memory* getMemory() { return memory_; }
private:
	bool vblank_;
	//unsigned long cycleCounter_;
	//Memory *memory_;

};

}
#endif
