============================
Embedded Fixed-Point Library
============================

- Author: gbmhunter (www.cladlab.com)
- Created: 2012/10/23
- Last Modified: 2013/05/10
- Version: v2.0.1.1
- Company: CladLabs
- Project: Free Embedded Code librarys.
- Language: C++
- Compiler: GCC	
- uC Model: n/a
- Computer Architecture: n/a
- Operating System: n/a
- Documentation Format: Doxygen
- License: GPLv3

Description
===========

Fixed-point library for fast arithmetic operations. Designed for use on a 32-bit architecture. 

Fixed-point numbers aresigned. Class supports dynamic precision, determined with variable p which denotes fractional precision. 

The integer precision is (32 bits - p). Overflows will wrap. Support operator oveloading for most common fixed-point
arithemetic.

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
