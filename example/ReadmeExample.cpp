///
/// \file 				ReadmeExample.cpp
/// \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
/// \edited 			n/a
/// \created			2018-01-10
/// \last-modified		2017-01-10
/// \brief 				Contains the example code that is shown in the README.
/// \details
///						See README.rst in root dir for more info.

// System includes
#include <iostream>

// 3rd party includes
#include "MFixedPoint/FpS.hpp"
#include "MFixedPoint/FpF.hpp"

using namespace mn::MFixedPoint;

int main() {
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
    std::cout << "My fast 32-bit fixed-point number = " << fpNum4.ToDouble();
    
    // Converting between different precisions. Requires access to raw value just like
    // when doing fixed-point to double conversion.
    FpF32<20> aHigherPrecisionNum(7.5);
    // FpF32<12> aLowerPrecisionNum.rawVal = aHigherPrecisionNum.rawVal >> (20 - 12);
    
    // You can use 64-bit fixed point numbers in exactly the same way!
    FpF64<48> aFp64Num(4.58676);
    
    // Creating a 32-bit slow fixed-point number (notice the slightly different syntax)
    FpS32 fpSNum1(12.23, 12);
    
    // You can cast slow 32-bit fixed-point numbers back to doubles
    // (you can't do this with the fast fixed-point data types)
    std::cout << "My slow 32-bit fixed-point number = " << (double)fpSNum1; 
    
    return 0;
}