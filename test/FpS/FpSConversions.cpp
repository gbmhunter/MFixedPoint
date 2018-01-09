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

	// Check double->fixed conversion first as the
	// rest of the tests depend on it
	MTEST(PositiveDoubleToFixedConversionTest) {
		FpS<int32_t> fp1(3.2, 8);
		// The closest fixed point number this can be represented
		// as is Math.Round(3.2*2^8) = 819 = 0b001100110011
		CHECK_EQUAL(fp1.GetRawVal(), (int32_t)0b001100110011);
	}

	MTEST(NegativeDoubleToFixedConversionTest) {
		FpS<int32_t> fp1(-3.2, 8);

		// The closest fixed point number this can be represented
		// as is Math.Round(-3.2*2^8) = -819 = 0b11111111111111111111110011001101 (32-bit 2's compliment)
		CHECK_EQUAL(fp1.GetRawVal(), (int32_t)0b11111111111111111111110011001101);
	}

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

	MTEST(CastInt32Negative) {
		FpS<int32_t> fp1(-3.2, 8);
        CHECK_EQUAL((int32_t)fp1, -4);
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