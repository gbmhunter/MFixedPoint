//!
//! @file 		FpTest-Fp32sBinary.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Performs unit tests on the slow 32-bit fixed point binary operations.
//! @details
//!				See README.rst

// Slow 32-bit fixed-point library
#include "../src/include/FixedPoint-Fp32s.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp32sBinaryTests)
{
	TEST(EqualsTest)
	{
		Fp32s fp1 = Fp32s(5.6, 12);
		Fp32s fp2 = Fp32s(5.6, 12);
		
		CHECK(fp1 == fp2);
	}

	TEST(NotEqualsTest)
	{
		Fp32s fp1 = Fp32s(10.6, 12);
		Fp32s fp2 = Fp32s(5.6, 12);
		
		CHECK(fp1 != fp2);
	}

	TEST(GreaterThanTest)
	{
		Fp32s fp1 = Fp32s(10.6, 12);
		Fp32s fp2 = Fp32s(5.6, 12);
		
		CHECK(fp1 > fp2);
	}

	TEST(LessThanTest)
	{
		Fp32s fp1 = Fp32s(3.3, 12);
		Fp32s fp2 = Fp32s(18.4, 12);
		
		CHECK(fp1 < fp2);
	}
}