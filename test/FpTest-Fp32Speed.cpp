//!
//! @file 		FpTest-Fp32Speed.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Performs unit tests on the 32-bit fixed point binary operations.
//! @details
//!				See README.rst in root dir for more info.

// 32-bit fixed-point library
#include "../src/include/FixedPoint-Fp32.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp32SpeedTests)
{

	TEST(MultSpeedTest)
	{
		Fp32<8> fp1 = Fp32<8>(5.6);
		Fp32<8> fp2 = Fp32<8>(5.6);
		Fp32<8> fp3;

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
		Fp32<8> fp1 = Fp32<8>(21.6);
		Fp32<8> fp2 = Fp32<8>(5.6);
		Fp32<8> fp3;

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