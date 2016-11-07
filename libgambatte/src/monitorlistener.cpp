#include "monitorlistener.h"
#include <pthread.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "video/ppu.h"
#include <time.h>
#include <semaphore.h>
#include <unistd.h>

#define PIN_HBLANK 5 // D14
#define PIN_VBLANK 4 // D13

namespace gambatte {

MonitorListener *listener;

int hblankTarget = 0;
int hblankCount = 0;
double frameCount = 0;

time_t start;

void hblankHandler() {
//	printf("hblank\n");
        hblankCount++;
	if (hblankCount == hblankTarget) {
//		printf("HBLANK = %d\n", hblankCount);
		listener->dispatchHBlank();
	}
}

void vblankHandler() {
	listener->dispatchVBlank();

        hblankCount = 0;
	frameCount++;
        time_t end;
        time(&end);

        if (end - start >= 1) {
                double vBlankFrequency = frameCount / (end - start);
                frameCount = 0;
                start = end;
                // printf("VBLANK Frequency = %fHz.\n", vBlankFrequency);
        }
}

void MonitorListener::startListening() {
	sem_init(&vblankSemaphore, 0, 0);

	listener = this;
	time(&start);

	pinMode(PIN_HBLANK, INPUT);
	pinMode(PIN_VBLANK, INPUT);

	wiringPiISR(PIN_VBLANK, INT_EDGE_FALLING, &vblankHandler);
//	wiringPiISR(PIN_HBLANK, INT_EDGE_RISING, &hblankHandler);
}

void MonitorListener::waitForHBlank(int line) {
	hblankTarget = line;
	sem_wait(&hblankSemaphore);
}

void MonitorListener::waitForVBlank() {
	sem_wait(&vblankSemaphore);
}

void MonitorListener::dispatchHBlank() {
	sem_post(&hblankSemaphore);
}

void MonitorListener::dispatchVBlank() {
	sem_post(&vblankSemaphore);
}

}
