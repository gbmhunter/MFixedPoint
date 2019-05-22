//!
//! \file 				FpSArithmeticTests.cpp
//! \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! \edited 			n/a
//! \created			2013-07-22
//! \last-modified		2019-05-22
//! \brief 				Performs unit tests on the fixed point FpS class.
//! \details
//!						See README.rst in root dir for more info.

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/FpS.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpSArithmeticTests) {

	MTEST(AdditionSameNumFracBits) {
		FpS32 fp1(1.11, 8);
		FpS32 fp2(2.22, 8);
		FpS32 fp3 = fp1 + fp2;		
        CHECK_CLOSE(fp3.ToDouble(), 3.33, 0.1);
	}

	MTEST(AdditionDiffNumFracBits) {
		FpS32 fp1(34.2, 7);
		FpS32 fp2(8.6, 10);
		FpS32 fp3 = fp1 + fp2;
        CHECK_CLOSE(fp3.ToDouble(), 34.2 + 8.6, 0.1);
		CHECK_EQUAL(fp3.GetNumFracBits(), 7);
	}

	MTEST(NegativeAdditionTest)	{
		FpS32 fp1(-3.2, 12);
		FpS32 fp2(-0.6, 12);
		auto fp3 = fp1 + fp2;
		CHECK_CLOSE(-3.8, fp3.ToDouble(), 0.1);
	}

	MTEST(Addition64SameFracBitsTest) {		
		FpS64 fp1(3.21, 42);
		FpS64 fp2(12.789, 42);		
		auto fp3 = fp1 + fp2;
		CHECK_CLOSE(fp3.ToDouble(), 3.21 + 12.789, 0.1);		
	}

	MTEST(Addition64DiffFracBitsTest) {		
		FpS64 fp1(3.21, 42);
		FpS64 fp2(12.789, 50);		
		auto fp3 = fp1 + fp2;
		CHECK_CLOSE(fp3.ToDouble(), 3.21 + 12.789, 0.1);		
	}

	MTEST(SubtractionPositive) {
		FpS32 fp1(34.2, 8);
		FpS32 fp2(8.6, 8);
		FpS32 fp3 = fp1 - fp2;
        CHECK_EQUAL(fp3.GetRawVal(), (int32_t)(34.2 * (1 << 8)) - (int32_t)(8.6 * (1 << 8)));
	}

	MTEST(SubtractionNegative) {
		FpS32 fp1(5.8, 8);
		FpS32 fp2(12.3, 8);
		FpS32 fp3 = fp1 - fp2;
        CHECK_CLOSE(fp3.ToDouble(), 5.8 - 12.3, 0.1);
	}

	MTEST(SubtractionDiffNumFracBits) {
		FpS32 fp1(12.34, 20);
		FpS32 fp2(2.2, 5);
		FpS32 fp3 = fp1 - fp2;
        CHECK_CLOSE(fp3.ToDouble(), 12.34 - 2.2, 0.1);
		CHECK_EQUAL(fp3.GetNumFracBits(), 5);
	}

	MTEST(MultiplicationSameNumFracBits) {
		FpS32 fp1(1.5, 8);
		FpS32 fp2(5.0, 8);
		FpS32 fp3 = fp1 * fp2;		
        CHECK_CLOSE(fp3.ToDouble(), 7.5, 0.1);
	}

	MTEST(NegativeMultiplicationTest) {
		FpS32 fp1(-3.2, 12);
		FpS32 fp2(-0.6, 12);
		
		auto fp3 = fp1 * fp2;
		CHECK_CLOSE(1.92, fp3.ToDouble(), 0.1);
	}

	MTEST(OverflowMultiplicationTest) {
		FpS<int64_t, int64_t> fp1(-4000.0, 20);
		FpS<int64_t, int64_t> fp2(-0.01, 20);
		auto fp3 = fp1 * fp2;
		CHECK_CLOSE(fp3.ToDouble(), 40.0, 0.1);		
	}

	MTEST(PositiveDivisionTest)	{
		FpS32 fp1(3.2, 12);
		FpS32 fp2(0.6, 12);		
		auto fp3 = fp1 / fp2;
		CHECK_CLOSE(5.33, fp3.ToDouble(), 0.1);
	}

	MTEST(NegativeDivisionTest) {
		FpS32 fp1(-3.2, 12);
		FpS32 fp2(-0.6, 12);	
		auto fp3 = fp1 / fp2;
		CHECK_CLOSE(5.33, fp3.ToDouble(), 0.1);
	}

	MTEST(Modulus) {
		FpS32 fp1(5.1, 10);
		FpS32 fp2(1.5, 8);
		FpS32 fp3 = fp1 % fp2;		
		CHECK_CLOSE(fp3.ToDouble(), 0.6, 0.1);
	}

}