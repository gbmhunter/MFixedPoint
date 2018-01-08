//!
//! \file 				FpSConversions.cpp
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

	// MTEST(README) {
	// 	FpS<int32_t> fp1(2.22, 8);	
	// 	printf("ToInt<int32_t>() = %i\n", fp1.ToInt<int32_t>()); // Prints "ToInt<int32_t>() = 2"
	// 	printf("ToDouble() = %.2f\n", fp1.ToDouble()); // Prints "ToDouble() = 2.22"
	// }

	MTEST(ToInt32Positive) {
		FpS<int32_t> fp1(34.2, 8);
        CHECK_EQUAL(fp1.ToInt<int32_t>(), 34);
	}

	MTEST(ToInt32Negative) {
		FpS<int32_t> fp1(-66.3, 8);
        CHECK_EQUAL(fp1.ToInt<int32_t>(), -67); // Rounds towards negative infinity
	}

	MTEST(ToFloat) {
		FpS<int32_t> fp1(34.2, 8);
        CHECK_CLOSE(fp1.ToFloat(), 34.2, 0.1);
	}

	MTEST(ToDouble) {
		FpS<int32_t> fp1(123.4, 15);
        CHECK_CLOSE(fp1.ToDouble(), 123.4, 0.01);
	}

	MTEST(CastInt32Positive) {
		FpS<int32_t> fp1(34.2, 8);
        CHECK_EQUAL((int32_t)fp1, 34);
	}

	MTEST(CastFloat) {
		FpS<int32_t> fp1(34.2, 8);
        CHECK_CLOSE((float)fp1, 34.2, 0.1);
	}

	MTEST(CastDouble) {
		FpS<int32_t> fp1(-34.982, 15);
        CHECK_CLOSE((double)fp1, -34.982, 0.01);
	}
}