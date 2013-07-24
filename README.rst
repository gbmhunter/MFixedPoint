============================
Embedded Fixed-Point Library
============================

- Author: gbmhunter <gbmhunter@gmail.com> (http://www.cladlab.com)
- Created: 2012/10/23
- Last Modified: 2013/07/24
- Version: v5.3.0.1
- Company: CladLabs
- Project: Open-source Embedded Code Libraries
- Language: C++
- Compiler: GCC	
- uC Model: n/a
- Computer Architecture: n/a
- Operating System: n/a
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

Fixed-point numbers are signed. 

The 32-bit Libraries (Fp32f, Fp32s)
-----------------------------------

Intermediary overflows are protected with int64_t casting, end-result overflows will wrap like usual. 

The 64-bit Libraries (Fp64f, Fp64s)
-----------------------------------

Intermediary overflows are **NOT** protected from overflowing, due to the inability of intermediate casting to int128_t on most embedded platforms.

On any 32-bit or lower architecture, 64-bit numbers will be slower than 32-bit numbers. Use only if 32-bit numbers don't offer
the range/precision required.

The Fast Libraries (Fp32f, Fp64f)
---------------------------------

The number of bits used for the decimal part of the number (Q) is given as a template parameter (e.g. Fp32f<12>(3.4) will create the number 3.4 with 12 bits of decimal precision). It is not stored in the fixed-point object. This gives the fastest possible arithmetic speeds, at the expense of loosing some functionality.

You have to be aware that when adding numbers with different Q, you have to perform the bit-shifting yourself. Also, if you want to convert a fast fixed-point number to a double, you cannot use a cast (e.g. (double)myFp32fNum won't work, you have to use provided functions (e.g. Fix32ToDouble(myFp32fNum);).

The Slow Libraries (Fp32s, Fp64s)
---------------------------------

The number of bits used for the decimal part of the number (Q) is given as a function argument (e.g. Fp32s(3.4, 12) will create the number 3.4 with 12 bits of decimal precision). The Q is stored in the fixed-point object. This gives slightly slower arithmetic speed than the fast libraries, but allows for more functionality.

The extra functionality includes the ability to add two numbers with a different Q transparently, and to ability to cast the fixed-point number into different types (e.g. (double)myFp32sNum will convert the number to a double).

Port Independence
=================

The library is designed to be port-independent. Port-specific functions are declared in separate files, Fp-Port.cpp and Fp-Port.hpp. These files include functions for printing debug information. Fill in the functions as desired.

Configuration
=============

Configuration settings are in 'Fp-Config.hpp'. This file allows you to turn on/off debug message printing (which itself is port-specific, and defined in Fp-Port.hpp/cpp).

Compiling
=========

Either use provided Makefile in root directory, or integrate into an IDE. The Makefile builds the fixed point libraries and automatically runs all unit tests.

To run the makefile, open a terminal in the root directory of this library, and type:

::

	make all
	
To clean all files as a result of compilation, run:

::

	make clean

Usage
=====

See the unit tests in ./test/ for more usage examples!

::

#include "/src/include/FixedPoint-Fp32f.hpp"
#include "/src/include/FixedPoint-Fp64f.hpp"

int main()
{
	// Create two 32-bit fixed-point numbers with 24 decimal bits and 8 fractional bits.
	// This constructor converts from doubles
	Fp32f<8> aFpNum1 = Fp32f<8>(3.2);
	Fp32f<8> aFpNum2 = Fp32f<8>(0.6);
	
	// Performing a quick fixed-point addition
	Fp32f<8> aFpNum3 = aFpNum1 + aFpNum2;
	
	// Performing a quick fixed-point multiplication
	Fp32f<8> aFpNm4 = aFpNum1 * aFpNum2;
	
	// Converting fixed-point back to double. Requires you
	// to pass the raw value (which can be accessed with
	// .rawVal)
	double result = Fix32ToFloat<8>(aFpNum4.rawVal);
	
	// Converting between different precisions. Requires access to raw value just like
	// when doing fixed-point to double conversion.
	Fp32f<20> aHigherPrecisionNum = Fp32f<20>(7.5);
	Fp32f<12> aLowerPrecisionNum.rawVal = aHigherPrecisionNum.rawVal >> (20 - 12);
	
	// You can use 64-bit fixed point numbers in exactly the same way!
	Fp64f<48> aFp64Num = Fp64f<48>(4.58676);
	
	return 0;
}
	
Changelog
=========

======== ========== ===================================================================================================
Version  Date       Comment
======== ========== ===================================================================================================
v5.3.0.1 2013/07/24 Updated README to describe the differences between the four libraries better.
v5.3.0.0 2013/07/24 Added fixed-point, 64-bit, slow library (Fp64s). Added relevant unit tests. Added relevant notes to README.
v5.2.0.0 2013/07/24 Added arithmetic overloads (both simple and compound) and binary overloads for the Fp32s library. Change Suite name in FpTest-Fp32fArithmetic.cpp. Added '%=' overload to Fp32f library. Added unit tests for relevant additions.
v5.1.1.0 2013/07/23 Added cast support to int32_t and float. Changed Suite name Fp32fCastTests to Fp32sCastTests. Renamed Fp32Q class to Fp32s (was meant to do this in v5.1.0.0), and updated tests/benchmarks accordingly. Added to all unit test filenames either 'f' or 's' to reflect new class names.
v5.1.0.1 2013/07/23 Updated 'Usage' section of README to reflect new class names. Changed 'make test' to 'make all' in 'Compiling' section.
v5.1.0.0 2013/07/23 Renamed classes Fp32 to Fp32f, Fp64 to Fp64f, and Fp32Q to Fp32s. The f stands designated the faster library, the s for the slower but more powerful library. Updated README accordingly. Updated all tests and benchmarks accordingly.
v5.0.1.0 2013/07/22 Added 'Relevant Header' sections to all libraries in README. Added comments to Makefile 'clean' and added 'clean-fp' make command.
v5.0.0.0 2013/07/22 Added new fixed point class which also stores Q (Fp32Q). Slower, but more powerful than the template-based approach used for Fp32 and Fp64 (being able to do casts to other data types is the major improvement). Currently only limited operator support for this library (double cast is supported). Added unit test for double cast on Fp32Q library.
v4.0.1.0 2013/07/19 Benchmarking now reports time per single test and percentage difference from expected.
v4.0.0.0 2013/07/19 Added benchmarking program to test the performance (both size and speed) of the fixed point library.
v3.4.8.0 2013/07/17 Added unit tests for the size of both the Fp32 and Fp64 objects.
v3.4.7.0 2013/07/17 Added speed tests for both 32-bit and 64-bit fixed-point basic mathematics.
v3.4.6.0 2013/07/17 Got rid of 'Comparison Between Signed And Unsigned Integer Expressions' compiler warning.
v3.4.5.0 2013/07/17 Added bit-width to FixToFloat family of functions. Also changed '2' to 'to'.
v3.4.4.0 2013/07/17 Removed pragma code from FixedPoint-Port.hpp that printed a compiler message about Linux.
v3.4.3.0 2013/07/17 Replaced all int's with fixed-width int32_t so width is guaranteed.
v3.4.2.1 2013/07/17 Added main(), includes and 64-bit fixed point example to README usage section.
v3.4.2.0 2013/07/16 Added basic speed unit tests for multiplication and division.
v3.4.1.0 2013/07/16 Replaced intValue with rawVal for Fp32 class.
v3.4.0.0 2013/07/12 Added binary overloads for Fp64 class. Added binary unit tests for Fp64.
v3.3.2.0 2013/07/12 Added test suites to unit tests, split unit tests up into their own suite-grouped files.
v3.3.1.0 2013/07/12 Fixed incorrect includes after file-name changes.
v3.3.0.0 2013/07/12 Renamed files to follow Namespace-Class convention.
v3.2.2.0 2013/07/11 Made Makefile automatically find .cpp files in both src and test and compile them.
v3.2.1.1 2013/06/18 Added comments to 'fpConfig_PRINT_DEBUG_GENERAL'. Added 'Configuration' section to README. Added more info to 'Compiling' section in README.
v3.2.1.0 2013/06/17 Makefile now compiles UnitTest++ as a dependency, and removes all files from './obj/'.
v3.2.0.0 2013/06/17 Modified Makefile so it automatically compiles all .cpp files. Puts compiled files into new 'obj' directory.
v3.1.1.0 2013/06/17 Added 'Fp-Port.cpp/hpp' and moved port-specific functions into these files. Add 'Port Independence' section to README. Added 'Fp-Config.hpp'.
v3.1.0.2 2013/06/08 README changelog is now in reverse chronological order and in table format.
v3.1.0.1 2013/06/02 Added more info to README about using this library as a data type.
v3.1.0.0 2013/05/30 Added more unit tests for basic operator overloads (now 21 in total). Improved Makefile.
v3.0.1.0 2013/05/30 Added Makefile to root directory. Fixed syntax error in basic unit test. Added 'Compiling' section to README.
v3.0.0.0 2013/05/30 Added unit tests in './test' to verify libraries are working correctly. Uses UnitTest++ library.
v2.1.0.0 2013/05/30 Renamed Fp.cpp to Fp32.cpp (and .h in include), since there is now a 64-bit version (Fp64.hpp). 32-bit FP Class renamed accordingly.
v2.0.1.2 2013/05/10 Improved README.rst with usage section, code examples, and better description.
v2.0.1.1 2013/05/10 Added README.rst.
v2.0.1.0 2013/05/10 Fixed bug in constructor to Fp64 from int32_t. Added cast to int64_t before shifting to prevent truncation.
v2.0.0.0 2013/05/09 Added support for 64-bit fixed point numbers (Fp64.h).
v1.3.2.0 2013/05/09 Renamed Fp.h to Fp.hpp. Removed doubling up of version in both files, now just defined in Fp.hpp. Added dates	to version numbers. Added C++ guard at the start of both Fp.cpp and Fp.hpp.
v1.3.1.2 2013/05/08 Indented all namespace objects (formatting issue).
v1.3.1.1 2013/05/08 Moved Fp.h into ./src/include/. Changed to 4-digit versioning system. Changed incorrect date.
v1.3.1 	 2012/11/05 Added library description.
v1.3.0 	 2012/11/05 Added operator overload for '%'. Tested and works fine.
v1.2.0 	 2012/11/04 Made fp a class with public members, rather than structure.
v1.1.1 	 2012/11/04 Fixed filename errors. Attributed Markus Trenkwalder as the original author.
v1.1.0 	 2012/10/23 Merged fixed_func.h into this file. Added	comments. Changed fixed_point to fp.
======== ========== ===================================================================================================