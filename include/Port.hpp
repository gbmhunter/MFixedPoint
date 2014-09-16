//!
//! @file 				Port.hpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited				n/a
//! @created			2013-06-17
//! @last-modified		2014-09-15
//! @brief 				Port specific functions.
//! @details
//! 	See README.rst in root dir for more info.


//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#ifndef FP_PORT_H
#define FP_PORT_H

#include "Config.hpp"
#include <stdint.h>
	
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
