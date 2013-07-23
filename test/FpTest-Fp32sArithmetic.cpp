//!
//! @file 		FpTest-Fp32sArithmetic.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/07/24
//! @brief 		Performs unit tests on the slow 32-bit fixed point arithmetic.
//! @details
//!				See README.rst in root dir for more info.

// Slow 32-bit fixed-point library
#include "../src/include/FixedPoint-Fp32s.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp32sArithmeticTests)
{
	TEST(PositiveAdditionTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		Fp32s fp3 = fp1 + fp2;

		CHECK_CLOSE(3.8, (double)fp3, 0.1);
	}
	
	TEST(NegativeAdditionTest)
	{
		Fp32s fp1 = Fp32s(-3.2, 12);
		Fp32s fp2 = Fp32s(-0.6, 12);
		
		Fp32s fp3 = fp1 + fp2;

		CHECK_CLOSE(-3.8, (double)fp3, 0.1);
	}
	
	TEST(PositiveSubtractionTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		Fp32s fp3 = fp1 - fp2;

		CHECK_CLOSE(2.6, (double)fp3, 0.1);
	}

	TEST(NegativeSubtractionTest)
	{
		Fp32s fp1 = Fp32s(-3.2, 12);
		Fp32s fp2 = Fp32s(-0.6, 12);
		
		Fp32s fp3 = fp1 - fp2;

		CHECK_CLOSE(-2.6, (double)fp3, 0.1);
	}
	
	TEST(PositiveMultiplicationTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		Fp32s fp3 = fp1 * fp2;

		CHECK_CLOSE(1.92, (double)fp3, 0.1);
	}

	TEST(NegativeMultiplicationTest)
	{
		Fp32s fp1 = Fp32s(-3.2, 12);
		Fp32s fp2 = Fp32s(-0.6, 12);
		
		Fp32s fp3 = fp1 * fp2;

		CHECK_CLOSE(1.92, (double)fp3, 0.1);
	}
	
	TEST(PositiveDivisionTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		Fp32s fp3 = fp1 / fp2;

		CHECK_CLOSE(5.33, (double)fp3, 0.1);
	}

	TEST(NegativeDivisionTest)
	{
		Fp32s fp1 = Fp32s(-3.2, 12);
		Fp32s fp2 = Fp32s(-0.6, 12);
		
		Fp32s fp3 = fp1 / fp2;

		CHECK_CLOSE(5.33, (double)fp3, 0.1);
	}
	
	TEST(ModuloTest)
	{
		Fp32s fp1 = Fp32s(20.2, 12);
		Fp32s fp2 = Fp32s(1.5, 12);
		
		Fp32s fp3 = fp1 % fp2;
		//20.2 % 1.5 = 0.7
		CHECK_CLOSE(0.7, (double)fp3, 0.1);
	}
}