//!
//! \file 				FpSMisc.cpp
//! \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! \edited 			n/a
//! \created			2018-01-08
//! \last-modified		2017-01-08
//! \brief 				Performs unit tests on the fixed point FpS class.
//! \details
//!						See README.rst in root dir for more info.

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/FpS.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpSMisc) {

	MTEST(NoFractionalBits)	{
		FpS<int32_t> fp1(34, 0);		
        CHECK_EQUAL(fp1.GetRawVal(), 34);
	}

	MTEST(OneFractionalBit)	{
		FpS<int32_t> fp1(34, 1);		
        CHECK_EQUAL(fp1.GetRawVal(), 34 << 1);
	}

	MTEST(SizeTest) {	
		CHECK_EQUAL(sizeof(FpS<int8_t>), (size_t)2);
		CHECK_EQUAL(sizeof(FpS<int16_t>), (size_t)4);
		CHECK_EQUAL(sizeof(FpS<int32_t>), (size_t)8);
		CHECK_EQUAL(sizeof(FpS<int64_t>), (size_t)16);
	}
}