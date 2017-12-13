//!
//! @file 				Fp64fTypeConversion.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-05-30
//! @last-modified		2017-06-27
//! @brief 				Performs type conversion unit tests on the fast 64-bit fixed point library.
//! @details
//!		See README.rst in root dir for more info.

// System includes
// none

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/Fp64f.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(Fp64fTypeConversionTests)
{

	// Check double->fixed conversion first as the
	// rest of the tests depend on it
	MTEST(PositiveDoubleToFixedConversionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);

		// The closest fixed point number this can be represented
		// as is Math.Round(3.2*2^8) = 819 = 0b001100110011
		CHECK_EQUAL(fp1.rawVal, (int32_t)0b001100110011);
	}

	MTEST(NegativeDoubleToFixedConversionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(-3.2);

		// The closest fixed point number this can be represented
		// as is Math.Round(-3.2*2^8) = -819 = 0b1111111111111111111111111111111111111111111111111111110011001101 (64-bit 2's compliment)
		CHECK_EQUAL(fp1.rawVal, (int32_t)0b1111111111111111111111111111111111111111111111111111110011001101);
	}

	// Now check fix->float conversion as the
	// rest of the tests depend on it
	MTEST(PositiveFixedToFloatConversionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);

		CHECK_CLOSE(3.2, (float)fp1, 0.1);
	}

	MTEST(NegativeFixedToFloatConversionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(-3.2);

		CHECK_CLOSE(-3.2, (float)fp1, 0.1);
	}
	
	// Now check fix->double conversion as the
	// rest of the tests depend on it
	MTEST(PositiveFixedToDoubleConversionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);

		CHECK_CLOSE(3.2, (double)fp1, 0.1);
		
		// This will be outside floats range
		fp1 = Fp64f<8>((double)(((int64_t)1 << 54) - 1));
		CHECK_CLOSE((double)(((int64_t)1 << 54) - 1), (double)fp1, 1e2);
	}

	MTEST(NegativeFixedToDoubleConversionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(-3.2);

		CHECK_CLOSE(-3.2, (double)fp1, 0.1);
		
		// This will be outside floats range
		fp1 = Fp64f<8>(-(double)(((int64_t)1 << 54)));
		CHECK_CLOSE(-(double)(((int64_t)1 << 54)), (double)fp1, 1e2);
	}

}
