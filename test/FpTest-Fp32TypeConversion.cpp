//!
//! @file 		FpTest-Fp32TypeConversion.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Performs unit tests on the 32-bit fixed point library (Fp32).
//! @details
//!				See README.rst

// 32-bit fixed-point library
#include "../src/include/FixedPoint-Fp32.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp32TypeConversionTests)
{

	// Check double->fixed conversion first as the
	// rest of the tests depend on it
	TEST(PositiveDoubleToFixedConversionTest)
	{
		Fp32<8> fp1 = Fp32<8>(3.2);

		// The closest fixed point number this can be represented
		// as is Math.Round(3.2*2^8) = 819 = 0b001100110011
		CHECK_EQUAL(0b001100110011, fp1.intValue);
	}

	TEST(NegativeDoubleToFixedConversionTest)
	{
		Fp32<8> fp1 = Fp32<8>(-3.2);

		// The closest fixed point number this can be represented
		// as is Math.Round(-3.2*2^8) = -819 = 0b11111111111111111111110011001101 (32-bit 2's compliment)
		CHECK_EQUAL(0b11111111111111111111110011001101, fp1.intValue);
	}

	// Now check float->double conversion as the
	// rest of the tests depend on it
	TEST(PositiveFixedToFloatConversionTest)
	{
		Fp32<8> fp1 = Fp32<8>(3.2);

		CHECK_CLOSE(3.2, Fix2Float<8>(fp1.intValue), 0.1);
	}

	TEST(NegativeFixedToFloatConversionTest)
	{
		Fp32<8> fp1 = Fp32<8>(-3.2);

		CHECK_CLOSE(-3.2, Fix2Float<8>(fp1.intValue), 0.1);
	}

}