
#include <stdio.h>
#include <stdlib.h>
#include "fpgamemory.h"
#include <wiringPiSPI.h>

#define CHANNEL 0

namespace gambatte {

	FPGAMemory::FPGAMemory() {
		if (wiringPiSPISetup(CHANNEL, 32000000) < 0) {
                printf ("SPI Setup failed.\n");
        }
	}

	FPGAMemory::~FPGAMemory() {
	}

	void ShadowMemory::remoteWrite(unsigned address, unsigned data) {
		unsigned char* buffer = (unsigned char*) malloc(3);

		buffer[0] = (address & 0xFF);
		buffer[1] = ((address >> 8) & 0xFF);
		buffer[2] = (data & 0xFF);

		wiringPiSPIDataRW(CHANNEL, buffer, 3);
        free(buffer);
	}

	unsigned ShadowMemory::remoteRead(unsigned address) {

		return 0;
	}
}