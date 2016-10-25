
#include <stdio.h>
#include "shadowmemory.h"

ShadowMemory::ShadowMemory() {
	this->vram = new unsigned char[VRAM_END - VRAM_START];
	this->registers = new unsigned char[REGISTERS_END - REGISTERS_START];
}

void ShadowMemory::remoteWrite(unsigned long address, unsigned data) {
	printf("*(%p) = %02x", address, data);

	if (isVram(address)) {
		this->vram[address - VRAM_START] = data;
	} else if (isGpuRegister(address)) {
		this->registers[address - REGISTERS_START] = data;
	}

}

unsigned long ShadowMemory::remoteRead(unsigned long address) {
	printf("return *(%p)", address);

	if (isVram(address)) {
		return this->vram[address - VRAM_START];
	} else if (isGpuRegister(address)) {
		return this->registers[address - REGISTERS_START];
	}

	return 0;
}

// VRAM: 0x8000 -> 0xA000
// I/O regs: 0xFF40 -> 0xFF4B
