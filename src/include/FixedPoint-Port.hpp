//!
//! @file 		Fp-Port.hpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited		n/a
//! @date 		2013/06/17
//! @brief 		Port specific functions.
//! @details
//! 			See README.rst


//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#ifndef FP_PORT_H
#define FP_PORT_H

#include "FixedPoint-Config.hpp"
#include <stdint.h>

//! @brief		Determines what code is used for the port-specific functions.
//! @details	Supported platforms:
//!					PSOC	All PSoC families (PSoC 3, PSoC 4, PSoC 5, PSoC 5LP)
#if(__linux__ == 1)
	#define TARGET_PLATFORM		LINUX
#elif(PSOC4 == 1)
	#define TARGET_PLATFORM		PSOC
#else
	#error Target platform not recognised
#endif
	
namespace Fp
{

	class Port
	{
		public:
			static void DebugPrint(char* msg);
	};
	
} // namespace Fp

#endif // #ifndef FP_PORT_H

// EOF
