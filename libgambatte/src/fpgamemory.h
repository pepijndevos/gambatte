#ifndef FPGAMEM_H
#define FPGAMEM_H

namespace gambatte {

	class FPGAMemory : ExternalMemory {

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
	}
}


#endif
