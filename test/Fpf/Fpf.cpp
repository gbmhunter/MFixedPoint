//!
//! @file 				Fpf.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2018-01-08
//! @last-modified		2017-01-08
//! @brief 				Performs unit tests on the fixed point class.
//! @details
//!						See README.rst in root dir for more info.

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/Fpf.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpfTests) {
	MTEST(NoFractionalBits)	{
		Fpf<int32_t, 0> fp1 = 34;		
        CHECK_EQUAL(fp1.rawVal, 34);
	}

	MTEST(OneFractionalBit)	{
		Fpf<int32_t, 1> fp1 = 34;		
        CHECK_EQUAL(fp1.rawVal, 34 << 1);
	}
}