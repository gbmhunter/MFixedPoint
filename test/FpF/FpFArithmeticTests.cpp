//!
//! \file 				FpFArithmeticTests.cpp
//! \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! \edited 			n/a
//! \created			2013-07-22
//! \last-modified		2018-01-10
//! \brief 				Performs unit tests on the fixed point FpF class.
//! \details
//!						See README.rst in root dir for more info.

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/FpF.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpFArithmeticTests) {

	// MTEST(ArithmeticOnReadme) {
	// 	FpS32 fp1(5.0, 8);
	// 	FpS32 fp2(1.5, 8);

	// 	printf("add = %.2f\n", (fp1 + fp2).ToDouble());
	// 	printf("sub = %.2f\n", (fp1 - fp2).ToDouble());
	// 	printf("mult = %.2f\n", (fp1 * fp2).ToDouble());
	// 	printf("div = %.2f\n", (fp1 / fp2).ToDouble());
	// }

	MTEST(AdditionSameNumFracBits) {
		FpF32<8> fp1(1.11);
		FpF32<8> fp2(2.22);
		FpF32<8> fp3 = fp1 + fp2;		
        CHECK_CLOSE(fp3.ToDouble(), 3.33, 0.1);
	}

	MTEST(Addition64SameFracBitsTest) {		
		FpF64<42> fp1(3.21);
		FpF64<42> fp2(12.789);		
		auto fp3 = fp1 + fp2;
		CHECK_CLOSE(fp3.ToDouble(), 3.21 + 12.789, 0.1);		
	}

	MTEST(NegativeAdditionTest)	{
		FpF32<12> fp1(-3.2);
		FpF32<12> fp2(-0.6);
		auto fp3 = fp1 + fp2;
		CHECK_CLOSE(fp3.ToDouble(), -3.8, 0.1);
	}

	MTEST(SubtractionPositive) {
		FpF32<8> fp1(34.2);
		FpF32<8> fp2(8.6);
		auto fp3 = fp1 - fp2;
        CHECK_CLOSE(fp3.ToDouble(), 34.2 - 8.6, 0.1);
	}

	MTEST(SubtractionNegative) {
		FpF32<8> fp1(5.8);
		FpF32<8> fp2(12.3);
		auto fp3 = fp1 - fp2;
        CHECK_CLOSE(fp3.ToDouble(), 5.8 - 12.3, 0.1);
	}

	MTEST(Multiplication) {
		FpF32<8> fp1(1.5);
		FpF32<8> fp2(5.0);
		auto fp3 = fp1 * fp2;		
        CHECK_CLOSE(fp3.ToDouble(), 7.5, 0.1);
	}

	MTEST(NegativeMultiplicationTest) {		
		FpF32<12> fp1(-3.2);
		FpF32<12> fp2(-0.6);		
		auto fp3 = fp1 * fp2;
		CHECK_CLOSE(fp3.ToDouble(), 1.92, 0.1);		
	}

	MTEST(PositiveDivisionTest)	{
		FpF32<12> fp1(3.2);
		FpF32<12> fp2(0.6);		
		auto fp3 = fp1 / fp2;
		CHECK_CLOSE(fp3.ToDouble(), 5.33, 0.1);
	}

	MTEST(NegativeDivisionTest) {
		FpF32<12> fp1(-3.2);
		FpF32<12> fp2(-0.6);	
		auto fp3 = fp1 / fp2;
		CHECK_CLOSE(fp3.ToDouble(), 5.33, 0.1);
	}

	MTEST(Modulus) {
		FpF32<10> fp1(5.1);
		FpF32<10> fp2(1.5);
		auto fp3 = fp1 % fp2;		
		CHECK_CLOSE(fp3.ToDouble(), 0.6, 0.1);
	}

}