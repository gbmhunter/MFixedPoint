===========
MFixedPoint
===========

------------------------------------------------------------------------------------------
A microcontroller-friendly fixed-point library specifically designed for embedded systems.
------------------------------------------------------------------------------------------

.. image:: https://travis-ci.org/mbedded-ninja/MFixedPoint.png?branch=master   
	:target: https://travis-ci.org/mbedded-ninja/MFixedPoint

- Author: gbmhunter <gbmhunter@gmail.com> (http://www.mbedded.ninja)
- Created: 2012-10-23
- Last Modified: 2015-01-26
- Version: v5.10.3.0
- Company: mbedded.ninja
- Project: MToolkit
- Language: C++
- Compiler: GCC	
- uC Model: Any
- Computer Architecture: Any
- Operating System: Any
- Documentation Format: Doxygen
- License: GPLv3

Description
===========

32-bit and 64-bit fixed-point libraries for fast arithmetic operations. Suitable for performing computationally intensive operations
on a computing platform that does not have a floating-point unit (like most smaller embedded systems, such as Cortex-M3, CortexM0,
ATmega, PSoC 5, PSoC 5 LP, PSoC 4, Arduino platforms e.t.c). Common applications include BLDC motor control and image processing.
Best performance on a 32-bit or higher architecture (although 8-bit architectures should still be fine). 

The libraries are designed to be a fully-functional data types within their limits (e.g. supports operator overloads and implicit/explicit casting). Can be used with
most libraries that use data type templates.

Fixed-point numbers are signed. Q is the number of bits used for the decimal part of the number (the rest are used for the integer part). Q can vary from 0 up to the bit-width of the fixed-point number.

The 32-bit Libraries (Fp32f, Fp32s)
-----------------------------------

Intermediary overflows are protected with int64_t casting, end-result overflows will wrap like usual. 

The 64-bit Libraries (Fp64f, Fp64s)
-----------------------------------

Intermediary overflows are **NOT** protected from overflowing, due to the inability of intermediate casting to :code:`int128_t` on most embedded platforms.

On any 32-bit or lower architecture, 64-bit numbers will be slower than 32-bit numbers. Use only if 32-bit numbers don't offer
the range/precision required.

The Fast Libraries (Fp32f, Fp64f)
---------------------------------

The number of bits used for the decimal part of the number (Q) is given as a template parameter (e.g. :code:`Fp32f<12>(3.4)` will create the number 3.4 with 12 bits of decimal precision). It is not stored in the fixed-point object. This gives the fastest possible arithmetic speeds, at the expense of loosing some functionality and a tad more code space.

You have to be aware that when adding numbers with different Q, you have to perform the bit-shifting yourself. Also, if you want to convert a fast fixed-point number to a double, you cannot use a cast (e.g. :code:`(double)myFp32fNum` won't work, you have to use provided functions (e.g. :code:`Fix32ToDouble(myFp32fNum);`).

The Slow Libraries (Fp32s, Fp64s)
---------------------------------

The number of bits used for the decimal part of the number (Q) is given as a function argument (e.g. :code:`Fp32s(3.4, 12)` will create the number 3.4 with 12 bits of decimal precision). The Q is stored in the fixed-point object (it is a template parameter in the fast libraries). This gives slightly slower arithmetic speed than the fast libraries, but allows for more functionality and should use less code space..

The extra functionality includes the ability to add two numbers with a different Q transparently, and to ability to cast the fixed-point number into different types (e.g. :code:`(double)myFp32sNum` will convert the number to a double).

When adding two fixed-point numbers which have a different Q, the result's Q is always that of lowest Q of the two operands. For example :code:`Fp32s(3.4, 10) + Fp32s(1.2, 14)` will result in same object being created as would the code :code:`Fp32s(4.6, 10)`. 

Casting to an :code:`int` rounds down to the nearest integer; e.g. 5.67 becomes 5, and -12.2 becomes -13.

Benchmarking
============

This library contains a benchmarking program in :code:`benchmark/` which runs operations on the fixed-point libraries and reports back on their performance. It is run automatically as part of :code:`make all`.

Do not pay much attention to the benchmarking results when run on a pre-emptive OS such as Linux.

Port Independence
=================

The library is designed to be port-independent. Port-specific functions are declared in separate files, Port.cpp and Port.hpp. These files include functions for printing debug information. Fill in the functions as desired.

Configuration
=============

Configuration settings are in :code:`include/Config.hpp`. This file allows you to turn on/off debug message printing (which itself is port-specific, and defined in :code:`include/Port.hpp/cpp`).

Compiling
=========

Either use the provided Makefile in root directory, or integrate into an IDE. The Makefile builds the fixed point libraries and automatically runs all unit tests and benchmark programs.

To run the makefile, open a terminal in the root directory of this library, and type:

::

	make all
	
To clean all files as a result of compilation, run:

::

	make clean

Usage
=====

See the unit tests in :code:`test/` for more usage examples!

::

	// Include the API header which provides access to all of the fixed-point
	// data types
	#include "MFixedPoint/api/MFixedPointApi.hpp"

	int main()
	{
		// Create two 32-bit fast fixed-point numbers with 24 decimal bits and 8 fractional bits.
		// This constructor converts from doubles
		Fp32f<8> aFpNum1 = Fp32f<8>(3.2);
		Fp32f<8> aFpNum2 = Fp32f<8>(0.6);
		
		// Performing a quick fixed-point addition
		Fp32f<8> aFpNum3 = aFpNum1 + aFpNum2;
		
		// Performing a quick fixed-point multiplication
		Fp32f<8> aFpNm4 = aFpNum1 * aFpNum2;
		
		// Printing the result as a double, using the Fix32ToDouble() method
		// Note that if you use slow fixed-point data type instead, you can 
		// directly cast one to a double 
		std::cout << "My fast 32-bit fixed-point number = " << Fix32ToDouble(aFpNum4);
		
		// Converting between different precisions. Requires access to raw value just like
		// when doing fixed-point to double conversion.
		Fp32f<20> aHigherPrecisionNum = Fp32f<20>(7.5);
		Fp32f<12> aLowerPrecisionNum.rawVal = aHigherPrecisionNum.rawVal >> (20 - 12);
		
		// You can use 64-bit fixed point numbers in exactly the same way!
		Fp64f<48> aFp64Num = Fp64f<48>(4.58676);
		
		// Creating a 32-bit slow fixed-point number (notice the slightly different syntax)
		Fp32s mySlowFp32Num = Fp32s(12.23, 12);
		
		// You can cast slow 32-bit fixed-point numbers back to doubles
		// (you can't do this with the fast fixed-point data types)
		std::cout << "My slow 32-bit fixed-point number = " << (double)mySlowFp32Num; 
		
		return 0;
	}

Code Dependencies
=================

The following table lists all of MFixedPoint's dependencies.

====================== ==================== ======================================================================
Dependency             Delivery             Usage
====================== ==================== ======================================================================
<cstdint>              C standard library   For platform agnostic fixed-width integers.
MUnitTest              External module      Framework for unit tests.
====================== ==================== ======================================================================
	
Changelog
=========

========= ========== ==============================================================================================
Version   Date       Comment
========= ========== ==============================================================================================
v5.10.3.0 2015-01-26 Renamed 'FloatToFixXX<p>()' functions to 'FloatToRawFixXX<p>()' to avoid people trying to use them to directly convert to a fixed point number using the syntax 'myFpNum = FloatToFixx<8>(4.6);', closes #80. Added unit test for the 'FloatToRawFix32<p>()' function. Added some relevant information to the README.
v5.10.2.2 2015-01-15 Fixed error in usage code in README. The include path for MFixedPointApi.hpp is incorrect, closes #77. Fixed error in the usage example in README where it incorrectly casts a fast fixed-point value to a double, closes #78. Turned more parts of the README into 'code' formatted sections rather than just plain text.
v5.10.2.1 2015-01-14 Added a table of MFixedPoint's dependencies to the README, closes #76.
v5.10.2.0 2014-09-24 Fixed all unit tests so they fit the format 'CHECK_EQUAL(actual, expected)'. Many have actual and expected around the wrong way, closes #75.
v5.10.1.0 2014-09-16 Updated '.travis.yml' file in attempt to fix TravisCI build error.
v5.10.0.0 2014-09-15 Updated title in README to 'MFixedPoint'. Added Eclipse project files. Update URLs in code comments from 'www.cladlab.com' to 'www.mbedded.ninja', closes #72. Moved headers from 'src/include/' to 'include/', to follow the convention of other MToolkit modules, closes #70. Added API file to the new foler 'api/', closes #71. Dropped 'FixedPoint-' prefix from code files, to follow the naming convention of the other MToolkit modules, closes #69. Replaced UnitTestCpp with the MUnitTest module, closes #73, closes #23.
v5.9.0.2  2014-09-02 Reworded title in README.
v5.9.0.1  2014-09-02 Fixed captilisation error in README.
v5.9.0.0  2014-09-02 Changed name from 'FixedPoint-Cpp' to 'FixedPointCpp'. Updated links in README to 'www.mbedded.ninja'. Updated dates in README to use ISO standard.
v5.8.1.0  2013-11-27 Changed some operator overloads in FixedPoint-Fp32f.hpp to pass in variable by reference instead of by value, as recommended by Cppcheck for better performance.
v5.8.0.0  2013-11-27 Added Cppcheck project file to root folder of repo.
v5.7.3.1  2013-08-21 Removed references in README to FixXXToFloat(), redundant now because of float/double overloads. Indented code examples so they will display properly.
v5.7.3.0  2013-08-21 Third attempt at fixing image, moved link to a new line.
v5.7.2.0  2013-08-21 Second attempt at fixing image.
v5.7.1.0  2013-08-21 Attempting to fix Travis CI build image URL.
v5.7.0.0  2013-08-21 Added Travis CI build status image to README. Updated .travis.yml to hopefully fix errors.
v5.6.0.0  2013-08-21 Added basic .travis.yml to use with Travis CI.
v5.5.3.0  2013-07-25 Updated FixedPoint-Port.cpp to look for PSOC definition (which you add via compiler option -D).
v5.5.2.0  2013-07-25 Change 'p' to 'q' in Fp32f.hpp, because precision was not the correct word.
v5.5.1.0  2013-07-25 Added more from Fpxxf conversion overloads to float/double/int and removed the FixXXToFloat() family of functions. Modified unit tests accordingly.
v5.5.0.0  2013-07-25 Added type conversion overloads for Fp32f to float. Added appropriate unit tests. Added size_t cast to integers in FpTest-FpxxfSize.cpp.
v5.4.5.0  2013-07-24 Fix64ToDouble(), Fix32ToDouble() were incorrectly returning floats. Added unit tests to detect this in future.
v5.4.4.0  2013-07-24 Added Fix32ToDouble(), Fix64ToDouble(), Fix64ToDouble() functions for fast Fp libraries. Added related unit tests.
v5.4.3.0  2013-07-24 Fixed incorrect cast to 32-bit in 64-bit division. Changed all instances of template parameter p to uint8_t. Added a bit of info about Q to the README.
v5.4.2.0  2013-07-24 Tidied up Port.hpp/cpp macros.
v5.4.1.0  2013-07-24 Merged type conversion and cast unit tests. Got rid of 'Deprecated Conversion To String Constant' compiler warnings. Added arithmetic unit tests for variables with different Q (applicable to the slow libraries only).
v5.4.0.0  2013-07-24 Added compound arithmetic unit tests for Fp64f library. Added conversions from float/double to Fp64f. Fixed negative int unit tests from failing by changing expected value (it rounds down to the nearest int). Added more tests to benchmark program. Added notes to README about benchmarking program.
v5.3.0.1  2013-07-24 Updated README to describe the differences between the four libraries better.
v5.3.0.0  2013-07-24 Added fixed-point, 64-bit, slow library (Fp64s). Added relevant unit tests. Added relevant notes to README.
v5.2.0.0  2013-07-24 Added arithmetic overloads (both simple and compound) and binary overloads for the Fp32s library. Change Suite name in FpTest-Fp32fArithmetic.cpp. Added '%=' overload to Fp32f library. Added unit tests for relevant additions.
v5.1.1.0  2013-07-23 Added cast support to int32_t and float. Changed Suite name Fp32fCastTests to Fp32sCastTests. Renamed Fp32Q class to Fp32s (was meant to do this in v5.1.0.0), and updated tests/benchmarks accordingly. Added to all unit test filenames either 'f' or 's' to reflect new class names.
v5.1.0.1  2013-07-23 Updated 'Usage' section of README to reflect new class names. Changed 'make test' to 'make all' in 'Compiling' section.
v5.1.0.0  2013-07-23 Renamed classes Fp32 to Fp32f, Fp64 to Fp64f, and Fp32Q to Fp32s. The f stands designated the faster library, the s for the slower but more powerful library. Updated README accordingly. Updated all tests and benchmarks accordingly.
v5.0.1.0  2013-07-22 Added 'Relevant Header' sections to all libraries in README. Added comments to Makefile 'clean' and added 'clean-fp' make command.
v5.0.0.0  2013-07-22 Added new fixed point class which also stores Q (Fp32Q). Slower, but more powerful than the template-based approach used for Fp32 and Fp64 (being able to do casts to other data types is the major improvement). Currently only limited operator support for this library (double cast is supported). Added unit test for double cast on Fp32Q library.
v4.0.1.0  2013-07-19 Benchmarking now reports time per single test and percentage difference from expected.
v4.0.0.0  2013-07-19 Added benchmarking program to test the performance (both size and speed) of the fixed point library.
v3.4.8.0  2013-07-17 Added unit tests for the size of both the Fp32 and Fp64 objects.
v3.4.7.0  2013-07-17 Added speed tests for both 32-bit and 64-bit fixed-point basic mathematics.
v3.4.6.0  2013-07-17 Got rid of 'Comparison Between Signed And Unsigned Integer Expressions' compiler warning.
v3.4.5.0  2013-07-17 Added bit-width to FixToFloat family of functions. Also changed '2' to 'to'.
v3.4.4.0  2013-07-17 Removed pragma code from FixedPoint-Port.hpp that printed a compiler message about Linux.
v3.4.3.0  2013-07-17 Replaced all int's with fixed-width int32_t so width is guaranteed.
v3.4.2.1  2013-07-17 Added main(), includes and 64-bit fixed point example to README usage section.
v3.4.2.0  2013-07-16 Added basic speed unit tests for multiplication and division.
v3.4.1.0  2013-07-16 Replaced intValue with rawVal for Fp32 class.
v3.4.0.0  2013-07-12 Added binary overloads for Fp64 class. Added binary unit tests for Fp64.
v3.3.2.0  2013-07-12 Added test suites to unit tests, split unit tests up into their own suite-grouped files.
v3.3.1.0  2013-07-12 Fixed incorrect includes after file-name changes.
v3.3.0.0  2013-07-12 Renamed files to follow Namespace-Class convention.
v3.2.2.0  2013-07-11 Made Makefile automatically find .cpp files in both src and test and compile them.
v3.2.1.1  2013-06-18 Added comments to 'fpConfig_PRINT_DEBUG_GENERAL'. Added 'Configuration' section to README. Added more info to 'Compiling' section in README.
v3.2.1.0  2013-06-17 Makefile now compiles UnitTest++ as a dependency, and removes all files from './obj/'.
v3.2.0.0  2013-06-17 Modified Makefile so it automatically compiles all .cpp files. Puts compiled files into new 'obj' directory.
v3.1.1.0  2013-06-17 Added 'Fp-Port.cpp/hpp' and moved port-specific functions into these files. Add 'Port Independence' section to README. Added 'Fp-Config.hpp'.
v3.1.0.2  2013-06-08 README changelog is now in reverse chronological order and in table format.
v3.1.0.1  2013-06-02 Added more info to README about using this library as a data type.
v3.1.0.0  2013-05-30 Added more unit tests for basic operator overloads (now 21 in total). Improved Makefile.
v3.0.1.0  2013-05-30 Added Makefile to root directory. Fixed syntax error in basic unit test. Added 'Compiling' section to README.
v3.0.0.0  2013-05-30 Added unit tests in './test' to verify libraries are working correctly. Uses UnitTest++ library.
v2.1.0.0  2013-05-30 Renamed Fp.cpp to Fp32.cpp (and .h in include), since there is now a 64-bit version (Fp64.hpp). 32-bit FP Class renamed accordingly.
v2.0.1.2  2013-05-10 Improved README.rst with usage section, code examples, and better description.
v2.0.1.1  2013-05-10 Added README.rst.
v2.0.1.0  2013-05-10 Fixed bug in constructor to Fp64 from int32_t. Added cast to int64_t before shifting to prevent truncation.
v2.0.0.0  2013-05-09 Added support for 64-bit fixed point numbers (Fp64.h).
v1.3.2.0  2013-05-09 Renamed Fp.h to Fp.hpp. Removed doubling up of version in both files, now just defined in Fp.hpp. Added dates	to version numbers. Added C++ guard at the start of both Fp.cpp and Fp.hpp.
v1.3.1.2  2013-05-08 Indented all namespace objects (formatting issue).
v1.3.1.1  2013-05-08 Moved Fp.h into ./src/include/. Changed to 4-digit versioning system. Changed incorrect date.
v1.3.1.0  2012-11-05 Added library description.
v1.3.0.0  2012-11-05 Added operator overload for '%'. Tested and works fine.
v1.2.0.0  2012-11-04 Made fp a class with public members, rather than structure.
v1.1.1.0  2012-11-04 Fixed filename errors. Attributed Markus Trenkwalder as the original author.
v1.1.0.0  2012-10-23 Merged fixed_func.h into this file. Added	comments. Changed fixed_point to fp.
========= ========== ==============================================================================================