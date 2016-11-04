#ifndef MONITOR_LISTENER_H
#define MONITOR_LISTENER_H

#include "video/ppu.h"
#include "memory.h"
#include <stdio.h>
#include <semaphore.h>

namespace gambatte {

class MonitorListener {
public:
	void startListening();

	void waitForHBlank(int line);

	void waitForVBlank();

	void dispatchHBlank();

	void dispatchVBlank();

private:
	sem_t vblankSemaphore;
	sem_t hblankSemaphore;
};

}
#endif
