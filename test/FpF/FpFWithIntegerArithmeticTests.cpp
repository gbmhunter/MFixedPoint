//!
//! \file 				FpFWithIntegerArithmeticTests.cpp
//! \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! \edited 			n/a
//! \created			2018-02-11
//! \last-modified		2018-02-11
//! \brief 				Performs unit tests on the fixed point FpF class.
//! \details
//!						See README.rst in root dir for more info.

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/FpF.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpFWithIntegerArithmeticTests) {


	MTEST(Addition) {
		FpF32<8> fp1(1.11);
		FpF32<8> fp3 = fp1 + (int)8;
        CHECK_CLOSE(fp3.ToDouble(), 9.11, 0.1);
	}

    MTEST(SubtractionPositive) {
        std::cout << "Start test..." << std::endl;
        FpF32<8> fp1(34.2);
        FpF32<8> fp3 = fp1 - (int)8;
        CHECK_CLOSE(fp3.ToDouble(), 34.2 - 8, 0.1);
    }

	MTEST(SubtractionNegative)	{
		FpF32<12> fp1(-3.2);
		auto fp3 = fp1 - (int)5;
		CHECK_CLOSE(fp3.ToDouble(), -3.2 - 5.0, 0.1);
	}

	MTEST(Multiplication) {
		FpF32<8> fp1(1.5);
		auto fp3 = fp1 * 5;
        CHECK_CLOSE(fp3.ToDouble(), 1.5*5, 0.1);
	}

	MTEST(NegativeMultiplicationTest) {
		FpF32<12> fp1(-3.2);
		auto fp3 = fp1 * - 4;
		CHECK_CLOSE(fp3.ToDouble(), -3.2*-4, 0.1);
	}

	MTEST(PositiveDivisionTest)	{
		FpF32<12> fp1(3.2);
		auto fp3 = fp1 / 8;
		CHECK_CLOSE(fp3.ToDouble(), 3.2/8.0, 0.1);
	}

	MTEST(NegativeDivisionTest) {
		FpF32<12> fp1(-3.2);
		FpF32<12> fp2(-2.0);
		auto fp3 = fp1 / fp2;
		CHECK_CLOSE(fp3.ToDouble(), -3.2/-2.0, 0.1);
	}

}