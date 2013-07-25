//!
//! @file 		FpTest-Fp64fSize.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/07/17
//! @brief 		Tests the size of the Fp64f object.
//! @details
//!				See README.rst in the root dir for more info.

#include <stdio.h>

#include "../src/include/FixedPoint-Fp64f.hpp"
#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp64fSizeTests)
{
	TEST(SizeTest)
	{
		// Run unit tests
		//return UnitTest::RunAllTests();
		printf("FP: Size of Fp64f object (bytes) = '%lu'.\r\n", sizeof(Fp64f<12>));
	
		CHECK_EQUAL((size_t)8, sizeof(Fp64f<12>));
	}
}