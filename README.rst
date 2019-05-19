===========
MFixedPoint
===========

------------------------------------------------------------------------------------------
A microcontroller-friendly fixed-point library specifically designed for embedded systems.
------------------------------------------------------------------------------------------

.. image:: https://travis-ci.org/gbmhunter/MFixedPoint.png?branch=master   
	:target: https://travis-ci.org/gbmhunter/MFixedPoint


.. image:: https://codecov.io/gh/gbmhunter/MFixedPoint/branch/master/graph/badge.svg
    :target: https://codecov.io/gh/gbmhunter/MFixedPoint


Description
===========

MFixedPoint is a header-only fixed-point C++ library suitable for fast arithmetic operations on systems which don't have a FPU (e.g. embedded systems). Suitable for performing computationally intensive operations on a computing platform that does not have a floating-point unit (like most smaller embedded systems, such as Cortex-M3, CortexM0, ATmega, PSoC 5, PSoC 5 LP, PSoC 4, Arduino platforms e.t.c). Common applications include BLDC motor control and image processing. Best performance on a 32-bit or higher architecture (although 8-bit architectures should still be fine). 

The libraries are designed to be a fully-functional data types within their limits (e.g. supports operator overloads and implicit/explicit casting). Can be used with most libraries that use data type templates.

Fixed-point numbers are signed.

NOTE: This fixed point library will usually be slower when running of a CPU which has associated floating point unit (FPU), e.g. when running on your desktop/laptop. The benchmark performance tests (found in :code:`benchmark/`) suggest simple fixed-point operations such as addition/subtraction/multiplication/division are about 10x slower than their float/double counterparts when there is a FPU. However, this library is designed to be used on CPU's where there is no FPU present, which is the case for lower-end microcontrollers such as ARM Cortex M0/M3, Atmel ATMEGA, TI MSP430's e.t.c.

The "Slow" Fixed-Point Library (FpS)
------------------------------------

The "slow" fixed-point class is called :code:`FpS` (note that this class is not that slow, and is the recommend fixed-point class for almost all use cases). It allows for airthemtic between two fixed-point numbers that have different numbers of fractional bits. The underlying storage type of the fixed-point number and the overflow type are provided as the template parameters.

It is recommended that you use one of the predefined :code:`FpSxx` aliases (available with :code:`#include <MFixedPoint/FpS.h>`), which include:

.. code:: cpp

	FpS8
	FpS16
	FpS32
	FpS64 // Note: FpS64 is not protected from intermediatary overflows!

The number of fractional bits is stored in the fixed-point object (it is a template parameter in the fast library). This gives slightly slower arithmetic speed than the fast library, but allows for more functionality and should use less code space..

The extra functionality includes the ability to add two numbers with a different number of fractional bits transparently, and to ability to cast the fixed-point number into different types (e.g. :code:`(double)myFpSNum` will convert the number to a double).

When adding two fixed-point numbers which have a different number of fractional bits, the result's number of fractional bits is always that of lowest of the two operands. For example :code:`FpS32(3.4, 10) + FpS32(1.2, 14)` will result in same object being created as would the code :code:`FpS32(4.6, 10)`. 

Casting to an :code:`int` rounds to negative infinity; e.g. 5.67 becomes 5, and -12.2 becomes -13.

Create a fixed point number:

.. code:: cpp

	#include "MFixedPoint/FpS.hpp"

	// Create a 32-bit fixed-point number.
	// Assign a value of 12.34
	// Use 8 bits for the fractional part, leaving 24 for the integer part.
	FpS32 fp1(12.34, 8);
	

Addition/Subtraction/Multiplication/Division:

.. code:: cpp

	FpS32 fp1(5.0, 8);
	FpS32 fp2(1.5, 8);

	printf("add = %.2f\n", (fp1 + fp2).ToDouble()); // Prints "add = 6.50"
	printf("sub = %.2f\n", (fp1 - fp2).ToDouble()); // Prints "sub = 3.50"
	printf("mult = %.2f\n", (fp1 * fp2).ToDouble()); // Prints "mult = 7.50"
	printf("div = %.2f\n", (fp1 / fp2).ToDouble()); // Prints "div = 3.33"

Modulus:

.. code:: cpp

	FpS32 fp1(5.1, 10);
	FpS32 fp2(1.5, 8);

	printf("mod = %.2f\n", (fp1 % fp2).ToDouble()); // Prints "mod = 0.60"

Conversion/Casting:

.. code:: cpp

	FpS32 fp1(2.22, 8);	

	// Using the ToXXX() functions...
	printf("ToInt<int32_t>() = %i\n", fp1.ToInt<int32_t>()); // Prints "ToInt<int32_t>() = 2"
	printf("ToDouble() = %.2f\n", fp1.ToDouble()); // Prints "ToDouble() = 2.22"

	// Direct casting is also supported
	printf("(int32_t)fp1 = %i\n", (int32_t)fp1); // Prints "(int32_t)fp1 = 2"
	printf("(double)fp1 = %.2f\n", (double)fp1); // Prints "(double)fp1 = 2.22"

String/Stream Support:

:code:`FpS` provides a :code:`ToString()` method, as well as supporting a :code:`ostream` (e.g. :code:`std::cout`).

.. code:: cpp

	FpS32 fp1(4.87, 8);
    printf(fp1.ToString());
    std::cout << fp1 << std::endl; // Prints 4.87

The "Fast" Fixed-Point Library (FpF)
------------------------------------

The number of fractional bits is given as a template parameter (e.g. :code:`FpF32<12>(3.4)` will create the number 3.4 with 12 bits of fractional precision). It is not stored in the fixed-point object. This gives the fastest possible arithmetic speeds, at the expense of loosing some functionality and a tad more code space.

Arithmetic operations between two FpF objects that have a different template parameter (fractional precision) is not directly supported. Instead, you will have to convert one of the FpF objects to the same fraction precision first, and then do the arithmetic operation.

Overflows
---------

:code:`FpS8, FpS16, FpS32` are protected from intermediary overflows. :code:`FpS64` is not, due to the lack of a :code:`int128_t` type on most embeded platforms.

On any 32-bit architecture, :code:`FpS64` numbers will be slower than :code:`FpS64` numbers. Use only if 32-bit numbers don't offer the range/precision required.


Benchmarking
============

This library contains a benchmarking program in :code:`benchmark/` which runs operations on the fixed-point libraries and reports back on their performance. It is run automatically as part of :code:`make all`.

The benchmarking is compared to software-based float arithmetic (using the custom header SoftFloat.hpp), since most benchmarking will be run on a development computer which has an FPU which will be used if float + float was written in code. If benchmarking on a device which does not have an FPU, you should compare the fixed-point operations against the native software float arithmetic implementation instead. Software-based 32-bit float addition and multiplication are performed and compared with the equivalent fixed-point operations.

These benchmark results were computed on a x64 Ubuntu machine running inside a virtual machine. 100k samples were taken for each type of test, and the average time provided.

+----------------+--------+--------+--------+--------+----------------+----------------+
| Arithmetic     | FpF32  | FpF64  | FpS32  | FpS64  | Software Float | Hardware Float |
+================+========+========+========+========+================+================+
| Addition       | 6.7ns  | 8.2ns  | 10.6ns | 14.2ns | 30.1ns         | 3.4ns          |
+----------------+--------+--------+--------+--------+----------------+----------------+
| Subtraction    | 7.5ns  | 7.5ns  | 14.0ns | 10.4ns | n/a            | 2.6ns          |
+----------------+--------+--------+--------+--------+----------------+----------------+
| Multiplication | 10.3ns | 10.1ns | 12.2ns | 10.4ns | 32.0ns         | 2.5ns          |
+----------------+--------+--------+--------+--------+----------------+----------------+
| Division       | 19.0ns | 18.0ns | 10.8ns | 19.8ns | n/a            | 5.1ns          |
+----------------+--------+--------+--------+--------+----------------+----------------+

Platform Independent
====================

The library is designed to be platform independent. Port-specific functions are declared in separate files, Port.cpp and Port.hpp. These files include functions for printing debug information. Fill in the functions as desired.

This library has been tested on:

- ARM Cortex-M3 microcontrollers
- Linux (Ubuntu)
- A CodeAnywhere "DevBox"

Compiling
=========

Either use cmake with the provided :code:`CMakeLists.txt` in the root directory, or integrate the source files into an IDE (for an embedded platform).

The cmake method will build the fixed point library and automatically runs all unit tests and the benchmark program.


.. code:: bash

	~$ git clone https://github.com/mbedded-ninja/MFixedPoint.git
	~$ cd MFixedPoint
	~/MFixedPoint$ mkdir build
	~/MFixedPoint$ cd build
	~/MFixedPoint/build$ cmake ..
	~/MFixedPoint/build$ make
	
You can run the tests manually by calling:

.. code:: bash

	~/MFixedPoint/build$ ./test/MFixedPointTests

Examples
========

See the unit tests in :code:`test/` for more usage examples!

.. code:: cpp

	// System includes
	#include <iostream>

	// 3rd party includes
	#include "MFixedPoint/FpS.hpp"
	#include "MFixedPoint/FpF.hpp"

	using namespace mn::MFixedPoint;

	int main() {

		//================================================================================================//
		//================================= Slow Fixed-Point Numbers (FpS) ===============================//
		//================================================================================================//

		// Creating a 32-bit "slow" fixed-point number (notice the slightly different syntax to FpF)
		FpS32 fpSNum1(12.23, 12);
		std::cout << "fpSNum1 = " << (double)fpSNum1 << std::endl;

		FpS32 fpSNum2(5.12, 16);
		std::cout << "fpSNum2 = " << (double)fpSNum2 << std::endl;
		
		std::cout << "fpSNum1 + fpSNum2 = " << (double)(fpSNum1 + fpSNum2) << std::endl;
		std::cout << "fpSNum1 - fpSNum2 = " << (double)(fpSNum1 - fpSNum2) << std::endl;
		std::cout << "fpSNum1 * fpSNum2 = " << (double)(fpSNum1 * fpSNum2) << std::endl;
		std::cout << "fpSNum1 / fpSNum2 = " << (double)(fpSNum1 / fpSNum2) << std::endl;
		std::cout << "fpSNum1 % fpSNum2 = " << (double)(fpSNum1 % fpSNum2) << std::endl;

		//================================================================================================//
		//================================= Fast Fixed-Point Numbers (FpF) ===============================//
		//================================================================================================//

		// Create two 32-bit fast fixed-point numbers with 24 decimal bits and 8 fractional bits.
		// This constructor converts from doubles
		FpF32<8> fpNum1(3.2);
		FpF32<8> fpNum2(0.6);
		
		// Performing a quick fixed-point addition
		auto fpNum3 = fpNum1 + fpNum2;
		
		// Performing a quick fixed-point multiplication
		auto fpNum4 = fpNum1 * fpNum2;
		
		// Printing the result as a double, using the Fix32ToDouble() method
		// Note that if you use slow fixed-point data type instead, you can 
		// directly cast one to a double 
		std::cout << "My fast 32-bit fixed-point number = " << (double)fpNum4;
		
		// Converting between different precisions. Requires access to raw value just like
		// when doing fixed-point to double conversion.
		FpF32<20> aHigherPrecisionNum(7.5);
		// FpF32<12> aLowerPrecisionNum.rawVal = aHigherPrecisionNum.rawVal >> (20 - 12);
		
		// You can use 64-bit fixed point numbers in exactly the same way!
		FpF64<48> aFp64Num(4.58676);
		
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