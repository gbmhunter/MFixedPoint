//!
//! @file 				FpF.cpp
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
#include "MFixedPoint/FpF.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpFRawValTests) {
	MTEST(NoFractionalBits)	{
		FpF32<0> fp1 = 34;		
        CHECK_EQUAL(fp1.rawVal, 34);
	}

	MTEST(OneFractionalBit)	{
		FpF32<1> fp1 = 34;		
        CHECK_EQUAL(fp1.rawVal, 34 << 1);
	}

	MTEST(CreateFromInteger)	{
		FpF32<8> fp1 = 34;		
        CHECK_EQUAL(fp1.rawVal, 34 << 8);
	}

	MTEST(CreateFromFloat)	{
		FpF32<24> fp1 = 34.2f;		
        CHECK_EQUAL(fp1.rawVal, (int32_t)(34.2f * (1 << 24)));
	}

	MTEST(CreateFromDouble)	{
		FpF32<24> fp1 = 34.2; // No suffix denotes a double		
        CHECK_EQUAL(fp1.rawVal, (int32_t)(34.2 * (1 << 24)));
	}

}