//!
//! @file 				Fp32sArithmetic.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-07-24
//! @last-modified		2017-06-27
//! @brief 				Performs unit tests on the slow 32-bit fixed point arithmetic.
//! @details
//!		See README.rst in root dir for more info.

// System includes
// none

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/Fp32s.hpp"

using namespace Fp;

MTEST_GROUP(Fp32sArithmeticTests)
{
	MTEST(PositiveAdditionTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		Fp32s fp3 = fp1 + fp2;

		CHECK_CLOSE(3.8, (double)fp3, 0.1);
	}
	
	MTEST(NegativeAdditionTest)
	{
		Fp32s fp1 = Fp32s(-3.2, 12);
		Fp32s fp2 = Fp32s(-0.6, 12);
		
		Fp32s fp3 = fp1 + fp2;

		CHECK_CLOSE(-3.8, (double)fp3, 0.1);
	}
	
	MTEST(PositiveSubtractionTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		Fp32s fp3 = fp1 - fp2;

		CHECK_CLOSE(2.6, (double)fp3, 0.1);
	}

	MTEST(NegativeSubtractionTest)
	{
		Fp32s fp1 = Fp32s(-3.2, 12);
		Fp32s fp2 = Fp32s(-0.6, 12);
		
		Fp32s fp3 = fp1 - fp2;

		CHECK_CLOSE(-2.6, (double)fp3, 0.1);
	}
	
	MTEST(PositiveMultiplicationTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		Fp32s fp3 = fp1 * fp2;

		CHECK_CLOSE(1.92, (double)fp3, 0.1);
	}

	MTEST(NegativeMultiplicationTest)
	{
		Fp32s fp1 = Fp32s(-3.2, 12);
		Fp32s fp2 = Fp32s(-0.6, 12);
		
		Fp32s fp3 = fp1 * fp2;

		CHECK_CLOSE(1.92, (double)fp3, 0.1);
	}
	
	MTEST(PositiveDivisionTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		Fp32s fp3 = fp1 / fp2;

		CHECK_CLOSE(5.33, (double)fp3, 0.1);
	}

	MTEST(NegativeDivisionTest)
	{
		Fp32s fp1 = Fp32s(-3.2, 12);
		Fp32s fp2 = Fp32s(-0.6, 12);
		
		Fp32s fp3 = fp1 / fp2;

		CHECK_CLOSE(5.33, (double)fp3, 0.1);
	}
	
	MTEST(ModuloTest)
	{
		Fp32s fp1 = Fp32s(20.2, 12);
		Fp32s fp2 = Fp32s(1.5, 12);
		
		Fp32s fp3 = fp1 % fp2;
		//20.2 % 1.5 = 0.7
		CHECK_CLOSE(0.7, (double)fp3, 0.1);
	}
}
