//!
//! @file 				Fp32fBinary.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-05-30
//! @last-modified		2014-09-15
//! @brief 				Performs unit tests on the fast 32-bit fixed point binary operations.
//! @details
//!						See README.rst in root dir for more info.

// System includes
// none

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/Fp32f.hpp"

using namespace Fp;

MTEST_GROUP(Fp32fBinaryTests)
{
	MTEST(EqualsTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(5.6);
		Fp32f<8> fp2 = Fp32f<8>(5.6);
		
		CHECK(fp1 == fp2);
	}

	MTEST(NotEqualsTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(10.6);
		Fp32f<8> fp2 = Fp32f<8>(5.6);
		
		CHECK(fp1 != fp2);
	}

	MTEST(GreaterThanTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(10.6);
		Fp32f<8> fp2 = Fp32f<8>(5.6);
		
		CHECK(fp1 > fp2);
	}

	MTEST(LessThanTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(3.3);
		Fp32f<8> fp2 = Fp32f<8>(18.4);
		
		CHECK(fp1 < fp2);
	}
}
