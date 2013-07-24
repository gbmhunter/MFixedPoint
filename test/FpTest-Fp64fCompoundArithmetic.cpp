//!
//! @file 		FpTest-Fp64fCompoundArithmetic.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/07/24
//! @brief 		Performs unit tests on the fast 64-bit fixed point compound arithmetic.
//! @details
//!				See README.rst in root dir for more info.

// Fast 64-bit fixed-point library
#include "../src/include/FixedPoint-Fp64f.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp64fCompoundArithmeticTests)
{
	TEST(CompoundAdditionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);
		Fp64f<8> fp2 = Fp64f<8>(0.6);
		
		CHECK_EQUAL(0b001100110011, fp1.rawVal);
		
		fp1 += fp2;

		CHECK_CLOSE(3.8, Fix64ToFloat<8>(fp1.rawVal), 0.1);
	}

	TEST(CompoundSubtractionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);
		Fp64f<8> fp2 = Fp64f<8>(0.6);
		
		fp1 -= fp2;

		CHECK_CLOSE(2.6, Fix64ToFloat<8>(fp1.rawVal), 0.1);
	}

	TEST(CompoundMultiplicationTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);
		Fp64f<8> fp2 = Fp64f<8>(0.6);
		
		fp1 *= fp2;

		CHECK_CLOSE(1.92, Fix64ToFloat<8>(fp1.rawVal), 0.1);
	}

	TEST(CompoundDivisionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);
		Fp64f<8> fp2 = Fp64f<8>(0.6);
		
		fp1 /= fp2;

		CHECK_CLOSE(5.33, Fix64ToFloat<8>(fp1.rawVal), 0.1);
	}
	
	TEST(CompoundModuloTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(20.2);
		Fp64f<8> fp2 = Fp64f<8>(1.5);
		
		fp1 %= fp2;
		//20.2 % 1.5 = 0.7
		
		CHECK_CLOSE(0.7, Fix64ToFloat<8>(fp1.rawVal), 0.1);
	}
}