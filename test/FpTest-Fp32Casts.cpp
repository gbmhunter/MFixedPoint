//!
//! @file 		FpTest-Fp32Casts.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/07/12
//! @brief 		Performs casting checks on the 32-bit fixed point library.
//! @details
//!				See README.rst in root dir for more info.

// 32-bit fixed-point library which also stores Q.
#include "../src/include/FixedPoint-Fp32Q.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Fp;

SUITE(Fp32CastTests)
{
	TEST(DoubleCastTest)
	{
		Fp32Q fp1 = Fp32Q(5.6, 12);
		double dbl1 = (double)fp1;
		
		CHECK_CLOSE(5.6, dbl1, 0.05);
	}
}