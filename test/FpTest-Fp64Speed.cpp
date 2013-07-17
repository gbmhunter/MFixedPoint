//!
//! @file 		FpTest-Fp64Speed.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Performs speed unit tests on the 64-bit fixed point maths.
//! @details
//!				See README.rst in root dir for more info.

// 64-bit fixed-point library
#include "../src/include/FixedPoint-Fp64.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp64SpeedTests)
{
	TEST(AddSpeedTest)
	{
		Fp64<8> fp1 = Fp64<8>(5.6);
		Fp64<8> fp2 = Fp64<8>(8.9);
		Fp64<8> fp3;

		{
			UNITTEST_TIME_CONSTRAINT(1);
			
			int x = 0;
			for(x = 0; x < 10000; x++)
			{
				fp3 = fp1 + fp2;
			}
		
		}
	}
	
	TEST(SubSpeedTest)
	{
		Fp64<8> fp1 = Fp64<8>(5.6);
		Fp64<8> fp2 = Fp64<8>(8.9);
		Fp64<8> fp3;

		{
			UNITTEST_TIME_CONSTRAINT(1);
			
			int x = 0;
			for(x = 0; x < 10000; x++)
			{
				fp3 = fp1 - fp2;
			}
		
		}
	}

	TEST(MultSpeedTest)
	{
		Fp64<8> fp1 = Fp64<8>(5.6);
		Fp64<8> fp2 = Fp64<8>(5.6);
		Fp64<8> fp3;

		{
			UNITTEST_TIME_CONSTRAINT(1);
			
			int x = 0;
			for(x = 0; x < 10000; x++)
			{
				fp3 = fp1*fp2;
			}
		
			}
	}
	
	TEST(DivSpeedTest)
	{
		Fp64<8> fp1 = Fp64<8>(21.6);
		Fp64<8> fp2 = Fp64<8>(5.6);
		Fp64<8> fp3;

		{
			UNITTEST_TIME_CONSTRAINT(1);
			
			int x = 0;
			for(x = 0; x < 10000; x++)
			{
				fp3 = fp1/fp2;
			}
		
			}
	}
}