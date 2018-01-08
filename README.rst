===========
MFixedPoint
===========

------------------------------------------------------------------------------------------
A microcontroller-friendly fixed-point library specifically designed for embedded systems.
------------------------------------------------------------------------------------------

.. image:: https://travis-ci.org/mbedded-ninja/MFixedPoint.png?branch=master   
	:target: https://travis-ci.org/mbedded-ninja/MFixedPoint


.. image:: https://codecov.io/gh/mbedded-ninja/MFixedPoint/branch/master/graph/badge.svg
    :target: https://codecov.io/gh/mbedded-ninja/MFixedPoint


Description
===========

32-bit and 64-bit fixed-point libraries for fast arithmetic operations. Suitable for performing computationally intensive operations
on a computing platform that does not have a floating-point unit (like most smaller embedded systems, such as Cortex-M3, CortexM0,
ATmega, PSoC 5, PSoC 5 LP, PSoC 4, Arduino platforms e.t.c). Common applications include BLDC motor control and image processing.
Best performance on a 32-bit or higher architecture (although 8-bit architectures should still be fine). 

The libraries are designed to be a fully-functional data types within their limits (e.g. supports operator overloads and implicit/explicit casting). Can be used with
most libraries that use data type templates.

Fixed-point numbers are signed. Q is the number of bits used for the decimal part of the number (the rest are used for the integer part). Q can vary from 0 up to the bit-width of the fixed-point number.

The "Slow" Fixed-Point Class
----------------------------

The "slow" fixed-point class is called FpS (note that this class is not that slow, and is the recommend fixed-point class for almost all use cases). It allows for airthemtic between two fixed-point numbers that have different numbers of fractional bits. The underlying storage type of the fixed-point number is provided as the only template parameter.

Create a fixed point number:

::

	// Create a fixed point number of 32-bits. 8 bits are used for the fractional part, leaving 24 for the integer part.
	FpS<int32_t> fp1(12.34, 8);
	

Addition/Subtraction/Multiplication/Division:

::

	FpS<int32_t> fp1(5.0, 8);
	FpS<int32_t> fp2(1.5, 8);

	printf("add = %.2f\n", (fp1 + fp2).ToDouble()); // Prints "add = 6.50"
	printf("sub = %.2f\n", (fp1 - fp2).ToDouble()); // Prints "sub = 3.50"
	printf("mult = %.2f\n", (fp1 * fp2).ToDouble()); // Prints "mult = 7.50"
	printf("div = %.2f\n", (fp1 / fp2).ToDouble()); // Prints "div = 3.33"

Modulus:

::
	FpS<int32_t> fp1(5.1, 10);
	FpS<int32_t> fp2(1.5, 8);

	printf("mod = %.2f\n", (fp1 % fp2).ToDouble()); // Prints "mod = 0.60"

Conversion/Casting:

::
	FpS<int32_t> fp1(2.22, 8);	

	// Using the ToXXX() functions...
	printf("ToInt<int32_t>() = %i\n", fp1.ToInt<int32_t>()); // Prints "ToInt<int32_t>() = 2"
	printf("ToDouble() = %.2f\n", fp1.ToDouble()); // Prints "ToDouble() = 2.22"

	// Direct casting is also supported
	printf("(int32_t)fp1 = %i\n", (int32_t)fp1); // Prints "(int32_t)fp1 = 2"
	printf("(double)fp1 = %.2f\n", (double)fp1); // Prints "(double)fp1 = 2.22"
	

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

Platform Independent
====================

The library is designed to be platform independent. Port-specific functions are declared in separate files, Port.cpp and Port.hpp. These files include functions for printing debug information. Fill in the functions as desired.

This library has been tested on:
- An ARM Cortex-M3 microcontroller
- Linux
- A CodeAnywhere "DevBox"

Configuration
=============

Configuration settings are in :code:`include/Config.hpp`. This file allows you to turn on/off debug message printing (which itself is port-specific, and defined in :code:`include/Port.hpp/cpp`).

Compiling
=========

Either use cmake with the provided :code:`CMakeLists.txt` in the root directory, or integrate the source files into an IDE (for an embedded platform).

The cmake method will build the fixed point library and automatically runs all unit tests and the benchmark program.


::

	~$ git clone https://github.com/mbedded-ninja/MFixedPoint.git
	~$ cd MFixedPoint
	~/MFixedPoint$ mkdir build
	~/MFixedPoint$ cd build
	~/MFixedPoint/build$ cmake ..
	~/MFixedPoint/build$ make
	
You can then the tests by calling:

::

	~/MFixedPoint/build$ ./test/MFixedPointTests

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

Visual Studio Code
==================

Project files for Visual Studio Code are included in this repository. Include paths have been added to :code:`c_cpp_properties.json` to improve auto-complete. This includes the directory :code:`${workspaceRoot}/build/external/include` (which contains the 3rd party libraries MFixedPoint depends on that are automatically downloaded by CMake) but is only valid once CMake has been run at least once from with a build directory called :code:`build`.

Code Dependencies
=================

The following table lists all of MFixedPoint's dependencies.

====================== ==================== ======================================================================
Dependency             Delivery             Usage
====================== ==================== ======================================================================
<cstdint>              C standard library   For platform agnostic fixed-width integers.
MUnitTest              External module      Framework for unit tests.
====================== ==================== ======================================================================