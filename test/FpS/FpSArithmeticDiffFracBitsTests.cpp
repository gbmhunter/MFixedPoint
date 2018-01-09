///
/// \file 				FpSArithmeticDiffFracBitsTests.cpp
/// \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
/// \edited 			n/a
/// \created			2013-07-24
/// \last-modified		2018-01-08
/// \brief 				Performs unit tests on the slow 32-bit fixed point compound arithmetic with variables that have
///						a different Q .
/// \details
///		See README.rst in root fir for more info.

// System includes
// none

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/FpS.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpSArithmeticDiffFracBitsTests) {
	
	MTEST(DiffQCompoundAdditionNoChangeTest) {
		FpS32 fp1(3.2, 8);
		FpS32 fp2(0.6, 12);		
		fp1 += fp2;
		CHECK_CLOSE(3.8, fp1.ToDouble(), 0.1);
		CHECK_EQUAL(fp1.GetNumFracBits(), 8);
		CHECK_EQUAL(fp2.GetNumFracBits(), 12);
	}
	
	MTEST(DiffQCompoundAdditionChangeTest) {
		FpS32 fp1(0.4, 16);
		FpS32 fp2(8.2, 5);
		
		// This should change the Q of fp1 to 5
		fp1 += fp2;

		CHECK_CLOSE(8.6, fp1.ToDouble(), 0.1);
		CHECK_EQUAL(fp1.GetNumFracBits(), 5);
		CHECK_EQUAL(fp2.GetNumFracBits(), 5);
	}
	
	MTEST(DiffQCompoundSubtractionNoChangeTest)	{
		FpS32 fp1(3.2, 7);
		FpS32 fp2(0.6, 22);
		fp1 -= fp2;
		CHECK_CLOSE(2.6, fp1.ToDouble(), 0.1);
		CHECK_EQUAL(fp1.GetNumFracBits(), 7);
		CHECK_EQUAL(fp2.GetNumFracBits(), 22);
	}
	
	MTEST(DiffQCompoundSubtractionChangeTest) {
		FpS32 fp1(2.3, 24);
		FpS32 fp2(13.0, 12);		
		fp1 -= fp2;
		CHECK_CLOSE(-10.7, fp1.ToDouble(), 0.1);
		CHECK_EQUAL(fp1.GetNumFracBits(), 12);
		CHECK_EQUAL(fp2.GetNumFracBits(), 12);
	}
	
	MTEST(DiffQCompoundMultiplicationNoChangeTest) {	
		FpS32 fp1(3.2, 6);
		FpS32 fp2(0.6, 12);		
		fp1 *= fp2;
		CHECK_CLOSE(1.92, fp1.ToDouble(), 0.1);
		CHECK_EQUAL(fp1.GetNumFracBits(), 6);
		CHECK_EQUAL(fp2.GetNumFracBits(), 12);
	}
	
	MTEST(DiffQCompoundMultiplicationChangeTest) {
		FpS32 fp1(3.2, 12);
		FpS32 fp2(0.6, 6);		
		fp1 *= fp2;
		CHECK_CLOSE(1.92, fp1.ToDouble(), 0.1);
		CHECK_EQUAL(fp1.GetNumFracBits(), 6);
		CHECK_EQUAL(fp2.GetNumFracBits(), 6);
	}

	MTEST(DiffQCompoundDivisionNoChangeTest) {
		FpS32 fp1(3.2, 12);
		FpS32 fp2(0.6, 18);		
		fp1 /= fp2;
		CHECK_CLOSE(5.33, fp1.ToDouble(), 0.1);
		CHECK_EQUAL(fp1.GetNumFracBits(), 12);
		CHECK_EQUAL(fp2.GetNumFracBits(), 18);
	}
	
	MTEST(DiffQCompoundDivisionChangeTest) {
		FpS32 fp1(3.2, 18);
		FpS32 fp2(0.6, 12);		
		fp1 /= fp2;
		CHECK_CLOSE(5.33, fp1.ToDouble(), 0.1);
		CHECK_EQUAL(fp1.GetNumFracBits(), 12);
		CHECK_EQUAL(fp2.GetNumFracBits(), 12);
	}
	
	MTEST(DiffQCompoundModuloNoChangeTest) {
		FpS32 fp1(20.2, 12);
		FpS32 fp2(1.5, 19);
		
		fp1 %= fp2;
		//20.2 % 1.5 = 0.7
		
		CHECK_CLOSE(0.7, fp1.ToDouble(), 0.1);
		CHECK_EQUAL(fp1.GetNumFracBits(), 12);
		CHECK_EQUAL(fp2.GetNumFracBits(), 19);
	}
	
	MTEST(DiffQCompoundModuloChangeTest) {
		FpS32 fp1(20.2, 19);
		FpS32 fp2(1.5, 12);
		
		fp1 %= fp2;
		//20.2 % 1.5 = 0.7
		CHECK_CLOSE(0.7, fp1.ToDouble(), 0.1);
		CHECK_EQUAL(fp1.GetNumFracBits(), 12);
		CHECK_EQUAL(fp2.GetNumFracBits(), 12);
	}
	
}
