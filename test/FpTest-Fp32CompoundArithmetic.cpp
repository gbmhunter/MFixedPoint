//!
//! @file 		FpTest-Fp32fCompoundArithmetic.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Performs unit tests on the 32-bit fixed point compound arithmetic.
//! @details
//!				See README.rst

// 32-bit fixed-point library
#include "../src/include/FixedPoint-Fp32f.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp32fTests)
{

	TEST(CompoundAdditionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);
		Fp32f<8> fp2 = Fp32f<8>(0.6);
		
		fp1 += fp2;

		CHECK_CLOSE(3.8, Fix32ToFloat<8>(fp1.rawVal), 0.1);
	}

	TEST(CompoundSubtractionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);
		Fp32f<8> fp2 = Fp32f<8>(0.6);
		
		fp1 -= fp2;

		CHECK_CLOSE(2.6, Fix32ToFloat<8>(fp1.rawVal), 0.1);
	}

	TEST(CompoundMultiplicationTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);
		Fp32f<8> fp2 = Fp32f<8>(0.6);
		
		fp1 *= fp2;

		CHECK_CLOSE(1.92, Fix32ToFloat<8>(fp1.rawVal), 0.1);
	}

	TEST(CompoundDivisionTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.2);
		Fp32f<8> fp2 = Fp32f<8>(0.6);
		
		fp1 /= fp2;

		CHECK_CLOSE(5.33, Fix32ToFloat<8>(fp1.rawVal), 0.1);
	}
}