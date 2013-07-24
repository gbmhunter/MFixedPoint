//!
//! @file 		FpTest-Fp64fTypeConversion.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Performs unit tests on the fast 64-bit fixed point library.
//! @details
//!				See README.rst in root dir for more info.

// Fast 64-bit fixed-point library
#include "../src/include/FixedPoint-Fp64f.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp64fTypeConversionTests)
{

	// Check double->fixed conversion first as the
	// rest of the tests depend on it
	TEST(PositiveDoubleToFixedConversionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);

		// The closest fixed point number this can be represented
		// as is Math.Round(3.2*2^8) = 819 = 0b001100110011
		CHECK_EQUAL((int32_t)0b001100110011, fp1.rawVal);
	}

	/*
	TEST(NegativeDoubleToFixedConversionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(-3.2);

		// The closest fixed point number this can be represented
		// as is Math.Round(-3.2*2^8) = -819 = 0b11111111111111111111110011001101 (32-bit 2's compliment)
		CHECK_EQUAL((int32_t)0b11111111111111111111110011001101, fp1.rawVal);
	}*/

	// Now check float->double conversion as the
	// rest of the tests depend on it
	TEST(PositiveFixedToFloatConversionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);

		CHECK_CLOSE(3.2, Fix64ToFloat<8>(fp1.rawVal), 0.1);
	}

	TEST(NegativeFixedToFloatConversionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(-3.2);

		CHECK_CLOSE(-3.2, Fix64ToFloat<8>(fp1.rawVal), 0.1);
	}

}