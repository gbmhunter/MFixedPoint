//!
//! @file 				Fp32fSize.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-05-30
//! @last-modified		2014-09-15
//! @brief 				Tests the size of the Fp32f object.
//! @details
//!		See README.rst in the root dir for more info.

//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

//===== USER LIBRARIES =====//
#include "MUnitTest/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MFixedPointApi.hpp"

using namespace Fp;

MTEST_GROUP(Fp32fSizeTests)
{
	MTEST(SizeTest)
	{
		// Run unit tests
		//return UnitTest::RunAllTests();
		printf("FP: Size of Fp32f object (bytes) = '%lu'.\r\n", sizeof(Fp32f<12>));
	
		CHECK_EQUAL(sizeof(Fp32f<12>), (size_t)4);
	}
}
