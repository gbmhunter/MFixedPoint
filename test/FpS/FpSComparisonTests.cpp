//!
//! @file 				FpSComparisonTests.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-05-30
//! @last-modified		2018-01-08
//! @brief 				Performs unit tests on the FpS fixed point binary operations.
//! @details
//!		See README.rst

// System includes
// none

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/FpS.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpSComparisonTests) {

	MTEST(EqualsTest) {
		FpS32 fp1(5.6, 12);
		FpS32 fp2(5.6, 12);		
		CHECK(fp1 == fp2);
	}

	MTEST(NegEqualsTest) {
		FpS32 fp1(-2.8, 8);
		FpS32 fp2(-2.8, 8);
		FpS32 fp3(-8.9, 8);		
		CHECK_EQUAL(fp1 == fp2, true);
		CHECK_EQUAL(fp1 == fp3, false);
	}

	MTEST(NotEqualsTest) {
		FpS32 fp1(10.6, 12);
		FpS32 fp2(5.6, 12);	
		CHECK(fp1 != fp2);
	}

	MTEST(GreaterThanPos) {
		FpS32 fp1(10.6, 12);
		FpS32 fp2(5.6, 12);
		FpS32 fp3(13.2, 12);	
		FpS32 fp4(10.6, 12);	
		CHECK_EQUAL(fp1 > fp2, true);
		CHECK_EQUAL(fp1 > fp3, false);
		CHECK_EQUAL(fp1 > fp4, false); // These are equal
	}

	MTEST(GreaterThanNeg) {
		FpS32 fp1(-10.6, 12);
		FpS32 fp2(-5.6, 12);
		FpS32 fp3(-13.2, 12);		
		CHECK_EQUAL(fp1 > fp2, false);
		CHECK_EQUAL(fp1 > fp3, true);
	}

	MTEST(LessThanPos)	{
		FpS32 fp1(3.3, 12);
		FpS32 fp2(18.4, 12);
		FpS32 fp3(2.89, 12);
		CHECK_EQUAL(fp1 < fp2, true);
		CHECK_EQUAL(fp1 < fp3, false);
	}

	MTEST(GreaterThanOrEqPos) {
		FpS32 fp1(10.6, 12);
		FpS32 fp2(10.6, 12);		
		CHECK_EQUAL(fp1 >= fp2, true);		
	}

	MTEST(LessThanOrEqPos) {
		FpS32 fp1(10.6, 12);
		FpS32 fp2(10.6, 12);
		FpS32 fp3(8.92, 12);
		CHECK_EQUAL(fp1 <= fp2, true);
		CHECK_EQUAL(fp1 <= fp3, false);
	}

}
