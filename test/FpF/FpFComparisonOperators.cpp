//!
//! \file 				FpFComparisonOperators.cpp
//! \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! \edited 			n/a
//! \created			2018-02-12
//! \last-modified		2018-02-12
//! \brief 				Performs unit tests on the fixed point FpF class.
//! \details
//!						See README.rst in root dir for more info.

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/FpF.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpFComparisonOperators) {

	MTEST(LessThanTwoFpF) {
		FpF32<8> fp1(1.11);
		FpF32<8> fp2(1.21);
        CHECK_EQUAL(fp1 < fp2, true);
	}

    MTEST(LessThanInt) {
        FpF32<8> fp1(1.11);
        CHECK_EQUAL(fp1 < (int)2, true);
    }

    MTEST(LessThanEqualToTwoFpF) {
        FpF32<8> fp1(2.22);
        FpF32<8> fp2(2.22);
        CHECK_EQUAL(fp1 <= fp2, true);
    }

    MTEST(LessThanEqualToInt) {
        FpF32<8> fp1(1.11);
        CHECK_EQUAL(fp1 <= 2, true);
    }

    MTEST(GreaterThanTwoFpF) {
        FpF32<8> fp1(5.01);
        FpF32<8> fp2(4.32);
        CHECK_EQUAL(fp1 > fp2, true);
    }

    MTEST(GreaterThanInt) {
        FpF32<8> fp1(-3.4);
        CHECK_EQUAL(fp1 > -4, true);
    }

    MTEST(GreaterThanEqualToTwoFpF) {
        FpF32<8> fp1(-12);
        FpF32<8> fp2(-12);
        CHECK_EQUAL(fp1 >= fp2, true);
    }

    MTEST(GreaterThanEqualToInt) {
        FpF32<8> fp1(-11.9);
        CHECK_EQUAL(fp1 >= -12, true);
    }

    MTEST(EqualToTwoFpFTrue) {
        FpF32<8> fp1(-12);
        FpF32<8> fp2(-12);
        CHECK_EQUAL(fp1 == fp2, true);
    }

    MTEST(EqualToTwoFpFFalse) {
        FpF32<8> fp1(-12);
        FpF32<8> fp2(-13);
        CHECK_EQUAL(fp1 == fp2, false);
    }

    MTEST(NotEqualToTwoFpFTrue) {
        FpF32<8> fp1(3.4);
        FpF32<8> fp2(3.8);
        CHECK_EQUAL(fp1 != fp2, true);
    }

    MTEST(NotEqualToTwoFpFFalse) {
        FpF32<8> fp1(3.82);
        FpF32<8> fp2(3.82);
        CHECK_EQUAL(fp1 != fp2, false);
    }

}