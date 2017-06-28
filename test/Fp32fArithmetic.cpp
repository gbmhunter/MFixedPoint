//!
//! @file 				Fp32fArithmetic.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-05-30
//! @last-modified		2017-06-27
//! @brief 				Performs unit tests on the 32-bit fixed point arithmetic.
//! @details
//!						See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
// none

//===== USER LIBRARIES =====//
#include "MUnitTest/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MFixedPointApi.hpp"


using namespace Fp;

MTEST_GROUP(Fp32fArithmeticTests)
{

	MTEST(PositiveAdditionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);
		Fp32f<8> fp2 = Fp32f<8>(0.6);
		
		Fp32f<8> fp3 = fp1 + fp2;

		CHECK_CLOSE(3.8, (float)fp3, 0.1);
	}

	MTEST(NegativeAdditionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(-3.2);
		Fp32f<8> fp2 = Fp32f<8>(-0.6);
		
		Fp32f<8> fp3 = fp1 + fp2;

		CHECK_CLOSE(-3.8, (float)fp3, 0.1);
	}

	MTEST(PositiveSubtractionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);
		Fp32f<8> fp2 = Fp32f<8>(0.6);
		
		Fp32f<8> fp3 = fp1 - fp2;

		CHECK_CLOSE(2.6, (float)fp3, 0.1);
	}

	MTEST(NegativeSubtractionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(-3.2);
		Fp32f<8> fp2 = Fp32f<8>(-0.6);
		
		Fp32f<8> fp3 = fp1 - fp2;

		CHECK_CLOSE(-2.6, (float)fp3, 0.1);
	}

	MTEST(PositiveMultiplicationTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);
		Fp32f<8> fp2 = Fp32f<8>(0.6);
		
		Fp32f<8> fp3 = fp1 * fp2;

		CHECK_CLOSE(1.92, (float)fp3, 0.1);
	}

	MTEST(NegativeMultiplicationTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(-3.2);
		Fp32f<8> fp2 = Fp32f<8>(-0.6);
		
		Fp32f<8> fp3 = fp1 * fp2;

		CHECK_CLOSE(1.92, (float)fp3, 0.1);
	}

	MTEST(PositiveDivisionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);
		Fp32f<8> fp2 = Fp32f<8>(0.6);
		
		Fp32f<8> fp3 = fp1 / fp2;

		CHECK_CLOSE(5.33, (float)fp3, 0.1);
	}

	MTEST(NegativeDivisionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(-3.2);
		Fp32f<8> fp2 = Fp32f<8>(-0.6);
		
		Fp32f<8> fp3 = fp1 / fp2;

		CHECK_CLOSE(5.33, (float)fp3, 0.1);
	}

	MTEST(ModuloTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(20.2);
		Fp32f<8> fp2 = Fp32f<8>(1.5);
		
		Fp32f<8> fp3 = fp1 % fp2;
		//20.2 % 1.5 = 0.7
		CHECK_CLOSE(0.7, (float)fp3, 0.1);
	}

}
