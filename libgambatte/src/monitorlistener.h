#ifndef MONITOR_LISTENER_H
#define MONITOR_LISTENER_H

#include "video/ppu.h"
#include "memory.h"
#include <stdio.h>
#include <semaphore.h>

namespace gambatte {

/**
 * Responsible for listening to events the display dispatches.
 */
class MonitorListener {
public:
	/**
	 * Starts listening to horizontal and vertical blanks.
	 */
	void startListening();

	/**
	 * Blocks the current thread until the provided HBlank occurred.
	 * @param line
	 *  The horizontal blank to wait for.
	 */
	void waitForHBlank(int line);

	/**
	 * Blocks the current thread until the next VBlank occurs.
	 */
	void waitForVBlank();

	/**
	 * Dispatches the horizontal blank event.
	 */
	void dispatchHBlank();

	/**
	 * Dispatches the vertical blank event.
	 */
	void dispatchVBlank();

private:
	sem_t vblankSemaphore;
	sem_t hblankSemaphore;
};

}
#endif
