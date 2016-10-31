
#include <stdio.h>
#include <stdlib.h>
#include "shadowmemory.h"

namespace gambatte {

	ShadowMemory::ShadowMemory() {
		// Initialize shadow memory variables.
		this->vram = (unsigned char*) malloc(VRAM_END - VRAM_START);
		this->registers = (unsigned char*) malloc(REGISTERS_END - REGISTERS_START);
	}

	ShadowMemory::~ShadowMemory() {
		// Release the shadow memory.
		free(this->vram);
		free(this->registers);
	}

	void ShadowMemory::remoteWrite(unsigned address, unsigned data) {
		// Decide whether the address is in VRAM or a GPU register, and write the data to it.
		if (isVram(address)) {
			this->vram[address - VRAM_START] = data;
		} else if (isGpuRegister(address, true)) {
			this->registers[(address & 0xFF) - (REGISTERS_START & 0xFF)] = data;
		}
	}

	unsigned ShadowMemory::remoteRead(unsigned address) {
		// Decide whether the address is in VRAM or a GPU register, and read the data to it.
		if (isVram(address)) {
			return this->vram[address - VRAM_START];
		} else if (isGpuRegister(address, true)) {
			return this->registers[(address & 0xFF) - (REGISTERS_START & 0xFF)];
		} else {
			printf("NOT A VRAM ADDRESS %08x", address);
		}

		return 0;
	}
}