//!
//! @file 				Fp64fSize.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-07-17
//! @last-modified		2014-09-15
//! @brief 				Tests the size of the Fp64f object.
//! @details
//!		See README.rst in the root dir for more info.

//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

//===== USER LIBRARIES =====//
#include "MUnitTest/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MFixedPointApi.hpp"

using namespace Fp;

MTEST_GROUP(Fp64fSizeTests)
{
	MTEST(SizeTest)
	{
		// Run unit tests
		//return UnitTest::RunAllTests();
		printf("FP: Size of Fp64f object (bytes) = '%lu'.\r\n", sizeof(Fp64f<12>));
	
		CHECK_EQUAL(sizeof(Fp64f<12>), (size_t)8);
	}
}
