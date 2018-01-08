//!
//! \file 				FpSConstructors.cpp
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

MTEST_GROUP(FpSTests) {

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

}