
#include <stdio.h>
#include <stdlib.h>
#include "fpgamemory.h"
#include <wiringPiSPI.h>
#include <unistd.h>

#define CHANNEL_WRITE 0
#define CHANNEL_READ 1
#define FREQUENCY 100000000 /*32000000*/

namespace gambatte {

	FPGAMemory::FPGAMemory() {
		if (wiringPiSPISetup(CHANNEL_WRITE, FREQUENCY) == -1) {
	                printf ("WRITE SPI Setup failed.\n");
        	}
		if (wiringPiSPISetup(CHANNEL_READ, FREQUENCY) == -1) {
			printf ("READ SPI Setup failed.\n");
		}
	}

	FPGAMemory::~FPGAMemory() {
	}

	void FPGAMemory::writeAddressToBuffer(unsigned char* buffer, unsigned address) {
                if (isVram(address) || isSprite(address)) {
                        buffer[0] = ((address >> 8) & 0xFF);
                } else {
                        buffer[0] = 0xFF;
                }

                buffer[1] = (address & 0xFF);
	}

	void FPGAMemory::remoteWrite(unsigned address, unsigned data) {
		writeAddressToBuffer(writeBuffer, address);
		writeBuffer[2] = data & 0xFF;

		wiringPiSPIDataRW(CHANNEL_WRITE, writeBuffer, 3);
	}

	unsigned FPGAMemory::remoteRead(unsigned address) {
		writeAddressToBuffer(readBuffer, address);
//		printf("REQ: %02x %02x %02x\n", readBuffer[0], readBuffer[1], readBuffer[2]);
		wiringPiSPIDataRW(CHANNEL_READ, readBuffer, 3);
//		printf("%04x: %02x\n", address, readBuffer[2]);
		printf("REC: %02x %02x %02x\n", readBuffer[0], readBuffer[1], readBuffer[2]);
		return readBuffer[2];
	}
}
