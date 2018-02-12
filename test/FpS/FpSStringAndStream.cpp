//!
//! \file 				FpSStringAndStream.cpp
//! \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! \edited 			n/a
//! \created			2018-02-11
//! \last-modified		2018-02-11
//! \brief 				Performs unit tests on the fixed point FpS class.
//! \details
//!						See README.rst in root dir for more info.

// System includes
#include <sstream>

// 3rd party includes
#include "MUnitTest/MUnitTestApi.hpp"

// User includes
#include "MFixedPoint/FpS.hpp"

using namespace mn::MFixedPoint;

MTEST_GROUP(FpSStringAndStream) {

    MTEST(StringTest1)	{
        FpS32 fp1(34, 0);
        CHECK_EQUAL(fp1.ToString(), "34.000000");
    }

    MTEST(StringTest2)	{
        FpS32 fp1(34.0625, 16);
        CHECK_EQUAL(fp1.ToString(), "34.062500");
    }

	MTEST(StreamTest1)	{
		FpS32 fp1(34, 0);
        std::stringstream output;
        output << fp1 << std::endl;
        CHECK_EQUAL(output.str(), "34\n");
	}

    MTEST(StreamTest2)	{
        FpS32 fp1(34.0625, 16);
        std::stringstream output;
        output << fp1 << std::endl;
        CHECK_EQUAL(output.str(), "34.0625\n");
    }
}