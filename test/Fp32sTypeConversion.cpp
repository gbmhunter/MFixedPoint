//!
//! @file 				Fp32sTypeConversion.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-05-30
//! @last-modified		2017-06-27
//! @brief 				Performs type conversion unit tests on the slow 32-bit fixed point library (Fp32s).
//! @details
//!		See README.rst in root dir for more info.

// System includes
// none

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/Fp32s.hpp"

using namespace Fp;

MTEST_GROUP(Fp32sTypeConversionTests)
{
	// Check double->fixed conversion first as the
	// rest of the tests depend on it
	MTEST(PositiveDoubleToFixedConversionTest)
	{
		Fp32s fp1 = Fp32s(3.2, 8);

		// The closest fixed point number this can be represented
		// as is Math.Round(3.2*2^8) = 819 = 0b001100110011
		CHECK_EQUAL(fp1.rawVal, (int32_t)0b001100110011);
	}

	MTEST(NegativeDoubleToFixedConversionTest)
	{
		Fp32s fp1 = Fp32s(-3.2, 8);

		// The closest fixed point number this can be represented
		// as is Math.Round(-3.2*2^8) = -819 = 0b11111111111111111111110011001101 (32-bit 2's compliment)
		CHECK_EQUAL(fp1.rawVal, (int32_t)0b11111111111111111111110011001101);
	}
	
	MTEST(PosInt32CastTest)
	{
		Fp32s fp1 = Fp32s(5.6, 12);
		int32_t myInt32 = (int32_t)fp1;
		
		CHECK_EQUAL(myInt32, 5);
	}
	
	MTEST(NegInt32CastTest)
	{
		Fp32s fp1 = Fp32s(-22.3, 12);
		int32_t myInt32 = (int32_t)fp1;
		
		// Rounds down to nearest int
		CHECK_EQUAL(myInt32, -23);
	}

	MTEST(PosFloatCastTest)
	{
		Fp32s fp1 = Fp32s(5.6, 12);
		float flo1 = (float)fp1;
		
		CHECK_CLOSE(5.6, flo1, 0.05);
	}
	
	MTEST(NegFloatCastTest)
	{
		Fp32s fp1 = Fp32s(-2.2, 12);
		float flo1 = (float)fp1;
		
		CHECK_CLOSE(-2.2, flo1, 0.05);
	}
	
	MTEST(PosDoubleCastTest)
	{
		Fp32s fp1 = Fp32s(5.6, 12);
		double dbl1 = (double)fp1;
		
		CHECK_CLOSE(5.6, dbl1, 0.05);
	}
	
	MTEST(NegDoubleCastTest)
	{
		Fp32s fp1 = Fp32s(-25.6, 12);
		double dbl1 = (double)fp1;
		
		CHECK_CLOSE(-25.6, dbl1, 0.05);
	}

}
