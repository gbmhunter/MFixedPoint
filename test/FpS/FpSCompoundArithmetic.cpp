//!
//! @file 				FpSCompoundArithmetic.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-07-24
//! @last-modified		2018-01-08
//! @brief 				Performs unit tests on the FpS fixed point compound arithmetic.
//! @details
//!		See README.rst in root fir for more info.

// System includes
// none

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/FpS.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpSCompoundArithmeticTests)
{
	MTEST(CompoundAdditionTest)	{
		FpS32 fp1(3.2, 12);
		FpS32 fp2(0.6, 12);
		fp1 += fp2;
		CHECK_CLOSE(3.8, (double)fp1, 0.1);
	}

	MTEST(CompoundSubtractionTest) {
		FpS32 fp1(3.2, 12);
		FpS32 fp2(0.6, 12);		
		fp1 -= fp2;
		CHECK_CLOSE(2.6, (double)fp1, 0.1);
	}

	MTEST(CompoundMultiplicationTest) {
		FpS32 fp1(3.2, 12);
		FpS32 fp2(0.6, 12);		
		fp1 *= fp2;
		CHECK_CLOSE(1.92, (double)fp1, 0.1);
	}

	MTEST(CompoundDivisionTest) {
		FpS32 fp1(3.2, 12);
		FpS32 fp2(0.6, 12);		
		fp1 /= fp2;
		CHECK_CLOSE(5.33, (double)fp1, 0.1);
	}
	
	MTEST(CompoundModuloTest) {
		FpS32 fp1(20.2, 12);
		FpS32 fp2(1.5, 12);		
		fp1 %= fp2;
		//20.2 % 1.5 = 0.7
		CHECK_CLOSE(0.7, (double)fp1, 0.1);
	}
}
