//!
//! @file 		FpTest-Fp64fSpeed.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Performs speed unit tests on the 64-bit fixed point maths.
//! @details
//!				See README.rst in root dir for more info.

// 64-bit fixed-point library
#include "../src/include/FixedPoint-Fp64f.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp64fSpeedTests)
{
	TEST(AddSpeedTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(5.6);
		Fp64f<8> fp2 = Fp64f<8>(8.9);
		Fp64f<8> fp3;

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
		Fp64f<8> fp1 = Fp64f<8>(5.6);
		Fp64f<8> fp2 = Fp64f<8>(8.9);
		Fp64f<8> fp3;

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
		Fp64f<8> fp1 = Fp64f<8>(5.6);
		Fp64f<8> fp2 = Fp64f<8>(5.6);
		Fp64f<8> fp3;

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
		Fp64f<8> fp1 = Fp64f<8>(21.6);
		Fp64f<8> fp2 = Fp64f<8>(5.6);
		Fp64f<8> fp3;

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