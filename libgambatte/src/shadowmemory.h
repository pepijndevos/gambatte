#ifndef SHADOW_MEM
#define SHADOW_MEM

#include "externalmemory.h"

namespace gambatte {

	/**
     * Provides an implementation for the ExternalMemory class, storing the memory on the same device.
	 */
	class ShadowMemory : public ExternalMemory {

	public:
		/**
		 * Creates a new instance of the ShadowMemory class.
		 */
		ShadowMemory();

		/**
		 * Releases the shadow memory from memory. (memoryception :D).
		 */
		~ShadowMemory();

		virtual void remoteWrite(unsigned address, unsigned data);

		virtual unsigned remoteRead(unsigned address);

	private:
		/**
  		 * Represents the VRAM of the GameBoy.
  		 */
		unsigned char* vram;

		/**
		 * Represents the GPU registers of the GameBoy.
		 */
		unsigned char* registers;
	};

}

#endif
