#include "monitorlistener.h"
#include <pthread.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "video/ppu.h"
#include <time.h>

#define PIN_HBLANK 5 // D14
#define PIN_VBLANK 4 // D13

namespace gambatte {

MonitorListener *listener;

double hblankCount = 0;
double frameCount = 0;

time_t start;

void hblankHandler() {
        if (hblankCount >= 144 && hblankCount < 145) {
                frameCount ++;
        }
        hblankCount++;
}

void vblankHandler() {
//	listener->getMemory()->resetCounters(listener->getCycleCounter());
	//listener->getPPU()->getLyCounter()->reset(0, listener->getCycleCounter());
	//listener->getMemory()->triggerVblankInterrupt(listener->getCycleCounter());
	listener->dispatchVBlank();
        hblankCount = 0;
	frameCount++;
        time_t end;
        time(&end);

        if (end - start >= 1) {
                double vBlankFrequency = frameCount / (end - start);
                frameCount = 0;
                start = end;
                printf("VBLANK Frequency = %fHz.\n", vBlankFrequency);
        }
}

void MonitorListener::startListening() {
	printf("Started listening!\n");
	listener = this;
	time(&start);
	wiringPiISR(PIN_VBLANK, INT_EDGE_RISING, &vblankHandler);
	//wiringPiISR(PIN_HBLANK, INT_EDGE_RISING, &hblankHandler);
}

void MonitorListener::waitForVBlank() {
	vblank_ = false;
	int x = 0;
	while (!vblank_) {
		x++;
	}
//	printf("VBLANK %d\n", x);
}

void MonitorListener::dispatchVBlank() {
	vblank_ = true;
}

}
