//!
//! @file 		FpTest-Fp32fSize.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Tests the size of the Fp32f object.
//! @details
//!				See README.rst in the root dir for more info.

#include <stdio.h>

#include "../src/include/FixedPoint-Fp32f.hpp"
#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp32fSizeTests)
{
	TEST(SizeTest)
	{
		// Run unit tests
		//return UnitTest::RunAllTests();
		printf("FP: Size of Fp32f object (bytes) = '%lu'.\r\n", sizeof(Fp32f<12>));
	
		CHECK_EQUAL((size_t)4, sizeof(Fp32f<12>));
	}
}