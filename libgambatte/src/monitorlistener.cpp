#include "monitorlistener.h"
#include <pthread.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "video/ppu.h"
#include <time.h>

#define PIN_HBLANK 5 // D14
#define PIN_VBLANK 4 // D13

namespace gambatte {

//void* listenThread(void *arg) {
//	PPU *ppu = (PPU*) arg;
//
//	bool vblankOccurred = false;
//	printf("listen\n");
//	int frameCount = 0;
//	time_t rawTime;
//	time (&rawTime);
//	for (;;) {
//		if (digitalRead(PIN_VBLANK) == HIGH) {
//			if (!vblankOccurred) {
//				frameCount++;
//			//	ppu->doLyCountEvent();
//				vblankOccurred = true;
//			}
//		} else {
//			vblankOccurred = false;
//		}
//
//		if (frameCount == 10) {
//			time_t nextTime;
//			time(&rawTime);
//
//			double frequency = frameCount / (nextTime - rawTime);
//			printf("VBlank frequency = %d\n", frequency);
//
//			rawTime = nextTime;
///			frameCount = 0;
//		}
//	}
//
//	return NULL;
//}

PPU *ppu;


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
//      printf("HBLANKs = %f.\n", hblankCount);
        hblankCount = 0;

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
//	pthread_t threadID;
//
//	if (pthread_create(&threadID, NULL, &listenThread, ppu_) != 0) {
//		printf("Can't create thread.\n");
//	}
	ppu = ppu_;
	time(&start);
	wiringPiISR(PIN_VBLANK, INT_EDGE_RISING, &vblankHandler);
	wiringPiISR(PIN_HBLANK, INT_EDGE_RISING, &hblankHandler);
}

}
