//!
//! @file 				Fp32sDifferentQArithmetic.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-07-24
//! @last-modified		2014-09-15
//! @brief 				Performs unit tests on the slow 32-bit fixed point compound arithmetic with variables that have
//!						a different Q .
//! @details
//!		See README.rst in root fir for more info.

// System includes
// none

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/Fp32s.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(Fp32sDiffQArithmeticTests)
{
	MTEST(DiffQCompoundAdditionNoChangeTest)
	{
		Fp32s fp1 = Fp32s(3.2, 8);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		fp1 += fp2;

		CHECK_CLOSE(3.8, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 8);
		CHECK_EQUAL(fp2.q, 12);
	}
	
	MTEST(DiffQCompoundAdditionChangeTest)
	{
		Fp32s fp1 = Fp32s(0.4, 16);
		Fp32s fp2 = Fp32s(8.2, 5);
		
		// This should change the Q of fp1 to 5
		fp1 += fp2;

		CHECK_CLOSE(8.6, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 5);
		CHECK_EQUAL(fp2.q, 5);
	}
	
	MTEST(DiffQCompoundSubtractionNoChangeTest)
	{
		Fp32s fp1 = Fp32s(3.2, 7);
		Fp32s fp2 = Fp32s(0.6, 22);
		
		fp1 -= fp2;

		CHECK_CLOSE(2.6, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 7);
		CHECK_EQUAL(fp2.q, 22);
	}
	
	MTEST(DiffQCompoundSubtractionChangeTest)
	{
		Fp32s fp1 = Fp32s(2.3, 24);
		Fp32s fp2 = Fp32s(13.0, 12);
		
		fp1 -= fp2;

		CHECK_CLOSE(-10.7, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 12);
		CHECK_EQUAL(fp2.q, 12);
	}
	
	MTEST(DiffQCompoundMultiplicationNoChangeTest)
	{
		Fp32s fp1 = Fp32s(3.2, 6);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		fp1 *= fp2;

		CHECK_CLOSE(1.92, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 6);
		CHECK_EQUAL(fp2.q, 12);
	}
	
	MTEST(DiffQCompoundMultiplicationChangeTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 6);
		
		fp1 *= fp2;

		CHECK_CLOSE(1.92, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 6);
		CHECK_EQUAL(fp2.q, 6);
	}

	MTEST(DiffQCompoundDivisionNoChangeTest)
	{
		Fp32s fp1 = Fp32s(3.2, 12);
		Fp32s fp2 = Fp32s(0.6, 18);
		
		fp1 /= fp2;

		CHECK_CLOSE(5.33, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 12);
		CHECK_EQUAL(fp2.q, 18);
	}
	
	MTEST(DiffQCompoundDivisionChangeTest)
	{
		Fp32s fp1 = Fp32s(3.2, 18);
		Fp32s fp2 = Fp32s(0.6, 12);
		
		fp1 /= fp2;

		CHECK_CLOSE(5.33, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 12);
		CHECK_EQUAL(fp2.q, 12);
	}
	
	MTEST(DiffQCompoundModuloNoChangeTest)
	{
		Fp32s fp1 = Fp32s(20.2, 12);
		Fp32s fp2 = Fp32s(1.5, 19);
		
		fp1 %= fp2;
		//20.2 % 1.5 = 0.7
		
		CHECK_CLOSE(0.7, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 12);
		CHECK_EQUAL(fp2.q, 19);
	}
	
	MTEST(DiffQCompoundModuloChangeTest)
	{
		Fp32s fp1 = Fp32s(20.2, 19);
		Fp32s fp2 = Fp32s(1.5, 12);
		
		fp1 %= fp2;
		//20.2 % 1.5 = 0.7
		
		CHECK_CLOSE(0.7, (double)fp1, 0.1);
		CHECK_EQUAL(fp1.q, 12);
		CHECK_EQUAL(fp2.q, 12);
	}
	
}
