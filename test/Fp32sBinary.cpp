//!
//! @file 				Fp32sBinary.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-05-30
//! @last-modified		2017-06-27
//! @brief 				Performs unit tests on the slow 32-bit fixed point binary operations.
//! @details
//!		See README.rst

//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

//===== USER LIBRARIES =====//
#include "MUnitTest/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MFixedPointApi.hpp"

using namespace Fp;

MTEST_GROUP(Fp32sBinaryTests)
{
	MTEST(EqualsTest)
	{
		Fp32s fp1 = Fp32s(5.6, 12);
		Fp32s fp2 = Fp32s(5.6, 12);
		
		CHECK(fp1 == fp2);
	}

	MTEST(NotEqualsTest)
	{
		Fp32s fp1 = Fp32s(10.6, 12);
		Fp32s fp2 = Fp32s(5.6, 12);
		
		CHECK(fp1 != fp2);
	}

	MTEST(GreaterThanTest)
	{
		Fp32s fp1 = Fp32s(10.6, 12);
		Fp32s fp2 = Fp32s(5.6, 12);
		
		CHECK(fp1 > fp2);
	}

	MTEST(LessThanTest)
	{
		Fp32s fp1 = Fp32s(3.3, 12);
		Fp32s fp2 = Fp32s(18.4, 12);
		
		CHECK(fp1 < fp2);
	}
}
