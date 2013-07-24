//!
//! @file 		FixedPoint-Port.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/06/17
//! @brief 		Port specific functions.
//! @details
//!				See README.rst in root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// Associated header file
#include "include/FixedPoint-Port.hpp"

#ifdef __cplusplus
	
#endif

#ifdef __linux__
	#include <stdio.h>
#elif(CY_PSOC5)
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
