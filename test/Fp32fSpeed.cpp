//!
//! @file 				Fp32fSpeed.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-05-30
//! @last-modified		2014-09-15
//! @brief 				Performs speed unit tests on the 32-bit fixed point maths.
//! @details
//!		See README.rst in root dir for more info.

// System includes
// none

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/Fp32f.hpp"

using namespace Fp;

MTEST_GROUP(Fp32fSpeedTests)
{
	MTEST(AddSpeedTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(5.6);
		Fp32f<8> fp2 = Fp32f<8>(8.9);
		Fp32f<8> fp3;
		
		{
			//IME_CONSTRAINT(1000);
			
			int x = 0;
			for(x = 0; x < 10000000; x++)
			{
				fp3 = fp1 + fp2;
			}
		
		}
	}
	
	MTEST(SubSpeedTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(5.6);
		Fp32f<8> fp2 = Fp32f<8>(8.9);
		Fp32f<8> fp3;
		
		{
			//UNITTEST_TIME_CONSTRAINT(2000);
			
			int x = 0;
			for(x = 0; x < 100000000; x++)
			{
				fp3 = fp1 - fp2;
			}
		
		}
	}

	MTEST(MultSpeedTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(5.6);
		Fp32f<8> fp2 = Fp32f<8>(5.6);
		Fp32f<8> fp3;

		{
			//UNITTEST_TIME_CONSTRAINT(2000);
			
			int x = 0;
			for(x = 0; x < 10000000; x++)
			{
				fp3 = fp1*fp2;
			}
		
			}
	}
	
	MTEST(DivSpeedTest)
	{
		Fp32f<8> fp1 = Fp32f<8>(21.6);
		Fp32f<8> fp2 = Fp32f<8>(5.6);
		Fp32f<8> fp3;

		{
			//UNITTEST_TIME_CONSTRAINT(2000);
			
			int x = 0;
			for(x = 0; x < 10000000; x++)
			{
				fp3 = fp1/fp2;
			}
		
			}
	}
}
