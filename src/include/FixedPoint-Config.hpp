//!
//! @file 		Fp-Config.hpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited		n/a
//! @date 		2013/06/17
//! @brief 		Port specific functions.
//! @details
//! 			See README.rst in root dir for more info.

//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#ifndef FP_CONFIG_H
#define FP_CONFIG_H
	
//===============================================================================================//
//========================================= NAMESPACE ===========================================//
//===============================================================================================//
	
namespace Fp
{
	//! @brief		(bool) If set to 1, general debug information will be printed to the
	//!				port-specific output.
	#define fpConfig_PRINT_DEBUG_GENERAL		1
	
} // namespace Fp

#endif // #ifndef FP_CONFIG_H

// EOF
