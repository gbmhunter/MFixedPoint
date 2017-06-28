//!
//! @file 				Fp64fSpeed.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-05-30
//! @last-modified		2014-09-15
//! @brief 				Performs speed unit tests on the 64-bit fixed point maths.
//! @details
//!		See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
// none

//===== USER LIBRARIES =====//
#include "MUnitTest/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MFixedPointApi.hpp"

using namespace Fp;

MTEST_GROUP(Fp64fSpeedTests)
{
	MTEST(AddSpeedTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(5.6);
		Fp64f<8> fp2 = Fp64f<8>(8.9);
		Fp64f<8> fp3;

		{
			//UNITTEST_TIME_CONSTRAINT(1);
			
			int x = 0;
			for(x = 0; x < 10000; x++)
			{
				fp3 = fp1 + fp2;
			}
		
		}
	}
	
	MTEST(SubSpeedTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(5.6);
		Fp64f<8> fp2 = Fp64f<8>(8.9);
		Fp64f<8> fp3;

		{
			//UNITTEST_TIME_CONSTRAINT(1);
			
			int x = 0;
			for(x = 0; x < 10000; x++)
			{
				fp3 = fp1 - fp2;
			}
		
		}
	}

	MTEST(MultSpeedTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(5.6);
		Fp64f<8> fp2 = Fp64f<8>(5.6);
		Fp64f<8> fp3;

		{
			//UNITTEST_TIME_CONSTRAINT(1);
			
			int x = 0;
			for(x = 0; x < 10000; x++)
			{
				fp3 = fp1*fp2;
			}
		
			}
	}
	
	MTEST(DivSpeedTest)
	{
		Fp64f<8> fp1 = Fp64f<8>(21.6);
		Fp64f<8> fp2 = Fp64f<8>(5.6);
		Fp64f<8> fp3;

		{
			//UNITTEST_TIME_CONSTRAINT(1);
			
			int x = 0;
			for(x = 0; x < 10000; x++)
			{
				fp3 = fp1/fp2;
			}
		
			}
	}
}
