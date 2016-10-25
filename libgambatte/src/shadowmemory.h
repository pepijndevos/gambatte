#ifndef SHADOW_MEM
#define SHADOW_MEM

#include "externalmemory.h"

namespace gambatte {

	class ShadowMemory : public ExternalMemory {

	public:
		ShadowMemory();
		virtual void remoteWrite(unsigned long address, unsigned data);
		virtual unsigned remoteRead(unsigned long address);

	private:
		unsigned char* vram;
		usnigned char* registers;
	};

}

#endif
