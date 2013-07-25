//!
//! @file 		FpTest-Fp32fArithmetic.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Performs unit tests on the 32-bit fixed point arithmetic.
//! @details
//!				See README.rst in root dir for more info.

// Fast 32-bit fixed-point library
#include "../src/include/FixedPoint-Fp32f.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp32fArithmeticTests)
{

	TEST(PositiveAdditionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);
		Fp32f<8> fp2 = Fp32f<8>(0.6);
		
		Fp32f<8> fp3 = fp1 + fp2;

		CHECK_CLOSE(3.8, (float)fp3, 0.1);
	}

	TEST(NegativeAdditionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(-3.2);
		Fp32f<8> fp2 = Fp32f<8>(-0.6);
		
		Fp32f<8> fp3 = fp1 + fp2;

		CHECK_CLOSE(-3.8, (float)fp3, 0.1);
	}

	TEST(PositiveSubtractionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);
		Fp32f<8> fp2 = Fp32f<8>(0.6);
		
		Fp32f<8> fp3 = fp1 - fp2;

		CHECK_CLOSE(2.6, (float)fp3, 0.1);
	}

	TEST(NegativeSubtractionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(-3.2);
		Fp32f<8> fp2 = Fp32f<8>(-0.6);
		
		Fp32f<8> fp3 = fp1 - fp2;

		CHECK_CLOSE(-2.6, (float)fp3, 0.1);
	}

	TEST(PositiveMultiplicationTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);
		Fp32f<8> fp2 = Fp32f<8>(0.6);
		
		Fp32f<8> fp3 = fp1 * fp2;

		CHECK_CLOSE(1.92, (float)fp3, 0.1);
	}

	TEST(NegativeMultiplicationTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(-3.2);
		Fp32f<8> fp2 = Fp32f<8>(-0.6);
		
		Fp32f<8> fp3 = fp1 * fp2;

		CHECK_CLOSE(1.92, (float)fp3, 0.1);
	}

	TEST(PositiveDivisionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);
		Fp32f<8> fp2 = Fp32f<8>(0.6);
		
		Fp32f<8> fp3 = fp1 / fp2;

		CHECK_CLOSE(5.33, (float)fp3, 0.1);
	}

	TEST(NegativeDivisionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(-3.2);
		Fp32f<8> fp2 = Fp32f<8>(-0.6);
		
		Fp32f<8> fp3 = fp1 / fp2;

		CHECK_CLOSE(5.33, (float)fp3, 0.1);
	}

	TEST(ModuloTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(20.2);
		Fp32f<8> fp2 = Fp32f<8>(1.5);
		
		Fp32f<8> fp3 = fp1 % fp2;
		//20.2 % 1.5 = 0.7
		CHECK_CLOSE(0.7, (float)fp3, 0.1);
	}

}