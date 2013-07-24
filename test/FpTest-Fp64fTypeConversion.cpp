//!
//! @file 		FpTest-Fp64fTypeConversion.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Performs type conversion unit tests on the fast 64-bit fixed point library.
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

	TEST(NegativeDoubleToFixedConversionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(-3.2);

		// The closest fixed point number this can be represented
		// as is Math.Round(-3.2*2^8) = -819 = 0b1111111111111111111111111111111111111111111111111111110011001101 (64-bit 2's compliment)
		CHECK_EQUAL((int32_t)0b1111111111111111111111111111111111111111111111111111110011001101, fp1.rawVal);
	}

	// Now check fix->float conversion as the
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
	
	// Now check fix->double conversion as the
	// rest of the tests depend on it
	TEST(PositiveFixedToDoubleConversionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);

		CHECK_CLOSE(3.2, Fix64ToDouble<8>(fp1.rawVal), 0.1);
		
		// This will be outside floats range
		fp1 = Fp64f<8>((double)(((int64_t)1 << 54) - 1));
		CHECK_CLOSE((double)(((int64_t)1 << 54) - 1), Fix64ToDouble<8>(fp1.rawVal), 1e2);
	}

	TEST(NegativeFixedToDoubleConversionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(-3.2);

		CHECK_CLOSE(-3.2, Fix64ToDouble<8>(fp1.rawVal), 0.1);
		
		// This will be outside floats range
		fp1 = Fp64f<8>(-(double)(((int64_t)1 << 54)));
		CHECK_CLOSE(-(double)(((int64_t)1 << 54)), Fix64ToDouble<8>(fp1.rawVal), 1e2);
	}

}