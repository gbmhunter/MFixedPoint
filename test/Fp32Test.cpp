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

// Check double->fixed conversion first as the
// rest of the tests depend on it
TEST(PositiveDoubleToFixedConversionTest)
{
	Fp32<8> fp1 = Fp32<8>(3.2);

	// The closest fixed point number this can be represented
	// as is Math.Round(3.2*2^8) = 819 = 0b001100110011
	CHECK_EQUAL(0b001100110011, fp1.intValue);
}

TEST(NegativeDoubleToFixedConversionTest)
{
	Fp32<8> fp1 = Fp32<8>(-3.2);

	// The closest fixed point number this can be represented
	// as is Math.Round(-3.2*2^8) = -819 = 0b11111111111111111111110011001101 (32-bit 2's compliment)
	CHECK_EQUAL(0b11111111111111111111110011001101, fp1.intValue);
}

// Now check float->double conversion as the
// rest of the tests depend on it
TEST(PositiveFixedToFloatConversionTest)
{
	Fp32<8> fp1 = Fp32<8>(3.2);

	CHECK_CLOSE(3.2, Fix2Float<8>(fp1.intValue), 0.1);
}

TEST(NegativeFixedToFloatConversionTest)
{
	Fp32<8> fp1 = Fp32<8>(-3.2);

	CHECK_CLOSE(-3.2, Fix2Float<8>(fp1.intValue), 0.1);
}

TEST(PositiveAdditionTest)
{
	Fp32<8> fp1 = Fp32<8>(3.2);
	Fp32<8> fp2 = Fp32<8>(0.6);
	
	Fp32<8> fp3 = fp1 + fp2;

	CHECK_CLOSE(3.8, Fix2Float<8>(fp3.intValue), 0.1);
}

TEST(NegativeAdditionTest)
{
	Fp32<8> fp1 = Fp32<8>(-3.2);
	Fp32<8> fp2 = Fp32<8>(-0.6);
	
	Fp32<8> fp3 = fp1 + fp2;

	CHECK_CLOSE(-3.8, Fix2Float<8>(fp3.intValue), 0.1);
}

TEST(PositiveSubtractionTest)
{
	Fp32<8> fp1 = Fp32<8>(3.2);
	Fp32<8> fp2 = Fp32<8>(0.6);
	
	Fp32<8> fp3 = fp1 - fp2;

	CHECK_CLOSE(2.6, Fix2Float<8>(fp3.intValue), 0.1);
}

TEST(NegativeSubtractionTest)
{
	Fp32<8> fp1 = Fp32<8>(-3.2);
	Fp32<8> fp2 = Fp32<8>(-0.6);
	
	Fp32<8> fp3 = fp1 - fp2;

	CHECK_CLOSE(-2.6, Fix2Float<8>(fp3.intValue), 0.1);
}

TEST(PositiveMultiplicationTest)
{
	Fp32<8> fp1 = Fp32<8>(3.2);
	Fp32<8> fp2 = Fp32<8>(0.6);
	
	Fp32<8> fp3 = fp1 * fp2;

	CHECK_CLOSE(1.92, Fix2Float<8>(fp3.intValue), 0.1);
}

TEST(NegativeMultiplicationTest)
{
	Fp32<8> fp1 = Fp32<8>(-3.2);
	Fp32<8> fp2 = Fp32<8>(-0.6);
	
	Fp32<8> fp3 = fp1 * fp2;

	CHECK_CLOSE(1.92, Fix2Float<8>(fp3.intValue), 0.1);
}

TEST(PositiveDivisionTest)
{
	Fp32<8> fp1 = Fp32<8>(3.2);
	Fp32<8> fp2 = Fp32<8>(0.6);
	
	Fp32<8> fp3 = fp1 / fp2;

	CHECK_CLOSE(5.33, Fix2Float<8>(fp3.intValue), 0.1);
}

TEST(NegativeDivisionTest)
{
	Fp32<8> fp1 = Fp32<8>(-3.2);
	Fp32<8> fp2 = Fp32<8>(-0.6);
	
	Fp32<8> fp3 = fp1 / fp2;

	CHECK_CLOSE(5.33, Fix2Float<8>(fp3.intValue), 0.1);
}

TEST(CompoundAdditionTest)
{
	Fp32<8> fp1 = Fp32<8>(3.2);
	Fp32<8> fp2 = Fp32<8>(0.6);
	
	fp1 += fp2;

	CHECK_CLOSE(3.8, Fix2Float<8>(fp1.intValue), 0.1);
}

TEST(CompoundSubtractionTest)
{
	Fp32<8> fp1 = Fp32<8>(3.2);
	Fp32<8> fp2 = Fp32<8>(0.6);
	
	fp1 -= fp2;

	CHECK_CLOSE(2.6, Fix2Float<8>(fp1.intValue), 0.1);
}

TEST(CompoundMultiplicationTest)
{
	Fp32<8> fp1 = Fp32<8>(3.2);
	Fp32<8> fp2 = Fp32<8>(0.6);
	
	fp1 *= fp2;

	CHECK_CLOSE(1.92, Fix2Float<8>(fp1.intValue), 0.1);
}

TEST(CompoundDivisionTest)
{
	Fp32<8> fp1 = Fp32<8>(3.2);
	Fp32<8> fp2 = Fp32<8>(0.6);
	
	fp1 /= fp2;

	CHECK_CLOSE(5.33, Fix2Float<8>(fp1.intValue), 0.1);
}

TEST(ModuloTest)
{
	Fp32<8> fp1 = Fp32<8>(20.2);
	Fp32<8> fp2 = Fp32<8>(1.5);
	
	Fp32<8> fp3 = fp1 % fp2;
	//20.2 % 1.5 = 0.7
	CHECK_CLOSE(0.7, Fix2Float<8>(fp3.intValue), 0.1);
}

//=============== BINARY OPERATORS ===============//

TEST(EqualsTest)
{
	Fp32<8> fp1 = Fp32<8>(5.6);
	Fp32<8> fp2 = Fp32<8>(5.6);
	
	CHECK(fp1 == fp2);
}

TEST(NotEqualsTest)
{
	Fp32<8> fp1 = Fp32<8>(10.6);
	Fp32<8> fp2 = Fp32<8>(5.6);
	
	CHECK(fp1 != fp2);
}

TEST(GreaterThanTest)
{
	Fp32<8> fp1 = Fp32<8>(10.6);
	Fp32<8> fp2 = Fp32<8>(5.6);
	
	CHECK(fp1 > fp2);
}

TEST(LessThanTest)
{
	Fp32<8> fp1 = Fp32<8>(3.3);
	Fp32<8> fp2 = Fp32<8>(18.4);
	
	CHECK(fp1 < fp2);
}

int main()
{
	// Run unit tests
	return UnitTest::RunAllTests();
}