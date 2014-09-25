//!
//! @file 				Fp32fToFpTypeConversion.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-05-30
//! @last-modified		2014-09-15
//! @brief 				Performs type conversion unit tests on the 32-bit fixed point library (Fp32f).
//! @details
//!		See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

//===== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MFixedPointApi.hpp"

using namespace Fp;

MTEST_GROUP(Fp32fTypeConversionTests)
{

	// Check double->fixed conversion first as the
	// rest of the tests depend on it
	MTEST(PositiveDoubleToFixedConversionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);

		// The closest fixed point number this can be represented
		// as is Math.Round(3.2*2^8) = 819 = 0b001100110011
		CHECK_EQUAL(fp1.rawVal, (int32_t)0b001100110011);
	}

	MTEST(NegativeDoubleToFixedConversionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(-3.2);

		// The closest fixed point number this can be represented
		// as is Math.Round(-3.2*2^8) = -819 = 0b11111111111111111111110011001101 (32-bit 2's compliment)
		CHECK_EQUAL(fp1.rawVal, (int32_t)0b11111111111111111111110011001101);
	}

	// Now check float->fix conversion as the
	// rest of the tests depend on it
	MTEST(PositiveFixedToFloatConversionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);

		CHECK_CLOSE(3.2, (float)fp1, 0.1);
	}

	// Now check float->fix conversion as the
	// rest of the tests depend on it
	MTEST(PositiveFixedToFloatConversionTest2)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);

		CHECK_CLOSE(3.2, (float)fp1, 0.1);
	}
	
	MTEST(NegativeFixedToFloatConversionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(-3.2);

		CHECK_CLOSE(-3.2, (float)fp1, 0.1);
	}
	
	MTEST(NegativeFixedToFloatConversionTest2)
	{
		Fp32f<8> fp1 = Fp32f<8>(-3.2);

		CHECK_CLOSE(-3.2, (float)fp1, 0.1);
	}
	
	// Now check fix->double conversion as the
	// rest of the tests depend on it
	MTEST(PositiveFixedToDoubleConversionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);

		CHECK_CLOSE(3.2, (double)fp1, 0.1);
		
		// This will be outside floats range
		fp1 = Fp32f<8>((double)((1 << 23) - 1));
		CHECK_CLOSE((double)((1 << 23) - 1), (double)fp1, 1);
	}

	MTEST(NegativeFixedToDoubleConversionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(-3.2);

		CHECK_CLOSE(-3.2, (double)fp1, 0.1);
		
		// This will be outside floats range
		fp1 = Fp32f<8>(-(double)((1 << 23)));
		CHECK_CLOSE(-(double)((1 << 23)), (double)fp1, 1);
	}

}
