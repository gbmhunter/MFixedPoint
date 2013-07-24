//!
//! @file 		FpTest-Fp64sTypeConversion.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/07/24
//! @brief 		Performs type conversion tests on the slow 64-bit fixed point library.
//! @details
//!				See README.rst in root dir for more info.

// Slow 64-bit fixed-point library.
#include "../src/include/FixedPoint-Fp64s.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp64sTypeConversionTests)
{
	// Check double->fixed conversion first as the
	// rest of the tests depend on it
	TEST(PositiveDoubleToFixedConversionTest)
	{
		Fp64s fp1 = Fp64s(3.2, 8);

		// The closest fixed point number this can be represented
		// as is Math.Round(3.2*2^8) = 819 = 0b001100110011
		CHECK_EQUAL((int32_t)0b001100110011, fp1.rawVal);
		CHECK_EQUAL(8, fp1.q);
	}

	TEST(NegativeDoubleToFixedConversionTest)
	{
		Fp64s fp1 = Fp64s(-3.2, 8);

		// The closest fixed point number this can be represented
		// as is Math.Round(-3.2*2^8) = -819 = 0b1111111111111111111111111111111111111111111111111111110011001101 (64-bit 2's compliment)
		CHECK_EQUAL((int64_t)0b1111111111111111111111111111111111111111111111111111110011001101, fp1.rawVal);
		CHECK_EQUAL(8, fp1.q);
	}

	TEST(PosInt32CastTest)
	{
		Fp64s fp1 = Fp64s(12.8, 12);
		int32_t myInt32 = (int32_t)fp1;
		
		CHECK_EQUAL(12, myInt32);
	}

	TEST(NegInt32CastTest)
	{
		Fp64s fp1 = Fp64s(-22.3, 12);
		int32_t myInt32 = (int32_t)fp1;
		
		// Rounds down to nearest int
		CHECK_EQUAL(-23, myInt32);
	}
	
	TEST(PosInt64CastTest)
	{
		Fp64s fp1 = Fp64s(5.6, 12);
		int64_t myInt64 = (int64_t)fp1;
		
		CHECK_EQUAL(5, myInt64);
	}
	
	TEST(NegInt64CastTest)
	{
		Fp64s fp1 = Fp64s(-43.2, 12);
		int64_t myInt64 = (int64_t)fp1;
		
		// Rounds down to nearest int
		CHECK_EQUAL(-44, myInt64);
	}

	TEST(PosFloatCastTest)
	{
		Fp64s fp1 = Fp64s(5.6, 12);
		float flo1 = (float)fp1;
		
		CHECK_CLOSE(5.6, flo1, 0.05);
	}
	
	TEST(NegFloatCastTest)
	{
		Fp64s fp1 = Fp64s(-2.2, 12);
		float flo1 = (float)fp1;
		
		CHECK_CLOSE(-2.2, flo1, 0.05);
	}
	
	TEST(PosDoubleCastTest)
	{
		Fp64s fp1 = Fp64s(5.6, 12);
		double dbl1 = (double)fp1;
		
		CHECK_CLOSE(5.6, dbl1, 0.05);
	}
	
	TEST(NegDoubleCastTest)
	{
		Fp64s fp1 = Fp64s(-25.6, 12);
		double dbl1 = (double)fp1;
		
		CHECK_CLOSE(-25.6, dbl1, 0.05);
	}
}