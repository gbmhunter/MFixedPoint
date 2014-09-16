//!
//! @file 				Fp64fTest.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-07-12
//! @last-modified		2014-09-15
//! @brief 				Performs unit tests on the 64-bit fixed point binary arithmetic.
//! @details
//!		See README.rst

//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

//===== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MFixedPointApi.hpp"

using namespace Fp;

MTEST_GROUP(Fp64fBinaryTests)
{
	MTEST(PosEqualsTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(5.6);
		Fp64f<8> fp2 = Fp64f<8>(5.6);
		Fp64f<8> fp3 = Fp64f<8>(8.9);
		
		CHECK_EQUAL(true, fp1 == fp2);
		CHECK_EQUAL(false, fp1 == fp3);
	}
	
	MTEST(NegEqualsTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(-2.8);
		Fp64f<8> fp2 = Fp64f<8>(-2.8);
		Fp64f<8> fp3 = Fp64f<8>(-8.9);
		
		CHECK_EQUAL(true, fp1 == fp2);
		CHECK_EQUAL(false, fp1 == fp3);
	}

	MTEST(PosNotEqualsTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(10.6);
		Fp64f<8> fp2 = Fp64f<8>(5.6);
		Fp64f<8> fp3 = Fp64f<8>(5.6);
		
		CHECK_EQUAL(true, fp1 != fp2);
		CHECK_EQUAL(false, fp2 != fp3);
	}
	
	MTEST(NegNotEqualsTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(-1.8);
		Fp64f<8> fp2 = Fp64f<8>(-8.9);
		Fp64f<8> fp3 = Fp64f<8>(-8.9);
		
		CHECK_EQUAL(true, fp1 != fp2);
		CHECK_EQUAL(false, fp2 != fp3);
	}

	MTEST(PosGreaterThanTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(10.6);
		Fp64f<8> fp2 = Fp64f<8>(5.6);
		Fp64f<8> fp3 = Fp64f<8>(5.6);
		
		CHECK_EQUAL(true, fp1 > fp2);
		CHECK_EQUAL(false, fp2 > fp3);
	}
	
	MTEST(NegGreaterThanTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(-123.3);
		Fp64f<8> fp2 = Fp64f<8>(-130.4);
		Fp64f<8> fp3 = Fp64f<8>(-130.4);
		
		CHECK_EQUAL(true, fp1 > fp2);
		CHECK_EQUAL(false, fp2 > fp3);
	}

	MTEST(PosLessThanTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.3);
		Fp64f<8> fp2 = Fp64f<8>(18.4);
		Fp64f<8> fp3 = Fp64f<8>(18.4);
		
		CHECK_EQUAL(true, fp1 < fp2);
		CHECK_EQUAL(false, fp2 < fp3);
	}
}
