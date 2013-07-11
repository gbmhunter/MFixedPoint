============================
Embedded Fixed-Point Library
============================

- Author: gbmhunter <gbmhunter@gmail.com> (http://www.cladlab.com)
- Created: 2012/10/23
- Last Modified: 2013/07/11
- Version: v3.2.2.0
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

32-bit and 64-bit fixed-point library for fast arithmetic operations. Suitable for performing computationally intensive operations
on a computing platform that does not have a floating-point unit (like most smaller embedded systems, such as Cortex-M3, CortexM0,
ATmega, PSoC 5, PSoC 5 LP, PSoC 4, Arduino platforms e.t.c). Common applications include BLDC motor control and image processing.
Best performance on a 32-bit or higher architecture (although 8-bit architectures should still be fine). 

Designed to be a fully-functional data type (e.g. supports operator overloads and implicit/explicit casting). Can be used with
most other CladLabs C++ libraries that use data type templates (e.g. the PID library: Cpp-Pid, or the
linear interpolation library: Cpp-LinInterp).

Fixed-point numbers are signed. Class supports dynamic precision, determined with variable p which denotes fractional precision. 

32-bit Fixed-Point Numbers
--------------------------

The integer precision is (32 bits - p). Intermediary overflows are protected with int64 casting, end-result overflows will wrap like usual. 
Support operator overloading for most common fixed-point arithmetic.

64-bit Fixed-Point Numbers
--------------------------

Intermediary overflows are **NOT** protected from overflowing, due to the inability of converting to int128_t on most embedded platforms.
On any 32-bit or lower architecture, 64-bit numbers will be slower than 32-bit numbers. Use only if 32-bit numbers don't offer
the range/precision required.

Port Independence
=================

The library is designed to be port-independent. Port-specific functions are declared in separate files, Fp-Port.cpp and Fp-Port.hpp. These files include functions for printing debug information. Fill in the functions as desired.

Configuration
=============

Configuration settings are in 'Fp-Config.hpp'. This file allows you to turn on/off debug message printing (which itself is port-specific, and defined in Fp-Port.hpp/cpp).

Compiling
=========

Either use provided Makefile in root directory, or integrate into an IDE. The Makefile builds the fixed point library and automatically runs unit tests.

To run the makefile, open a terminal in the root directory of this library, and type:

::

	make test
	
To clean all compiled object files, run:

::

	make clean

Usage
=====

::

	// Create two 32-bit fixed-point numbers with 24 decimal bits and 8 fractional bits.
	// This constructor converts from doubles
	Fp32<8> aFpNum1 = Fp32<8>(3.2);
	Fp32<8> aFpNum2 = Fp32<8>(0.6);
	
	// Performing a quick fixed-point addition
	Fp32<8> aFpNum3 = aFpNum1 + aFpNum2;
	
	// Performing a quick fixed-point multiplication
	Fp32<8> aFpNm4 = aFpNum1 * aFpNum2;
	
	// Converting fixed-point back to double. Requires you
	// to pass the raw value (which can be accessed with
	// .intValue)
	double result = Fix2Float<8>(aFpNum4.intValue);
	
	// Converting between different precisions. Requires access to raw value just like
	// when doing fixed-point to double conversion.
	Fp32<20> aHigherPrecisionNum = Fp32<20>(7.5);
	Fp32<12> aLowerPrecisionNum.intValue = aHigherPrecisionNum.intValue >> (20 - 12)
	
Changelog
=========

======== ========== ===================================================================================================
Version  Date       Comment
======== ========== ===================================================================================================
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