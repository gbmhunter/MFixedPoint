//!
//! @file 		FpTest-Fp64Size.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/07/17
//! @brief 		Tests the size of the Fp64 object.
//! @details
//!				See README.rst in the root dir for more info.

#include <stdio.h>

#include "../src/include/FixedPoint-Fp64.hpp"
#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp64SizeTests)
{
	TEST(SizeTest)
	{
		// Run unit tests
		//return UnitTest::RunAllTests();
		printf("FP: Size of Fp64 object (bytes) = '%lu'.\r\n", sizeof(Fp64<12>));
	
		CHECK_EQUAL(8, sizeof(Fp64<12>));
	}
}