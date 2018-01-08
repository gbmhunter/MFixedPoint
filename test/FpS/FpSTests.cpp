//!
//! @file 				FpSTests.cpp
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
#include "MFixedPoint/FpS.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpSTests) {

	MTEST(NoFractionalBits)	{
		FpS<int32_t> fp1(34, 0);		
        CHECK_EQUAL(fp1.GetRawVal(), 34);
	}

	MTEST(OneFractionalBit)	{
		FpS<int32_t> fp1(34, 1);		
        CHECK_EQUAL(fp1.GetRawVal(), 34 << 1);
	}

	MTEST(CreateFromInteger)	{
		FpS<int32_t> fp1(34, 0);		
        CHECK_EQUAL(fp1.GetRawVal(), 34 << 0);
	}

	MTEST(CreateFromFloat)	{
		FpS<int32_t> fp1(34.2f, 8);		
        CHECK_EQUAL(fp1.GetRawVal(), (int32_t)(34.2f * (1 << 8)));
	}

	MTEST(CreateFromDouble)	{
		FpS<int32_t> fp1(34.2, 8); // No suffix denotes a double		
        CHECK_EQUAL(fp1.GetRawVal(), (int32_t)(34.2 * (1 << 8)));
	}

	MTEST(SizeTest) {	
		CHECK_EQUAL(sizeof(FpS<int8_t>), (size_t)2);
		CHECK_EQUAL(sizeof(FpS<int16_t>), (size_t)4);
		CHECK_EQUAL(sizeof(FpS<int32_t>), (size_t)8);
		CHECK_EQUAL(sizeof(FpS<int64_t>), (size_t)16);
	}

	MTEST(Addition)	{
		FpS<int32_t> fp1(34.2, 8);
		FpS<int32_t> fp2(8.6, 8);
		FpS<int32_t> fp3 = fp1 + fp2;
        CHECK_EQUAL(fp3.GetRawVal(), (int32_t)(34.2 * (1 << 8)) + (int32_t)(8.6 * (1 << 8)));
	}

	MTEST(Subtraction)	{
		FpS<int32_t> fp1(34.2, 8);
		FpS<int32_t> fp2(8.6, 8);
		FpS<int32_t> fp3 = fp1 - fp2;
        CHECK_EQUAL(fp3.GetRawVal(), (int32_t)(34.2 * (1 << 8)) - (int32_t)(8.6 * (1 << 8)));
	}
}