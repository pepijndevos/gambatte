#ifndef MONITOR_LISTENER_H
#define MONITOR_LISTENER_H

#include "video/ppu.h"

namespace gambatte {

class MonitorListener { 
public:
	MonitorListener(PPU *ppu) {
		ppu_ = ppu;
	}

	void startListening();

private:
	PPU* ppu_;

};

}
#endif
