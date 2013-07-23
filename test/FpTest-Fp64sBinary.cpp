//!
//! @file 		FpTest-Fp64sBinary.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/07/24
//! @brief 		Performs unit tests on the slow 64-bit fixed point binary operations.
//! @details
//!				See README.rst

// Slow 64-bit fixed-point library
#include "../src/include/FixedPoint-Fp64s.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp64sBinaryTests)
{
	TEST(EqualsTest)
	{
		Fp64s fp1 = Fp64s(5.6, 12);
		Fp64s fp2 = Fp64s(5.6, 12);
		
		CHECK(fp1 == fp2);
	}

	TEST(NotEqualsTest)
	{
		Fp64s fp1 = Fp64s(10.6, 12);
		Fp64s fp2 = Fp64s(5.6, 12);
		
		CHECK(fp1 != fp2);
	}

	TEST(GreaterThanTest)
	{
		Fp64s fp1 = Fp64s(10.6, 12);
		Fp64s fp2 = Fp64s(5.6, 12);
		
		CHECK(fp1 > fp2);
	}

	TEST(LessThanTest)
	{
		Fp64s fp1 = Fp64s(3.3, 12);
		Fp64s fp2 = Fp64s(18.4, 12);
		
		CHECK(fp1 < fp2);
	}
}