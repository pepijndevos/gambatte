#ifndef MONITOR_LISTENER_H
#define MONITOR_LISTENER_H

//#include "video/ppu.h"
//#include "memory.h"
#include <stdio.h>
#include <semaphore.h>

namespace gambatte {

class BlankAcceptor {
public:
	virtual void acceptHBlank(int hblank) = 0;
	virtual void acceptVBlank() = 0;
};

/**
 * Responsible for listening to events the display dispatches.
 */
class MonitorListener {
public:
	/**
	 * Starts listening to horizontal and vertical blanks.
	 */
	void startListening(BlankAcceptor *acceptor);

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

	unsigned getHBlank() const { return hblank_; }

	void setHBlank(unsigned value) { hblank_ = value; }
private:
//	BlankAcceptor *acceptor_;
	unsigned hblank_;
	sem_t vblankSemaphore;
	sem_t hblankSemaphore;
};

}
#endif
