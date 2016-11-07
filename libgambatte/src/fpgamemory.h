#ifndef FPGAMEM_H
#define FPGAMEM_H

#include "externalmemory.h"

namespace gambatte {

	class FPGAMemory : public ExternalMemory {
	public:
		/**
		 * Creates a new instance of the FPGA memory class.
		 */
		FPGAMemory();

		/**
		 * Disconnects from the FPGA.
		 */
		~FPGAMemory();

		virtual void remoteWrite(unsigned address, unsigned data);

		virtual unsigned remoteRead(unsigned address);
	private:

		void writeAddressToBuffer(unsigned char* buffer, unsigned address);

		unsigned char writeBuffer[3];
		unsigned char readBuffer[3];
	};
}


#endif
