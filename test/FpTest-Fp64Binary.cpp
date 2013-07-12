//!
//! @file 		FpTest-Fp64Test.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/07/12
//! @brief 		Performs unit tests on the 64-bit fixed point binary arithmetic.
//! @details
//!				See README.rst

// 64-bit fixed-point library
#include "../src/include/FixedPoint-Fp64.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp64BinaryTests)
{
	TEST(PosEqualsTest)
	{
		Fp64<8> fp1 = Fp64<8>(5.6);
		Fp64<8> fp2 = Fp64<8>(5.6);
		Fp64<8> fp3 = Fp64<8>(8.9);
		
		CHECK_EQUAL(true, fp1 == fp2);
		CHECK_EQUAL(false, fp1 == fp3);
	}
	
	TEST(NegEqualsTest)
	{
		Fp64<8> fp1 = Fp64<8>(-2.8);
		Fp64<8> fp2 = Fp64<8>(-2.8);
		Fp64<8> fp3 = Fp64<8>(-8.9);
		
		CHECK_EQUAL(true, fp1 == fp2);
		CHECK_EQUAL(false, fp1 == fp3);
	}

	TEST(PosNotEqualsTest)
	{
		Fp64<8> fp1 = Fp64<8>(10.6);
		Fp64<8> fp2 = Fp64<8>(5.6);
		Fp64<8> fp3 = Fp64<8>(5.6);
		
		CHECK_EQUAL(true, fp1 != fp2);
		CHECK_EQUAL(false, fp2 != fp3);
	}
	
	TEST(NegNotEqualsTest)
	{
		Fp64<8> fp1 = Fp64<8>(-1.8);
		Fp64<8> fp2 = Fp64<8>(-8.9);
		Fp64<8> fp3 = Fp64<8>(-8.9);
		
		CHECK_EQUAL(true, fp1 != fp2);
		CHECK_EQUAL(false, fp2 != fp3);
	}

	TEST(PosGreaterThanTest)
	{
		Fp64<8> fp1 = Fp64<8>(10.6);
		Fp64<8> fp2 = Fp64<8>(5.6);
		Fp64<8> fp3 = Fp64<8>(5.6);
		
		CHECK_EQUAL(true, fp1 > fp2);
		CHECK_EQUAL(false, fp2 > fp3);
	}
	
	TEST(NegGreaterThanTest)
	{
		Fp64<8> fp1 = Fp64<8>(-123.3);
		Fp64<8> fp2 = Fp64<8>(-130.4);
		Fp64<8> fp3 = Fp64<8>(-130.4);
		
		CHECK_EQUAL(true, fp1 > fp2);
		CHECK_EQUAL(false, fp2 > fp3);
	}

	TEST(PosLessThanTest)
	{
		Fp64<8> fp1 = Fp64<8>(3.3);
		Fp64<8> fp2 = Fp64<8>(18.4);
		Fp64<8> fp3 = Fp64<8>(18.4);
		
		CHECK_EQUAL(true, fp1 < fp2);
		CHECK_EQUAL(false, fp2 < fp3);
	}
}