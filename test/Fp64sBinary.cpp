//!
//! @file 				Fp64sBinary.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-07-24
//! @last-modified		2014-09-15
//! @brief 				Performs unit tests on the slow 64-bit fixed point binary operations.
//! @details
//!		See README.rst

//===== SYSTEM LIBRARIES =====//
// none

//===== USER LIBRARIES =====//
#include "MUnitTest/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MFixedPointApi.hpp"

using namespace Fp;

MTEST_GROUP(Fp64sBinaryTests)
{
	MTEST(EqualsTest)
	{
		Fp64s fp1 = Fp64s(5.6, 12);
		Fp64s fp2 = Fp64s(5.6, 12);
		
		CHECK(fp1 == fp2);
	}

	MTEST(NotEqualsTest)
	{
		Fp64s fp1 = Fp64s(10.6, 12);
		Fp64s fp2 = Fp64s(5.6, 12);
		
		CHECK(fp1 != fp2);
	}

	MTEST(GreaterThanTest)
	{
		Fp64s fp1 = Fp64s(10.6, 12);
		Fp64s fp2 = Fp64s(5.6, 12);
		
		CHECK(fp1 > fp2);
	}

	MTEST(LessThanTest)
	{
		Fp64s fp1 = Fp64s(3.3, 12);
		Fp64s fp2 = Fp64s(18.4, 12);
		
		CHECK(fp1 < fp2);
	}
}
