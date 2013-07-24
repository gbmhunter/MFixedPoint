//!
//! @file 		FixedPoint-Fp32f.hpp
//! @author 	Markus Trenkwalder
//! @edited 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2012/10/23
//! @brief 		Fast 32-bit fixed point library.
//! @details
//!				See README.rst in root dir for more info.


/*
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

#ifndef FP32F_H
#define FP32F_H

#include <stdint.h>

// Fixed-point configuration file
#include "FixedPoint-Config.hpp"

// Port-specific code
#include "FixedPoint-Port.hpp"

namespace Fp
{

	// The template argument p in all of the following functions refers to the 
	// fixed point precision (e.g. p = 8 gives 24.8 fixed point functions).

	//! @brief		Perform a fixed point multiplication without a 64-bit intermediate result.
	//!	@note 		This is fast but beware of intermediatry overflow!
	template <uint8_t p> 
	inline int32_t FixMulF(int32_t a, int32_t b)
	{
		return (a * b) >> p;
	}

	//! @brief		Perform a fixed point multiplication using a 64-bit intermediate result to
	//! 			prevent intermediatry overflow problems.
	//! @note 		Slower than Fp32f::FixMulF()
	template <uint8_t p>
	inline int32_t FixMul(int32_t a, int32_t b)
	{
		return (int32_t)(((int64_t)a * b) >> p);
	}

	// Fixed point division
	template <uint8_t p>
	inline int32_t fixdiv(int32_t a, int32_t b)
	{
		#if 0
			return (int32_t)((((int64_t)a) << p) / b);
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

			x.l = a << p;
			x.h = a >> (sizeof(int32_t) * 8 - p);
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

	//! @brief		Converts from float to fixed-point.
	//! @details	Good for inputting values into fixed-point arithmetic.
	//! @warning	Slow!
	template <uint8_t p>
	int32_t FloatToFix32(float f)
	{
		return (int32_t)(f * (1 << p));
	}
	
	//! @brief		Converts from double to fixed-point.
	//! @details	Good for inputting values into fixed-point arithmetic.
	//! @warning	Slow!
	template <uint8_t p>
	int32_t DoubleToFix32(double f)
	{
		return (int32_t)(f * (double)(1 << p));
	}
	
	//! @brief		Conversion from fixed-point to float.
	//! @details	Good for debugging fixed-point arithmetic.
	//! @warning 	Slow!
	template <uint8_t p>
	float Fix32ToFloat(int32_t f)
	{
		return (float)f / (1 << p);
	}
	
	//! @brief		Conversion from fixed-point to float.
	//! @details	Good for debugging fixed-point arithmetic.
	//! @warning 	Slow!
	template <uint8_t p>
	float Fix32ToDouble(int32_t f)
	{
		return (double)f / (double)(1 << p);
	}

	int32_t fixcos16(int32_t a);
	int32_t fixsin16(int32_t a);
	int32_t fixrsqrt16(int32_t a);
	int32_t fixsqrt16(int32_t a);

	//! The template argument p in all of the following functions refers to the 
	//! fixed point precision (e.g. p = 8 gives 24.8 fixed point functions).
	//! Contains mathematical operator overloading. Doesn't have modulus (%) overloading
	template <uint8_t p>
	class Fp32f {
		
		public:
		
		//! @brief		The fixed-point number is stored in this basic data type.
		int32_t rawVal;			
		
		Fp32f()
		{
			#if(fpConfig_PRINT_DEBUG_GENERAL == 1)
				//Port::DebugPrint("FP: New fixed-point object created.");
			#endif
		}
		/*explicit*/ Fp32f(int32_t i) : rawVal(i << p) {}
		/*explicit*/ Fp32f(float f) : rawVal(FloatToFix32<p>(f)) {}
		/*explicit*/ Fp32f(double f) : rawVal(FloatToFix32<p>((float)f)) {}
		
		// Compound Arithmetic Overloads
		
		Fp32f& operator += (Fp32f r)
		{
			rawVal += r.rawVal;
			return *this;
		}
		
		Fp32f& operator -= (Fp32f r)
		{
			rawVal -= r.rawVal;
			return *this;
		}
		
		Fp32f& operator *= (Fp32f r)
		{
			rawVal = FixMul<p>(rawVal, r.rawVal);
			return *this;
		}
		
		Fp32f& operator /= (Fp32f r)
		{
			rawVal = fixdiv<p>(rawVal, r.rawVal);
			return *this;
		}
		
		//! @brief		Overlaod for '%=' operator.
		Fp32f& operator %= (Fp32f r)
		{
			rawVal %= r.rawVal;
			return *this;
		}
		
		Fp32f& operator *= (int32_t r)
		{
			rawVal *= r;
			return *this;
		}
		
		Fp32f& operator /= (int32_t r)
		{ 
			rawVal /= r;
			return *this;
		}
		
		// Simple Arithmetic Overloads
		
		//! @brief		Overload for '-itself' operator.
		Fp32f operator - () const
		{
			Fp32f x;
			x.rawVal = -rawVal;
			return x;
		}
		
		//! @brief		Overload for '+' operator.
		//! @details	Uses '+=' operator.
		Fp32f operator + (Fp32f r) const
		{
			Fp32f x = *this;
			x += r;
			return x;
		}
		
		//! @brief		Overload for '-' operator.
		//! @details	Uses '-=' operator.
		Fp32f operator - (Fp32f r) const
		{
			Fp32f x = *this;
			x -= r;
			return x;
		}
		
		//! @brief		Overload for '*' operator.
		//! @details	Uses '*=' operator.
		Fp32f operator * (Fp32f r) const
		{
			Fp32f x = *this;
			x *= r;
			return x;
		}
		
		//! @brief		Overload for '/' operator.
		//! @details	Uses '/=' operator.
		Fp32f operator / (Fp32f r) const
		{
			Fp32f x = *this;
			x /= r;
			return x;
		}
		
		//! @brief		Overload for '%' operator.
		//! @details	Uses '%=' operator.
		Fp32f operator % (Fp32f r) const
		{
			Fp32f x = *this;
			x %= r;
			return x;
		}
		
		// Binary Operator Overloads
		
		bool operator == (Fp32f r) const
		{
			return rawVal == r.rawVal;
		}
		
		bool operator != (Fp32f r) const
		{
			return !(*this == r);
		}
		
		bool operator <  (Fp32f r) const
		{
			return rawVal < r.rawVal;
		}
		
		bool operator >  (Fp32f r) const
		{
			return rawVal > r.rawVal;
		}
		
		bool operator <= (Fp32f r) const
		{
			return rawVal <= r.rawVal;
		}
		
		bool operator >= (Fp32f r) const
		{
			return rawVal >= r.rawVal;
		}

		Fp32f operator + (int32_t r) const
		{
			Fp32f x = *this;
			x += r;
			return x;
		}
		
		Fp32f operator - (int32_t r) const
		{
			Fp32f x = *this;
			x -= r;
			return x;
		}
		
		Fp32f operator * (int32_t r) const
		{
			Fp32f x = *this;
			x *= r;
			return x;
		}
		
		Fp32f operator / (int32_t r) const
		{
			Fp32f x = *this;
			x /= r;
			return x;
		}
	};

	// Specializations for use with plain integers

	//! @note 		Assumes integer has the same precision as Fp32f
	template <uint8_t p>
	inline Fp32f<p> operator + (int32_t a, Fp32f<p> b)
	{ 
		return b + a; 
	}

	//! @note 		Assumes integer has the same precision as Fp32f
	template <uint8_t p>
	inline Fp32f<p> operator - (int32_t a, Fp32f<p> b)
	{
		return -b + a;
	}

	//! @note 		Assumes integer has the same precision as Fp32f
	template <uint8_t p>
	inline Fp32f<p> operator * (int32_t a, Fp32f<p> b)
	{ return b * a; }

	template <uint8_t p>
	inline Fp32f<p> operator / (int32_t a, Fp32f<p> b)
	{ 
		Fp32f<p> r(a); 
		r /= b; 
		return r;
	}

	// math functions
	// no default implementation

	template <uint8_t p>
	inline Fp32f<p> sin(Fp32f<p> a);

	template <uint8_t p>
	inline Fp32f<p> cos(Fp32f<p> a);

	template <uint8_t p>
	inline Fp32f<p> sqrt(Fp32f<p> a);

	template <uint8_t p>
	inline Fp32f<p> rsqrt(Fp32f<p> a);

	template <uint8_t p>
	inline Fp32f<p> inv(Fp32f<p> a);

	template <uint8_t p>
	inline Fp32f<p> abs(Fp32f<p> a)
	{ 
		Fp32f<p> r; 
		r.rawVal = a.rawVal > 0 ? a.rawVal : -a.rawVal; 
		return r; 
	}

	// Specializations for 16.16 format

	template <>
	inline Fp32f<16> sin(Fp32f<16> a)
	{
		Fp32f<16> r;
		r.rawVal = fixsin16(a.rawVal);
		return r;
	}

	template <>
	inline Fp32f<16> cos(Fp32f<16> a)
	{
		Fp32f<16> r;
		r.rawVal = fixcos16(a.rawVal);
		return r;
	}


	template <>
	inline Fp32f<16> sqrt(Fp32f<16> a)
	{
		Fp32f<16> r;
		r.rawVal = fixsqrt16(a.rawVal);
		return r;
	}

	template <>
	inline Fp32f<16> rsqrt(Fp32f<16> a)
	{
		Fp32f<16> r;
		r.rawVal = fixrsqrt16(a.rawVal);
		return r;
	}

	template <>
	inline Fp32f<16> inv(Fp32f<16> a)
	{
		Fp32f<16> r;
		r.rawVal = fixinv<16>(a.rawVal);
		return r;
	}

	// The multiply accumulate case can be optimized.
	template <uint8_t p>
	inline Fp32f<p> multiply_accumulate(
		int32_t count, 
		const Fp32f<p> *a,
		const Fp32f<p> *b)
	{
		long long result = 0;
		for (int32_t i = 0; i < count; ++i)
			result += static_cast<long long>(a[i].rawVal) * b[i].rawVal;
		Fp32f<p> r;
		r.rawVal = static_cast<int32_t>(result >> p);
		return r;
	}

} // namespace Fp

#endif // #ifndef FP32F_H

// EOF