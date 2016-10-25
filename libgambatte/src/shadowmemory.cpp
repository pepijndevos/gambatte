
#include <stdio.h>

#include "shadowmemory.h"

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
	// Debugging purposes:
	printf("*(%p) = %02x", address, data);

	// Decide whether the address is in VRAM or a GPU register, and write the data to it.
	if (isVram(address)) {
		this->vram[address - VRAM_START] = data;
	} else if (isGpuRegister(address)) {
		this->registers[address - REGISTERS_START] = data;
	}
}

unsigned ShadowMemory::remoteRead(unsigned address) {
	// Debugging purposes:
	printf("return *(%p)", address);

	// Decide whether the address is in VRAM or a GPU register, and read the data to it.
	if (isVram(address)) {
		return this->vram[address - VRAM_START];
	} else if (isGpuRegister(address)) {
		return this->registers[address - REGISTERS_START];
	}

	return 0;
}

// VRAM: 0x8000 -> 0xA000
// I/O regs: 0xFF40 -> 0xFF4B
