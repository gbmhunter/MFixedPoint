//!
//! @file 				Fp64fCompoundArithmetic.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-07-24
//! @last-modified		2014-09-15
//! @brief 				Performs unit tests on the fast 64-bit fixed point compound arithmetic.
//! @details
//!		See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

//===== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MFixedPointApi.hpp"

using namespace Fp;

MTEST_GROUP(Fp64fCompoundArithmeticTests)
{
	MTEST(CompoundAdditionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);
		Fp64f<8> fp2 = Fp64f<8>(0.6);
		
		CHECK_EQUAL(fp1.rawVal, 0b001100110011);
		
		fp1 += fp2;

		CHECK_CLOSE(3.8, (float)fp1, 0.1);
	}

	MTEST(CompoundSubtractionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);
		Fp64f<8> fp2 = Fp64f<8>(0.6);
		
		fp1 -= fp2;

		CHECK_CLOSE(2.6, (float)fp1, 0.1);
	}

	MTEST(CompoundMultiplicationTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);
		Fp64f<8> fp2 = Fp64f<8>(0.6);
		
		fp1 *= fp2;

		CHECK_CLOSE(1.92, (float)fp1, 0.1);
	}

	MTEST(CompoundDivisionTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.2);
		Fp64f<8> fp2 = Fp64f<8>(0.6);
		
		fp1 /= fp2;

		CHECK_CLOSE(5.33, (float)fp1, 0.1);
	}
	
	MTEST(CompoundModuloTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(20.2);
		Fp64f<8> fp2 = Fp64f<8>(1.5);
		
		fp1 %= fp2;
		//20.2 % 1.5 = 0.7
		
		CHECK_CLOSE(0.7, (float)fp1, 0.1);
	}
}
