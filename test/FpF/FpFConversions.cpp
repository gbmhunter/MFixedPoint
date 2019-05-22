//!
//! \file 				FpFConversions.cpp
//! \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! \edited 			n/a
//! \created			2013-07-22
//! \last-modified		2019-05-22
//! \brief 				Performs unit tests on the fixed point FpF class.
//! \details
//!						See README.rst in root dir for more info.

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/FpF.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpFConversions) {

	// Check double->fixed conversion first as the
	// rest of the tests depend on it
	MTEST(PositiveDoubleToFixedConversionTest) {
		FpF32<8> fp1(3.2);
		// The closest fixed point number this can be represented
		// as is Math.Round(3.2*2^8) = 819 = 0b001100110011
		CHECK_EQUAL(fp1.GetRawVal(), (int32_t)0b001100110011);
	}

	MTEST(NegativeDoubleToFixedConversionTest) {
		FpF32<8> fp1(-3.2);

		// The closest fixed point number this can be represented
		// as is Math.Round(-3.2*2^8) = -819 = 0b11111111111111111111110011001101 (32-bit 2's compliment)
		CHECK_EQUAL(fp1.GetRawVal(), (int32_t)0b11111111111111111111110011001101);
	}

	MTEST(ToInt32Positive) {
		FpF32<8> fp1(34.2);
        CHECK_EQUAL(fp1.ToInt<int32_t>(), 34);
	}

	MTEST(ToInt32Negative) {
		FpF32<8> fp1(-66.3);
        CHECK_EQUAL(fp1.ToInt<int32_t>(), -67); // Rounds towards negative infinity
	}

	MTEST(ToFloat) {
		FpF32<8> fp1(34.2);
        CHECK_CLOSE(fp1.ToFloat(), 34.2, 0.1);
	}

	MTEST(ToDouble) {
		FpF32<15> fp1(123.4);
        CHECK_CLOSE(fp1.ToDouble(), 123.4, 0.01);
	}

	MTEST(CastInt32Positive) {
		FpF32<8> fp1(34.2);
        CHECK_EQUAL((int32_t)fp1, 34);
	}

	MTEST(CastInt32Negative) {
		FpF32<8> fp1(-3.2);
        CHECK_EQUAL((int32_t)fp1, -4);
	}

	MTEST(CastFloat) {
		FpF32<8> fp1(34.2);
        CHECK_CLOSE((float)fp1, 34.2, 0.1);
	}

	MTEST(CastDouble) {
		FpF32<15> fp1(-34.982);
        CHECK_CLOSE((double)fp1, -34.982, 0.01);
	}

	MTEST(ConstructFromIntTest) {
		FpF<int64_t, int64_t, 25> fp1 = 75;
		CHECK_CLOSE(fp1.ToInt<int64_t>(), 75, 0.1);		
	}
}