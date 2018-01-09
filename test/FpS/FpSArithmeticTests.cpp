//!
//! \file 				FpSArithmeticTests.cpp
//! \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! \edited 			n/a
//! \created			2013-07-22
//! \last-modified		2018-01-08
//! \brief 				Performs unit tests on the fixed point FpS class.
//! \details
//!						See README.rst in root dir for more info.

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/FpS.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpSArithmeticTests) {

	// MTEST(ArithmeticOnReadme) {
	// 	FpS<int32_t> fp1(5.0, 8);
	// 	FpS<int32_t> fp2(1.5, 8);

	// 	printf("add = %.2f\n", (fp1 + fp2).ToDouble());
	// 	printf("sub = %.2f\n", (fp1 - fp2).ToDouble());
	// 	printf("mult = %.2f\n", (fp1 * fp2).ToDouble());
	// 	printf("div = %.2f\n", (fp1 / fp2).ToDouble());
	// }

	MTEST(AdditionSameNumFracBits) {
		FpS<int32_t> fp1(1.11, 8);
		FpS<int32_t> fp2(2.22, 8);
		FpS<int32_t> fp3 = fp1 + fp2;		
        CHECK_CLOSE(fp3.ToDouble(), 3.33, 0.1);
	}

	MTEST(AdditionDiffNumFracBits) {
		FpS<int32_t> fp1(34.2, 7);
		FpS<int32_t> fp2(8.6, 10);
		FpS<int32_t> fp3 = fp1 + fp2;
        CHECK_CLOSE(fp3.ToDouble(), 34.2 + 8.6, 0.1);
		CHECK_EQUAL(fp3.GetNumFracBits(), 7);
	}

	MTEST(NegativeAdditionTest)	{
		FpS<int32_t> fp1(-3.2, 12);
		FpS<int32_t> fp2(-0.6, 12);
		auto fp3 = fp1 + fp2;
		CHECK_CLOSE(-3.8, fp3.ToDouble(), 0.1);
	}

	MTEST(SubtractionPositive) {
		FpS<int32_t> fp1(34.2, 8);
		FpS<int32_t> fp2(8.6, 8);
		FpS<int32_t> fp3 = fp1 - fp2;
        CHECK_EQUAL(fp3.GetRawVal(), (int32_t)(34.2 * (1 << 8)) - (int32_t)(8.6 * (1 << 8)));
	}

	MTEST(SubtractionNegative) {
		FpS<int32_t> fp1(5.8, 8);
		FpS<int32_t> fp2(12.3, 8);
		FpS<int32_t> fp3 = fp1 - fp2;
        CHECK_CLOSE(fp3.ToDouble(), 5.8 - 12.3, 0.1);
	}

	MTEST(SubtractionDiffNumFracBits) {
		FpS<int32_t> fp1(12.34, 20);
		FpS<int32_t> fp2(2.2, 5);
		FpS<int32_t> fp3 = fp1 - fp2;
        CHECK_CLOSE(fp3.ToDouble(), 12.34 - 2.2, 0.1);
		CHECK_EQUAL(fp3.GetNumFracBits(), 5);
	}

	MTEST(MultiplicationSameNumFracBits) {
		FpS<int32_t> fp1(1.5, 8);
		FpS<int32_t> fp2(5.0, 8);
		FpS<int32_t> fp3 = fp1 * fp2;		
        CHECK_CLOSE(fp3.ToDouble(), 7.5, 0.1);
	}

	MTEST(NegativeMultiplicationTest) {
		FpS<int32_t> fp1(-3.2, 12);
		FpS<int32_t> fp2(-0.6, 12);
		
		auto fp3 = fp1 * fp2;
		CHECK_CLOSE(1.92, fp3.ToDouble(), 0.1);
	}

	MTEST(PositiveDivisionTest)	{
		FpS<int32_t> fp1(3.2, 12);
		FpS<int32_t> fp2(0.6, 12);		
		auto fp3 = fp1 / fp2;
		CHECK_CLOSE(5.33, fp3.ToDouble(), 0.1);
	}

	MTEST(NegativeDivisionTest) {
		FpS<int32_t> fp1(-3.2, 12);
		FpS<int32_t> fp2(-0.6, 12);	
		auto fp3 = fp1 / fp2;
		CHECK_CLOSE(5.33, fp3.ToDouble(), 0.1);
	}

	MTEST(Modulus) {
		FpS<int32_t> fp1(5.1, 10);
		FpS<int32_t> fp2(1.5, 8);
		FpS<int32_t> fp3 = fp1 % fp2;		
		CHECK_CLOSE(fp3.ToDouble(), 0.6, 0.1);
	}

}