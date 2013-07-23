//!
//! @file 		FpTest-Fp32fCasts.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/07/12
//! @brief 		Performs casting checks on the 32-bit fixed point library.
//! @details
//!				See README.rst in root dir for more info.

// Slow 32-bit fixed-point library.
#include "../src/include/FixedPoint-Fp32s.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp32sCastTests)
{
	TEST(PosInt32CastTest)
	{
		Fp32s fp1 = Fp32s(5.6, 12);
		int32_t myInt32 = (int32_t)fp1;
		
		CHECK_EQUAL(5, myInt32);
	}
	
	TEST(NegInt32CastTest)
	{
		Fp32s fp1 = Fp32s(-22.3, 12);
		int32_t myInt32 = (int32_t)fp1;
		
		CHECK_EQUAL(-22, myInt32);
	}

	TEST(PosFloatCastTest)
	{
		Fp32s fp1 = Fp32s(5.6, 12);
		float flo1 = (float)fp1;
		
		CHECK_CLOSE(5.6, flo1, 0.05);
	}
	
	TEST(NegFloatCastTest)
	{
		Fp32s fp1 = Fp32s(-2.2, 12);
		float flo1 = (float)fp1;
		
		CHECK_CLOSE(-2.2, flo1, 0.05);
	}
	
	TEST(PosDoubleCastTest)
	{
		Fp32s fp1 = Fp32s(5.6, 12);
		double dbl1 = (double)fp1;
		
		CHECK_CLOSE(5.6, dbl1, 0.05);
	}
	
	TEST(NegDoubleCastTest)
	{
		Fp32s fp1 = Fp32s(-25.6, 12);
		double dbl1 = (double)fp1;
		
		CHECK_CLOSE(-25.6, dbl1, 0.05);
	}
}