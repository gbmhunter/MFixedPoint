//!
//! @file 				Fp64sDifferentQArithmetic.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-07-24
//! @last-modified		2017-06-27
//! @brief 				Performs unit tests on the slow 64-bit fixed point compound arithmetic with variables that have
//!						a different Q .
//! @details
//!		See README.rst in root fir for more info.

// System includes
// none

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/Fp64s.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(Fp64sDiffQArithmeticTests)
{
	MTEST(DiffQCompoundAdditionNoChangeTest)
	{
		Fp64s fp1 = Fp64s(3.2, 8);
		Fp64s fp2 = Fp64s(0.6, 12);
		
		fp1 += fp2;

		CHECK_CLOSE(3.8, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 8);
		CHECK_EQUAL(fp2.q, 12);
	}
	
	MTEST(DiffQCompoundAdditionChangeTest)
	{
		Fp64s fp1 = Fp64s(0.4, 16);
		Fp64s fp2 = Fp64s(8.2, 5);
		
		// This should change the Q of fp1 to 5
		fp1 += fp2;

		CHECK_CLOSE(8.6, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 5);
		CHECK_EQUAL(fp2.q, 5);
	}
	
	MTEST(DiffQCompoundSubtractionNoChangeTest)
	{
		Fp64s fp1 = Fp64s(3.2, 7);
		Fp64s fp2 = Fp64s(0.6, 22);
		
		fp1 -= fp2;

		CHECK_CLOSE(2.6, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 7);
		CHECK_EQUAL(fp2.q, 22);
	}
	
	MTEST(DiffQCompoundSubtractionChangeTest)
	{
		Fp64s fp1 = Fp64s(2.3, 24);
		Fp64s fp2 = Fp64s(13.0, 12);
		
		fp1 -= fp2;

		CHECK_CLOSE(-10.7, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 12);
		CHECK_EQUAL(fp2.q, 12);
	}
	
	MTEST(DiffQCompoundMultiplicationNoChangeTest)
	{
		Fp64s fp1 = Fp64s(3.2, 6);
		Fp64s fp2 = Fp64s(0.6, 12);
		
		fp1 *= fp2;

		CHECK_CLOSE(1.92, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 6);
		CHECK_EQUAL(fp2.q, 12);
	}
	
	MTEST(DiffQCompoundMultiplicationChangeTest)
	{
		Fp64s fp1 = Fp64s(3.2, 12);
		Fp64s fp2 = Fp64s(0.6, 6);
		
		fp1 *= fp2;

		CHECK_CLOSE(1.92, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 6);
		CHECK_EQUAL(fp2.q, 6);
	}

	MTEST(DiffQCompoundDivisionNoChangeTest)
	{
		Fp64s fp1 = Fp64s(3.2, 12);
		Fp64s fp2 = Fp64s(0.6, 18);
		
		fp1 /= fp2;

		CHECK_CLOSE(5.33, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 12);
		CHECK_EQUAL(fp2.q, 18);
	}
	
	MTEST(DiffQCompoundDivisionChangeTest)
	{
		Fp64s fp1 = Fp64s(3.2, 18);
		Fp64s fp2 = Fp64s(0.6, 12);
		
		fp1 /= fp2;

		CHECK_CLOSE(5.33, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 12);
		CHECK_EQUAL(fp2.q, 12);
	}
	
	MTEST(DiffQCompoundModuloNoChangeTest)
	{
		Fp64s fp1 = Fp64s(20.2, 12);
		Fp64s fp2 = Fp64s(1.5, 19);
		
		fp1 %= fp2;
		//20.2 % 1.5 = 0.7
		
		CHECK_CLOSE(0.7, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 12);
		CHECK_EQUAL(fp2.q, 19);
	}
	
	MTEST(DiffQCompoundModuloChangeTest)
	{
		Fp64s fp1 = Fp64s(20.2, 19);
		Fp64s fp2 = Fp64s(1.5, 12);
		
		fp1 %= fp2;
		//20.2 % 1.5 = 0.7
		
		CHECK_CLOSE(0.7, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 12);
		CHECK_EQUAL(fp2.q, 12);
	}
	
}
