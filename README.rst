============================
Embedded Fixed-Point Library
============================

- Author: gbmhunter <gbmhunter@gmail.com> (http://www.cladlab.com)
- Created: 2012/10/23
- Last Modified: 2013/05/30
- Version: v2.1.0.0
- Company: CladLabs
- Project: Embedded Code Library
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

Fixed-point numbers are signed. Class supports dynamic precision, determined with variable p which denotes fractional precision. 

32-bit Fixed-Point Numbers
--------------------------

The integer precision is (32 bits - p). Intermediary overflows are protected with int64 casting, end-result overflows will wrap like usual. 
Support operator oveloading for most common fixed-point arithmetic.

64-bit Fixed-Point Numbers
--------------------------

Intermediary overflows are **NOT** protected from overflowing, due to the inability of converting to int128_t on most embedded platforms.
On any 32-bit or lower architecture, 64-bit numbers will be slower than 32-bit numbers. Use only if 32-bit numbers don't offer
the range/precision required.

Usage
=====

::

	// Create two 32-bit fixed-point numbers with 24 decimal bits and 8 fractional bits.
	// This constructor converts from doubles.
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

- v1.1.0 		-> (12/10/23) Merged fixed_func.h into this file. Added	comments. Changed fixed_point to fp.
- v1.1.1 		-> (12/11/04) Fixed filename errors. Attributed Markus Trenkwalder as the original author.
- v1.2.0 		-> (12/11/04) Made fp a class with public members, rather than structure.
- v1.3.0 		-> (12/11/05) Added operator overload for '%'. Tested and works fine.
- v1.3.1 		-> (12/11/05) Added library description.
- v1.3.1.1 	-> (13/05/08) Moved Fp.h into ./src/include/. Changed to 4-digit versioning system. Changed incorrect date.
- v1.3.1.2	-> (13/05/08) Indented all namespace objects (formatting issue).
- v1.3.2.0	-> (13/05/09) Renamed Fp.h to Fp.hpp. Removed doubling up of version in both files, now just defined in Fp.hpp. Added dates	to version numbers. Added C++ guard at the start of both Fp.cpp and Fp.hpp.
- v2.0.0.0	-> (13/05/09) Added support for 64-bit fixed point numbers (Fp64.h).
- v2.0.1.0	-> (13/05/10) Fixed bug in constructor to Fp64 from int32_t. Added cast to int64_t before shifting to prevent truncation.
- v2.0.1.1	-> (13/05/10) Added README.rst
- v2.0.1.2 	-> (13/05/10) Improved README.rst with usage section, code examples, and better description.
- v2.1.0.0  -> (13/05/30) Renamed Fp.cpp to Fp32.cpp (and .h in include), since there is now a 64-bit version (Fp64.hpp). 32-bit FP Class renamed accordingly.
