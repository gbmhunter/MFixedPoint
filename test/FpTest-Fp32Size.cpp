//!
//! @file 		FpTest-Fp32Size.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Tests the size of the Fp32 object.
//! @details
//!				See README.rst in the root dir for more info.

#include <stdio.h>

#include "../src/include/FixedPoint-Fp32.hpp"
#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp32SizeTests)
{
	TEST(SizeTest)
	{
		// Run unit tests
		//return UnitTest::RunAllTests();
		printf("FP: Size of Fp32 object (bytes) = '%lu'.\r\n", sizeof(Fp32<12>));
	
		CHECK_EQUAL(4, sizeof(Fp32<12>));
	}
}