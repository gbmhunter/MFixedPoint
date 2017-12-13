//!
//! @file 				Fp64fBinary.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (blog.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-07-12
//! @last-modified		2017-06-27
//! @brief 				Performs unit tests on the 64-bit fixed point binary arithmetic.
//! @details
//!		See README.rst

// System includes
// none

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/Fp64f.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(Fp64fBinaryTests)
{
	MTEST(PosEqualsTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(5.6);
		Fp64f<8> fp2 = Fp64f<8>(5.6);
		Fp64f<8> fp3 = Fp64f<8>(8.9);
		
		CHECK_EQUAL(fp1 == fp2, true);
		CHECK_EQUAL(fp1 == fp3, false);
	}
	
	MTEST(NegEqualsTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(-2.8);
		Fp64f<8> fp2 = Fp64f<8>(-2.8);
		Fp64f<8> fp3 = Fp64f<8>(-8.9);
		
		CHECK_EQUAL(fp1 == fp2, true);
		CHECK_EQUAL(fp1 == fp3, false);
	}

	MTEST(PosNotEqualsTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(10.6);
		Fp64f<8> fp2 = Fp64f<8>(5.6);
		Fp64f<8> fp3 = Fp64f<8>(5.6);
		
		CHECK_EQUAL(fp1 != fp2, true);
		CHECK_EQUAL(fp2 != fp3, false);
	}
	
	MTEST(NegNotEqualsTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(-1.8);
		Fp64f<8> fp2 = Fp64f<8>(-8.9);
		Fp64f<8> fp3 = Fp64f<8>(-8.9);
		
		CHECK_EQUAL(fp1 != fp2, true);
		CHECK_EQUAL(fp2 != fp3, false);
	}

	MTEST(PosGreaterThanTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(10.6);
		Fp64f<8> fp2 = Fp64f<8>(5.6);
		Fp64f<8> fp3 = Fp64f<8>(5.6);
		
		CHECK_EQUAL(fp1 > fp2, true);
		CHECK_EQUAL(fp2 > fp3, false);
	}
	
	MTEST(NegGreaterThanTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(-123.3);
		Fp64f<8> fp2 = Fp64f<8>(-130.4);
		Fp64f<8> fp3 = Fp64f<8>(-130.4);
		
		CHECK_EQUAL(fp1 > fp2, true);
		CHECK_EQUAL(fp2 > fp3, false);
	}

	MTEST(PosLessThanTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(3.3);
		Fp64f<8> fp2 = Fp64f<8>(18.4);
		Fp64f<8> fp3 = Fp64f<8>(18.4);
		
		CHECK_EQUAL(fp1 < fp2, true);
		CHECK_EQUAL(fp2 < fp3, false);
	}
}
