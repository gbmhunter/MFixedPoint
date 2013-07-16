//!
//! @file 		FpTest-Fp32CompoundArithmetic.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Performs unit tests on the 32-bit fixed point compound arithmetic.
//! @details
//!				See README.rst

// 32-bit fixed-point library
#include "../src/include/FixedPoint-Fp32.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp32Tests)
{

	TEST(CompoundAdditionTest)
	{
		Fp32<8> fp1 = Fp32<8>(3.2);
		Fp32<8> fp2 = Fp32<8>(0.6);
		
		fp1 += fp2;

		CHECK_CLOSE(3.8, Fix2Float<8>(fp1.rawVal), 0.1);
	}

	TEST(CompoundSubtractionTest)
	{
		Fp32<8> fp1 = Fp32<8>(3.2);
		Fp32<8> fp2 = Fp32<8>(0.6);
		
		fp1 -= fp2;

		CHECK_CLOSE(2.6, Fix2Float<8>(fp1.rawVal), 0.1);
	}

	TEST(CompoundMultiplicationTest)
	{
		Fp32<8> fp1 = Fp32<8>(3.2);
		Fp32<8> fp2 = Fp32<8>(0.6);
		
		fp1 *= fp2;

		CHECK_CLOSE(1.92, Fix2Float<8>(fp1.rawVal), 0.1);
	}

	TEST(CompoundDivisionTest)
	{
		Fp32<8> fp1 = Fp32<8>(3.2);
		Fp32<8> fp2 = Fp32<8>(0.6);
		
		fp1 /= fp2;

		CHECK_CLOSE(5.33, Fix2Float<8>(fp1.rawVal), 0.1);
	}
}