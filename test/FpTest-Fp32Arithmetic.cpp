//!
//! @file 		FpTest-Fp32Arithmetic.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Performs unit tests on the 32-bit fixed point arithmetic.
//! @details
//!				See README.rst

// 32-bit fixed-point library
#include "../src/include/FixedPoint-Fp32.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp32Tests)
{

	TEST(PositiveAdditionTest)
	{
		Fp32<8> fp1 = Fp32<8>(3.2);
		Fp32<8> fp2 = Fp32<8>(0.6);
		
		Fp32<8> fp3 = fp1 + fp2;

		CHECK_CLOSE(3.8, Fix2Float<8>(fp3.rawVal), 0.1);
	}

	TEST(NegativeAdditionTest)
	{
		Fp32<8> fp1 = Fp32<8>(-3.2);
		Fp32<8> fp2 = Fp32<8>(-0.6);
		
		Fp32<8> fp3 = fp1 + fp2;

		CHECK_CLOSE(-3.8, Fix2Float<8>(fp3.rawVal), 0.1);
	}

	TEST(PositiveSubtractionTest)
	{
		Fp32<8> fp1 = Fp32<8>(3.2);
		Fp32<8> fp2 = Fp32<8>(0.6);
		
		Fp32<8> fp3 = fp1 - fp2;

		CHECK_CLOSE(2.6, Fix2Float<8>(fp3.rawVal), 0.1);
	}

	TEST(NegativeSubtractionTest)
	{
		Fp32<8> fp1 = Fp32<8>(-3.2);
		Fp32<8> fp2 = Fp32<8>(-0.6);
		
		Fp32<8> fp3 = fp1 - fp2;

		CHECK_CLOSE(-2.6, Fix2Float<8>(fp3.rawVal), 0.1);
	}

	TEST(PositiveMultiplicationTest)
	{
		Fp32<8> fp1 = Fp32<8>(3.2);
		Fp32<8> fp2 = Fp32<8>(0.6);
		
		Fp32<8> fp3 = fp1 * fp2;

		CHECK_CLOSE(1.92, Fix2Float<8>(fp3.rawVal), 0.1);
	}

	TEST(NegativeMultiplicationTest)
	{
		Fp32<8> fp1 = Fp32<8>(-3.2);
		Fp32<8> fp2 = Fp32<8>(-0.6);
		
		Fp32<8> fp3 = fp1 * fp2;

		CHECK_CLOSE(1.92, Fix2Float<8>(fp3.rawVal), 0.1);
	}

	TEST(PositiveDivisionTest)
	{
		Fp32<8> fp1 = Fp32<8>(3.2);
		Fp32<8> fp2 = Fp32<8>(0.6);
		
		Fp32<8> fp3 = fp1 / fp2;

		CHECK_CLOSE(5.33, Fix2Float<8>(fp3.rawVal), 0.1);
	}

	TEST(NegativeDivisionTest)
	{
		Fp32<8> fp1 = Fp32<8>(-3.2);
		Fp32<8> fp2 = Fp32<8>(-0.6);
		
		Fp32<8> fp3 = fp1 / fp2;

		CHECK_CLOSE(5.33, Fix2Float<8>(fp3.rawVal), 0.1);
	}

	TEST(ModuloTest)
	{
		Fp32<8> fp1 = Fp32<8>(20.2);
		Fp32<8> fp2 = Fp32<8>(1.5);
		
		Fp32<8> fp3 = fp1 % fp2;
		//20.2 % 1.5 = 0.7
		CHECK_CLOSE(0.7, Fix2Float<8>(fp3.rawVal), 0.1);
	}

}