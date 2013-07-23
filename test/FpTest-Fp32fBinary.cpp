//!
//! @file 		FpTest-Fp32fBinary.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Performs unit tests on the fast 32-bit fixed point binary operations.
//! @details
//!				See README.rst

// Fast 32-bit fixed-point library
#include "../src/include/FixedPoint-Fp32f.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp32fBinaryTests)
{
	TEST(EqualsTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(5.6);
		Fp32f<8> fp2 = Fp32f<8>(5.6);
		
		CHECK(fp1 == fp2);
	}

	TEST(NotEqualsTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(10.6);
		Fp32f<8> fp2 = Fp32f<8>(5.6);
		
		CHECK(fp1 != fp2);
	}

	TEST(GreaterThanTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(10.6);
		Fp32f<8> fp2 = Fp32f<8>(5.6);
		
		CHECK(fp1 > fp2);
	}

	TEST(LessThanTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.3);
		Fp32f<8> fp2 = Fp32f<8>(18.4);
		
		CHECK(fp1 < fp2);
	}
}