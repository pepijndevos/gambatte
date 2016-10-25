
#ifndef EXTERNAL_MEM
#define EXTERNAL_MEM

#define VRAM_START 			0x8000;
#define VRAM_END 			0xA000;
#define REGISTERS_START 	0xFF40;
#define REGISTERS_END 		0xFF4B;

namespace gambatte {

	class ExternalMemory {

	public:
		
		bool shouldForward(unsigned long address) {
			return isVram(address) || isGpuRegister(address);
		}

		virtual void remoteWrite(unsigned long address, unsigned data) = 0;

		virtual unsigned remoteRead(unsigned long address) = 0;

	private:
		static bool isVram(unsigned long address) {
			return (address >= VRAM_START && address < VRAM_END);
		}

		static bool isGpuRegister(unsigned long address) {
			return  (address >= REGISTERS_START && address < REGISTERS_END);
		}
	};

}

#endif