//!
//! @file 				Fp64fSize.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-07-17
//! @last-modified		2017-06-27
//! @brief 				Tests the size of the Fp64f object.
//! @details
//!		See README.rst in the root dir for more info.

// System includes
// none

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/Fp64f.hpp"

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
