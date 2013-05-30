//!
//! @file 		Fp32Test.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Performs unit tests on the 32-bit fixed point library (Fp32).
//! @details
//!				See README.rst

// 32-bit fixed-point library
#include "../src/include/Fp32.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

TEST(BasicTest)
{
	// Create two 32-bit fixed-point numbers with 24 decimal bits and 8 fractional bits.
	// This constructor converts from doubles.
	Fp32<8> fp1 = Fp32<8>(3.2);
	Fp32<8> fp2 = Fp32<8>(0.6);
	
	Fp32<8> fp3 = fp1 + fp2;
	// Performing a quick fixed-point addition
	CHECK_CLOSE(3.8, Fix2Float<8>(fp3.intValue), 0.1);
}

int main()
{
	// Run unit tests
	return UnitTest::RunAllTests();
}