//!
//! @file 				Fp32sCompoundArithmetic.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-07-24
//! @last-modified		2017-06-27
//! @brief 				Performs unit tests on the slow 32-bit fixed point compound arithmetic.
//! @details
//!		See README.rst in root fir for more info.

//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

//===== USER LIBRARIES =====//
#include "MUnitTest/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MFixedPointApi.hpp"

using namespace Fp;

MTEST_GROUP(Fp32sCompoundArithmeticTests)
{
	MTEST(CompoundAdditionTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		fp1 += fp2;

		CHECK_CLOSE(3.8, (double)fp1, 0.1);
	}

	MTEST(CompoundSubtractionTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		fp1 -= fp2;

		CHECK_CLOSE(2.6, (double)fp1, 0.1);
	}

	MTEST(CompoundMultiplicationTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		fp1 *= fp2;

		CHECK_CLOSE(1.92, (double)fp1, 0.1);
	}

	MTEST(CompoundDivisionTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		fp1 /= fp2;

		CHECK_CLOSE(5.33, (double)fp1, 0.1);
	}
	
	MTEST(CompoundModuloTest)
	{
		Fp32s fp1 = Fp32s(20.2, 12);
		Fp32s fp2 = Fp32s(1.5, 12);
		
		fp1 %= fp2;
		//20.2 % 1.5 = 0.7
		
		CHECK_CLOSE(0.7, (double)fp1, 0.1);
	}
}
