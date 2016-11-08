#include "monitorlistener.h"
#include <pthread.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "video/ppu.h"
#include <time.h>
#include <sys/time.h>
#include <semaphore.h>
#include <unistd.h>

#define PIN_HBLANK 7 // D04
#define PIN_VBLANK 6 // D15

namespace gambatte {

BlankAcceptor *acceptor_;

int hblankTarget = 0;
volatile int hblankCount = 0;
volatile double frameCount = 0;
bool firstVBlank = false;

unsigned long long start;

unsigned long long getCurrentTime() {
	struct timeval tv;

	gettimeofday(&tv, NULL);

	return   (unsigned long long)(tv.tv_sec) * 1000 +
		 (unsigned long long)(tv.tv_usec) / 1000;
}

void hblankHandler() {
	if (!firstVBlank || hblankCount >= 153) {
		return;
	}
        hblankCount++;
//	printf("hblank = %02x\n", hblankCount);
//	listener->setHBlank(hblankCount);
	printf("HBLANK\n");
	acceptor_->acceptHBlank(hblankCount);

//	if (hblankCount == hblankTarget) {
//		listener->dispatchHBlank();
//	}
}

void vblankHandler() {
	firstVBlank = true;
//	listener->dispatchVBlank();
	acceptor_->acceptVBlank();

        hblankCount = 0;
	frameCount++;
        unsigned long long end = getCurrentTime();

	double seconds = (double)(end - start) / 1000.0;
        if (seconds >= 1) {
                double vBlankFrequency = frameCount / seconds;
                frameCount = 0;
                start = end;
                printf("[vblank]  FPS: %fHz.\n", vBlankFrequency);
        }
}

void MonitorListener::startListening(BlankAcceptor *acceptor) {
	acceptor_ = acceptor;
	acceptor_->acceptHBlank(0);
	sem_init(&vblankSemaphore, 0, 0);

//	listener = this;
	start = getCurrentTime();

	pinMode(PIN_HBLANK, INPUT);
	pinMode(PIN_VBLANK, INPUT);

	wiringPiISR(PIN_VBLANK, INT_EDGE_FALLING, &vblankHandler);
	wiringPiISR(PIN_HBLANK, INT_EDGE_FALLING, &hblankHandler);
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
