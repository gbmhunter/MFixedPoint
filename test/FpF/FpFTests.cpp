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

MTEST_GROUP(FpFTests) {
	MTEST(NoFractionalBits)	{
		FpF<int32_t, 0> fp1 = 34;		
        CHECK_EQUAL(fp1.rawVal, 34);
	}

	MTEST(OneFractionalBit)	{
		FpF<int32_t, 1> fp1 = 34;		
        CHECK_EQUAL(fp1.rawVal, 34 << 1);
	}

	MTEST(CreateFromInteger)	{
		FpF<int32_t, 8> fp1 = 34;		
        CHECK_EQUAL(fp1.rawVal, 34 << 8);
	}

	MTEST(CreateFromFloat)	{
		FpF<int32_t, 8> fp1 = 34.2f;		
        CHECK_EQUAL(fp1.rawVal, (int32_t)(34.2f * (1 << 8)));
	}

	MTEST(CreateFromDouble)	{
		FpF<int32_t, 8> fp1 = 34.2; // No suffix denotes a double		
        CHECK_EQUAL(fp1.rawVal, (int32_t)(34.2 * (1 << 8)));
	}

	MTEST(SizeTest) {	
		CHECK_EQUAL(sizeof(FpF<int8_t, 8>), (size_t)1);
		CHECK_EQUAL(sizeof(FpF<int16_t, 8>), (size_t)2);
		CHECK_EQUAL(sizeof(FpF<int32_t, 8>), (size_t)4);
		CHECK_EQUAL(sizeof(FpF<int64_t, 8>), (size_t)8);
	}

	MTEST(Addition)	{
		FpF<int32_t, 8> fp1 = 34.2;
		FpF<int32_t, 8> fp2 = 8.6;
		FpF<int32_t, 8> fp3 = fp1 + fp2;
        CHECK_EQUAL(fp3.rawVal, (int32_t)(34.2 * (1 << 8)) + (int32_t)(8.6 * (1 << 8)));
	}

	MTEST(Subtraction)	{
		FpF<int32_t, 8> fp1 = 34.2;
		FpF<int32_t, 8> fp2 = 8.6;
		FpF<int32_t, 8> fp3 = fp1 - fp2;
        CHECK_EQUAL(fp3.rawVal, (int32_t)(34.2 * (1 << 8)) - (int32_t)(8.6 * (1 << 8)));
	}
}