
#ifndef EXTERNAL_MEM
#define EXTERNAL_MEM

#define VRAM_START 			0x8000
#define VRAM_END 			0xA000
#define REGISTERS_START 	0xFF40
#define REGISTERS_END 		0xFF4B

namespace gambatte {

	/** 
	 * Provides a base implementation for a memory present on a remote device.
	 */
	class ExternalMemory {

	public:
		
		/**
		 * Determines whether the provided address should be forwarded to the remote device or not.
		 * 
		 * @param address 
		 *	The address to determine.
		 * @param lastByteOnly
		 *  True if only the last byte of the address should be checked, false otherwise.
		 * @return 
		 *  True whether the address should be forwarded, false otherwise.
		 */
		bool shouldForward(unsigned long address, bool lastByteOnly) {
			return isVram(address) || isGpuRegister(address, lastByteOnly);
		}

		/**
		 * Writes data to the remote memory.
		 * @param address
		 *  The address to write the data to.
		 * @param data
		 *  The data to write.
		 */
		virtual void remoteWrite(unsigned address, unsigned data) = 0;

		/**
		 * Reads data from the remote memory.
		 * @param address
		 *  The address to read data from.
		 */
		virtual unsigned remoteRead(unsigned address) = 0;

	protected:
		/**
		 * Determines whether an address is located in the VRAM of the gameboy.
		 * @param address
		 *  The address to determine.
		 * @return
		 *  True whether the address is located in VRAM, false otherwise.
		 */
		static bool isVram(unsigned address) {
			return (address >= VRAM_START && address < VRAM_END);
		}

		/**
		 * Determines whether an address points to a GPU register.
		 * @param address
		 *  The address to determine
		 * @return
		 *  True whether the address points to a GPU register, false otherwise.
		 */
		static bool isGpuRegister(unsigned address, bool lastByteOnly) {
			if (lastByteOnly) {
				return ((address & 0xFF) >= (REGISTERS_START & 0xFF) && (address & 0xFF) < (REGISTERS_END & 0xFF));
			} else {
				return  (address >= REGISTERS_START && address < REGISTERS_END);
			}
		}
	};

}

#endif