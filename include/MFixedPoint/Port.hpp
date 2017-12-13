//!
//! @file 				Port.hpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited				n/a
//! @created			2013-06-17
//! @last-modified		2017-12-13
//! @brief 				Port specific functions.
//! @details
//! 	See README.rst in root dir for more info.


//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#ifndef MN_MFIXEDPOINT_PORT_H
#define MN_MFIXEDPOINT_PORT_H

#include "Config.hpp"
#include <stdint.h>
	
namespace mn {
namespace MFixedPoint {

	class Port
	{
		public:
			static void DebugPrint(char* msg);
	};
	
} // namespace MFixedPoint
} // namespace mn

#endif // #ifndef MN_MFIXEDPOINT_PORT_H

// EOF
