//!
//! @file 		FixedPoint-Port.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/06/17
//! @brief 		Port specific functions.
//! @details
//!				See README.rst.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// Associated header file
#include "include/FixedPoint-Port.hpp"

#ifdef __cplusplus
	extern "C" {
#endif
	#if(TARGET_PLATFORM == LINUX)
		#include <stdio.h>
	#elif(TARGET_PLATFORM == PSOC)
		#include <device.h>
	#endif


#ifdef __cplusplus
	} // extern "C" {
#endif

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Fp 
{

	void Port::DebugPrint(char* msg)
	{
		#if(TARGET_PLATFORM == LINUX)
			// Print to terminal
			printf("%s", msg);
		#elif(TARGET_PLATFORM == PSOC)
			// Print to debug UART
			UartCpDebug_PutString(msg);
		#endif
	}

} // namespace Fp

// EOF
