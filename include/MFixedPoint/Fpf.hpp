///
/// \file 				Fpf.hpp
/// \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja), Markus Trenkwalder
/// \edited 			n/a
/// \created			2012-10-23
/// \last-modified		2018-01-08
/// \brief 				Fast 32-bit fixed point library.
/// \details
///		See README.rst in root dir for more info.


/* Original copyright notice
Copyright (c) 2007, Markus Trenkwalder

All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, 
  this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation 
  and/or other materials provided with the distribution.

* Neither the name of the library's copyright owner nor the names of its 
  contributors may be used to endorse or promote products derived from this 
  software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#ifndef MN_MFIXEDPOINT_FPF_H
#define MN_MFIXEDPOINT_FPF_H

#include <stdint.h>

// Fixed-point configuration file
#include "Config.hpp"

// Port-specific code
#include "Port.hpp"

namespace mn {
namespace MFixedPoint {

// The template argument q in all of the following functions refers to the 
// fixed point precision (e.g. q = 8 gives 24.8 fixed point functions).

/// \brief		Perform a fixed point multiplication without a 64-bit intermediate result.
///	\note 		This is fast but beware of intermediary overflow!
template <uint8_t q> 
inline int32_t FixMulF(int32_t a, int32_t b)
{
	return (a * b) >> q;
}

/// \brief		Perform a fixed point multiplication using a 64-bit intermediate result to
/// 			prevent intermediary overflow problems.
/// \note 		Slower than Fpf::FixMulF()
template <uint8_t q>
inline int32_t FixMul(int32_t a, int32_t b)
{
	return (int32_t)(((int64_t)a * b) >> q);
}

// Fixed point division
template <uint8_t q>
inline int32_t fixdiv(int32_t a, int32_t b)
{
	#if 0
		return (int32_t)((((int64_t)a) << q) / b);
	#else	
		// The following produces the same results as the above but gcc 4.0.3 
		// generates fewer instructions (at least on the ARM processor).
		union {
			int64_t a;
			struct {
				int32_t l;
				int32_t h;
			};
		} x;

		x.l = a << q;
		x.h = a >> (sizeof(int32_t) * 8 - q);
		return (int32_t)(x.a / b);
	#endif
}

namespace detail {
	inline uint32_t CountLeadingZeros(uint32_t x)
	{
		uint32_t exp = 31;
	
		if (x & 0xffff0000) { 
			exp -= 16; 
			x >>= 16; 
		}
	
		if (x & 0xff00) { 
			exp -= 8; 
			x >>= 8; 
		}
		
		if (x & 0xf0) { 
			exp -= 4; 
			x >>= 4; 
		}
	
		if (x & 0xc) { 
			exp -= 2; 
			x >>= 2; 
		}
		
		if (x & 0x2) { 
			exp -= 1; 
		}
	
		return exp;
	}
}

// q is the precision of the input
// output has 32-q bits of fraction
template <uint8_t q>
inline int32_t fixinv(int32_t a)
{
	int32_t x;

	bool sign = false;

	if (a < 0) {
		sign = true;
		a = -a;
	}

	static const uint16_t rcp_tab[] = { 
		0x8000, 0x71c7, 0x6666, 0x5d17, 0x5555, 0x4ec4, 0x4924, 0x4444
	};
		
	int32_t exp = detail::CountLeadingZeros(a);
	x = ((int32_t)rcp_tab[(a>>(28-exp))&0x7]) << 2;
	exp -= 16;

	if (exp <= 0)
		x >>= -exp;
	else
		x <<= exp;

	// Two iterations of newton-raphson  x = x(2-ax)
	x = FixMul<(32-q)>(x,((2<<(32-q)) - FixMul<q>(a,x)));
	x = FixMul<(32-q)>(x,((2<<(32-q)) - FixMul<q>(a,x)));

	if (sign)
		return -x;
	else
		return x;
}

/// \brief		Converts from float to a raw 32-bit fixed-point number.
/// \details	Do not write "myFpNum = FloatToRawFix32()"! This function outputs a raw
///				number, so you would have to use the syntax "myFpNum.rawVal = FloatToRawFix32()".
/// \warning	Slow!
template <uint8_t q>
int32_t FloatToRawFix32(float f) {
	return (int32_t)(f * (1 << q));
}

/// \brief		Converts from double to a raw 32-bit fixed-point number.
/// \details	Do not write "myFpNum = DoubleToRawFix32()"! This function outputs a raw
///				number, so you would have to use the syntax "myFpNum.rawVal = DoubleToRawFix32()".
/// \warning	Slow!
template <uint8_t q>
int32_t DoubleToRawFix32(double f) {
	return (int32_t)(f * (double)(1 << q));
}



int32_t fixcos16(int32_t a);
int32_t fixsin16(int32_t a);
int32_t fixrsqrt16(int32_t a);
int32_t fixsqrt16(int32_t a);

/// \brief		Represents a 32-bit fixed point number, with the template argument providing
///				the number of fractional bits (and consequentially also defining the number of
///				integer bits).
/// \details	The template argument p in all of the following functions refers to the 
/// 			number of fractional bits (e.g. q = 8 gives Q24.8 fixed point functions).
/// 			Contains mathematical operator overloading. Doesn't have modulus (%) overloading
template <class BaseType, std::size_t numFracBits>
class Fpf {
	
	public:
	
	/// \brief		The fixed-point number is stored in this basic data type.
	BaseType rawVal;			
	
	Fpf()
	{
		#if(fpConfig_PRINT_DEBUG_GENERAL == 1)
			//Port::DebugPrint("FP: New fixed-point object created.");
		#endif
	}
	
	Fpf(int8_t i) :
		rawVal((int32_t)i << numFracBits)	{}
	
	Fpf(int16_t i) :
		rawVal((int32_t)i << numFracBits)	{}
	
	Fpf(int32_t i) :
		rawVal(i << numFracBits) { }
	
	/// \brief		Constructor that accepts a float.
	Fpf(float f) :
		rawVal(FloatToRawFix32<numFracBits>(f)) {}
	
	/// \warning	Double is converted to float first.
	Fpf(double f) :
		rawVal(FloatToRawFix32<numFracBits>((float)f)) {}
	
	// Compound Arithmetic Overloads
	
	Fpf& operator += (Fpf r) {
		rawVal += r.rawVal;
		return *this;
	}
	
	Fpf& operator -= (Fpf r) {
		rawVal -= r.rawVal;
		return *this;
	}
	
	/// \brief		Overlaod for '*=' operator.
	/// \details	Uses intermediatary casting to int64_t to prevent overflows.
	Fpf& operator *= (Fpf r) {
		rawVal = FixMul<numFracBits>(rawVal, r.rawVal);
		return *this;
	}
	
	/// \brief		Overlaod for '/=' operator.
	/// \details	Uses intermediatary casting to int64_t to prevent overflows.
	Fpf& operator /= (Fpf r) {
		rawVal = fixdiv<numFracBits>(rawVal, r.rawVal);
		return *this;
	}
	
	/// \brief		Overlaod for '%=' operator.
	Fpf& operator %= (Fpf r) {
		rawVal %= r.rawVal;
		return *this;
	}
	
	
	Fpf& operator *= (int32_t r) {
		rawVal *= r;
		return *this;
	}
	
	Fpf& operator /= (int32_t r) { 
		rawVal /= r;
		return *this;
	}
	
	// Simple Arithmetic Overloads
	
	/// \brief		Overload for '-itself' operator.
	Fpf operator - () const
	{
		Fpf x;
		x.rawVal = -rawVal;
		return x;
	}
	
	/// \brief		Overload for '+' operator.
	/// \details	Uses '+=' operator.
	Fpf operator + (Fpf r) const
	{
		Fpf x = *this;
		x += r;
		return x;
	}
	
	/// \brief		Overload for '-' operator.
	/// \details	Uses '-=' operator.
	Fpf operator - (Fpf r) const
	{
		Fpf x = *this;
		x -= r;
		return x;
	}
	
	/// \brief		Overload for '*' operator.
	/// \details	Uses '*=' operator.
	Fpf operator * (Fpf r) const
	{
		Fpf x = *this;
		x *= r;
		return x;
	}
	
	/// \brief		Overload for '/' operator.
	/// \details	Uses '/=' operator.
	Fpf operator / (Fpf r) const
	{
		Fpf x = *this;
		x /= r;
		return x;
	}
	
	/// \brief		Overload for '%' operator.
	/// \details	Uses '%=' operator.
	Fpf operator % (Fpf r) const
	{
		Fpf x = *this;
		x %= r;
		return x;
	}
	
	// Fpf-Fpf Binary Operator Overloads
	
	bool operator == (Fpf r) const
	{
		return rawVal == r.rawVal;
	}
	
	bool operator != (const Fpf &r)
	{
		return !(*this == r);
	}
	
	bool operator <  (const Fpf &r)
	{
		return rawVal < r.rawVal;
	}
	
	bool operator >  (const Fpf &r)
	{
		return rawVal > r.rawVal;
	}
	
	bool operator <= (Fpf r) const
	{
		return rawVal <= r.rawVal;
	}
	
	bool operator >= (Fpf r) const
	{
		return rawVal >= r.rawVal;
	}
	
	/// \defgroup From Fpf Conversion Overloads (casts)
	/// \{
	
	/// \brief		Conversion operator from fixed-point to int16_t.
	/// \warning	Possible loss of accuracy from conversion from
	///				int32_t to int16_t.
	operator int16_t() {
		// Right-shift to get rid of all the decimal bits (truncate)
		return (int16_t)(rawVal >> numFracBits);
	}
	
	/// \brief		Conversion operator from fixed-point to int32_t.
	operator int32_t() {
		// Right-shift to get rid of all the decimal bits (truncate)
		return (rawVal >> numFracBits);
	}
	
	/// \brief		Conversion operator from fixed-point to int64_t.
	operator int64_t() {
		// Right-shift to get rid of all the decimal bits (truncate)
		return (int64_t)(rawVal >> numFracBits);
	}
	
	/// \brief		Conversion operator from fixed-point to float.
	operator float() { 
		return (float)rawVal / (float)(1 << numFracBits);
	}
	
	/// \brief		Conversion operator from fixed-point to double.
	/// \note		Similar to float conversion.
	operator double() { 
		return (double)rawVal / (double)(1 << numFracBits);
	}
	
	/// \}
	
	/// \addgroup Overloads Between Fpf And int32_t
	/// \{

	/// \brief		Addition operator overload.
	Fpf operator + (int32_t r) const {
		Fpf x = *this;
		x += r;
		return x;
	}
	
	Fpf operator - (int32_t r) const {
		Fpf x = *this;
		x -= r;
		return x;
	}
	
	Fpf operator * (int32_t r) const {
		Fpf x = *this;
		x *= r;
		return x;
	}
	
	Fpf operator / (int32_t r) const {
		Fpf x = *this;
		x /= r;
		return x;
	}
	
	bool operator >  (int32_t r) const {
		return rawVal > (r << numFracBits);
	}
	
	bool operator >=  (int32_t r) const {
		return rawVal >= (r << numFracBits);
	}
	
	bool operator <  (int32_t r) const {
		return rawVal < (r << numFracBits);
	}
	
	bool operator <=  (int32_t r) const	{
		return rawVal < (r << numFracBits);
	}
	
	bool operator ==  (int32_t r) const	{
		return rawVal == (r << numFracBits);
	}
	
	bool operator !=  (int32_t r) const	{
		return rawVal != (r << numFracBits);
	}

	/// \}
	
};

// Specializations for use with plain integers

/// \note 		Assumes integer has the same precision as Fpf
// template <uint8_t numFracBits>
// inline Fpf<numFracBits> operator + (int32_t a, Fpf<numFracBits> b)
// { 
// 	return b + a; 
// }

// /// \note 		Assumes integer has the same precision as Fpf
// template <uint8_t numFracBits>
// inline Fpf<numFracBits> operator - (int32_t a, Fpf<numFracBits> b)
// {
// 	return -b + a;
// }

// /// \note 		Assumes integer has the same precision as Fpf
// template <uint8_t numFracBits>
// inline Fpf<numFracBits> operator * (int32_t a, Fpf<numFracBits> b)
// { return b * a; }

// template <uint8_t numFracBits>
// inline Fpf<numFracBits> operator / (int32_t a, Fpf<numFracBits> b)
// { 
// 	Fpf<numFracBits> r(a); 
// 	r /= b; 
// 	return r;
// }

// math functions
// no default implementation

// template <uint8_t numFracBits>
// inline Fpf<numFracBits> sin(Fpf<numFracBits> a);

// template <uint8_t numFracBits>
// inline Fpf<numFracBits> cos(Fpf<numFracBits> a);

// template <uint8_t numFracBits>
// inline Fpf<numFracBits> sqrt(Fpf<numFracBits> a);

// template <uint8_t numFracBits>
// inline Fpf<numFracBits> rsqrt(Fpf<numFracBits> a);

// template <uint8_t numFracBits>
// inline Fpf<numFracBits> inv(Fpf<numFracBits> a);

// template <uint8_t numFracBits>
// inline Fpf<numFracBits> abs(Fpf<numFracBits> a)
// { 
// 	Fpf<numFracBits> r; 
// 	r.rawVal = a.rawVal > 0 ? a.rawVal : -a.rawVal; 
// 	return r; 
// }

// // Specializations for 16.16 format

// template <>
// inline Fpf<16> sin(Fpf<16> a)
// {
// 	Fpf<16> r;
// 	r.rawVal = fixsin16(a.rawVal);
// 	return r;
// }

// template <>
// inline Fpf<16> cos(Fpf<16> a)
// {
// 	Fpf<16> r;
// 	r.rawVal = fixcos16(a.rawVal);
// 	return r;
// }


// template <>
// inline Fpf<16> sqrt(Fpf<16> a)
// {
// 	Fpf<16> r;
// 	r.rawVal = fixsqrt16(a.rawVal);
// 	return r;
// }

// template <>
// inline Fpf<16> rsqrt(Fpf<16> a)
// {
// 	Fpf<16> r;
// 	r.rawVal = fixrsqrt16(a.rawVal);
// 	return r;
// }

// template <>
// inline Fpf<16> inv(Fpf<16> a)
// {
// 	Fpf<16> r;
// 	r.rawVal = fixinv<16>(a.rawVal);
// 	return r;
// }

// // The multiply accumulate case can be optimized.
// template <uint8_t numFracBits>
// inline Fpf<numFracBits> multiply_accumulate(
// 	int32_t count, 
// 	const Fpf<numFracBits> *a,
// 	const Fpf<numFracBits> *b)
// {
// 	long long result = 0;
// 	for (int32_t i = 0; i < count; ++i)
// 		result += static_cast<long long>(a[i].rawVal) * b[i].rawVal;
// 	Fpf<numFracBits> r;
// 	r.rawVal = static_cast<int32_t>(result >> numFracBits);
// 	return r;
// }

//===============================================================================================//
//======================================== GRAVEYARD ============================================//
//===============================================================================================//

/*
/// \brief		Conversion from fixed-point to float.
/// \details	Good for debugging fixed-point arithmetic.
/// \warning 	Slow!
template <uint8_t q>
float Fix32ToFloat(int32_t f)
{
	return (float)f / (1 << q);
}

/// \brief		Conversion from fixed-point to float.
/// \details	Good for debugging fixed-point arithmetic.
/// \warning 	Slow!
template <uint8_t q>
double Fix32ToDouble(int32_t f)
{
	return (double)f / (double)(1 << q);
}
*/

} // namespace MFixedPoint
} //namespace mn

#endif // #ifndef MN_MFIXEDPOINT_FPF_H

// EOF
