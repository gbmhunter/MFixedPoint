//!
//! @file 				Port.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-06-17
//! @last-modified		2017-06-26
//! @brief 				Port specific functions.
//! @details
//!		See README.rst in root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// Associated header file
#include "MFixedPoint/Port.hpp"

#ifdef __linux__
	#include <stdio.h>
#elif(PSOC)
	extern "C" {
		#include <device.h>
	}
#endif

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Fp 
{
	void Port::DebugPrint(char* msg)
	{
		#ifdef __linux__
			// Print to terminal
			printf("%s", msg);
		#elif(CY_PSOC5)
			// Print to debug UART
			UartCpDebug_PutString(msg);
		#endif
	}

} // namespace Fp

// EOF
