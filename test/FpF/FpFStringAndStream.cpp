//!
//! \file 				FpFStringAndStream.cpp
//! \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! \edited 			n/a
//! \created			2018-02-11
//! \last-modified		2018-02-11
//! \brief 				Performs unit tests on the fixed point FpF class.
//! \details
//!						See README.rst in root dir for more info.

// System includes
#include <sstream>

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/FpF.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpFStringAndStream) {

    MTEST(StringTest1)	{
        FpF32<16> fp1(34);
        CHECK_EQUAL(fp1.ToString(), "34.000000");
    }

    MTEST(StringTest2)	{
        FpF32<16> fp1(34.0625);
        CHECK_EQUAL(fp1.ToString(), "34.062500");
    }

	MTEST(StreamTest1)	{
		FpF32<16> fp1(34);
        std::stringstream output;
        output << fp1 << std::endl;
        CHECK_EQUAL(output.str(), "34\n");
	}

    MTEST(StreamTest2)	{
        FpF32<16> fp1(34.0625);
        std::stringstream output;
        output << fp1 << std::endl;
        CHECK_EQUAL(output.str(), "34.0625\n");
    }
}