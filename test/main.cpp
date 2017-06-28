//!
//! @file 				main.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-05-30
//! @last-modified		2014-09-15
//! @brief 				Has the entry point for the unit test program.
//! @details
//!		See README.rst

//===== SYSTEM LIBRARIES =====//
// none

//===== USER LIBRARIES =====//
#include "MUnitTest/MUnitTestApi.hpp"

//===== USER SOURCE =====//
// none

using namespace MbeddedNinja;

int main()
{
	// Run unit tests
	return TestRegister::RunAllTests();
}
