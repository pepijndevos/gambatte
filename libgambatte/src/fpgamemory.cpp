
#include <stdio.h>
#include <stdlib.h>
#include "fpgamemory.h"
#include <wiringPiSPI.h>
#include <unistd.h>

#define CHANNEL 0
#define FREQUENCY 200000000 /*32000000*/
namespace gambatte {

	FPGAMemory::FPGAMemory() {
		if (wiringPiSPISetup(CHANNEL, FREQUENCY) < 0) {
	                printf ("SPI Setup failed.\n");
        	}
	}

	FPGAMemory::~FPGAMemory() {
	}

	void FPGAMemory::remoteWrite(unsigned address, unsigned data) {
		//printf("remoteWrite(%04x, %02x)\n", address, data);
		unsigned char* buffer = (unsigned char*) malloc(3);

		if (isSprite(address)) {
//			printf("sprite write at %04x: %02x\n", address, data);
		}

		if (isVram(address) || isSprite(address)) {
			buffer[0] = ((address >> 8) & 0xFF);
		} else {
			buffer[0] = 0xFF;
		}

		buffer[1] = (address & 0xFF);
		buffer[2] = (data & 0xFF);

		wiringPiSPIDataRW(CHANNEL, buffer, 3);
	        free(buffer);
//		sleep(1);
	}

	unsigned FPGAMemory::remoteRead(unsigned address) {

		return 0;
	}
}
