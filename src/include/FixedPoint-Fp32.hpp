//!
//! @file 		Fp32.hpp
//! @author 	Markus Trenkwalder
//! @edited 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2012/10/23
//! @brief 		32-bit fixed point library.
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

#ifndef FP32_H
#define FP32_H

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
	template <int32_t p> 
	inline int32_t FixMulF(int32_t a, int32_t b)
	{
		return (a * b) >> p;
	}

	//! @brief		Perform a fixed point multiplication using a 64-bit intermediate result to
	//! 			prevent intermediatry overflow problems.
	//! @note 		Slower than Fp32::FixMulF()
	template <int32_t p>
	inline int32_t FixMul(int32_t a, int32_t b)
	{
		return (int32_t)(((int64_t)a * b) >> p);
	}

	// Fixed point division
	template <int32_t p>
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
	template <int32_t q>
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


	//! @brief		Conversion from fixed-point to float
	//! @details	Good for debugging fixed-point arithmetic
	//! @warning 	Slow!
	//! @public
	template <int32_t p>
	float Fix2Float(int32_t f)
	{
		return (float)f / (1 << p);
	}

	//! @brief		Converts from float to fixed-point
	//! @details	Good for inputting values into fixed-point arithmetic
	//! @warning	Slow!
	template <int32_t p>
	int32_t Float2Fix(float f)
	{
		return (int32_t)(f * (1 << p));
	}

	int32_t fixcos16(int32_t a);
	int32_t fixsin16(int32_t a);
	int32_t fixrsqrt16(int32_t a);
	int32_t fixsqrt16(int32_t a);

	//! The template argument p in all of the following functions refers to the 
	//! fixed point precision (e.g. p = 8 gives 24.8 fixed point functions).
	//! Contains mathematical operator overloading. Doesn't have modulus (%) overloading
	template <int32_t p>
	class Fp32 {
		
		public:
		
		int32_t rawVal;			//!< Access to raw value
		
		Fp32()
		{
			#if(fpConfig_PRINT_DEBUG_GENERAL == 1)
				//Port::DebugPrint("FP: New fixed-point object created.");
			#endif
		}
		/*explicit*/ Fp32(int32_t i) : rawVal(i << p) {}
		/*explicit*/ Fp32(float f) : rawVal(Float2Fix<p>(f)) {}
		/*explicit*/ Fp32(double f) : rawVal(Float2Fix<p>((float)f)) {}
		
		Fp32& operator += (Fp32 r) { rawVal += r.rawVal; return *this; }
		Fp32& operator -= (Fp32 r) { rawVal -= r.rawVal; return *this; }
		Fp32& operator *= (Fp32 r) { rawVal = FixMul<p>(rawVal, r.rawVal); return *this; }
		Fp32& operator /= (Fp32 r) { rawVal = fixdiv<p>(rawVal, r.rawVal); return *this; }
		
		Fp32& operator *= (int32_t r) { rawVal *= r; return *this; }
		Fp32& operator /= (int32_t r) { rawVal /= r; return *this; }
		
		Fp32 operator - () const { Fp32 x; x.rawVal = -rawVal; return x; }
		Fp32 operator + (Fp32 r) const { Fp32 x = *this; x += r; return x;}
		Fp32 operator - (Fp32 r) const { Fp32 x = *this; x -= r; return x;}
		Fp32 operator * (Fp32 r) const { Fp32 x = *this; x *= r; return x;}
		Fp32 operator / (Fp32 r) const { Fp32 x = *this; x /= r; return x;}
		
		//! Operator overload for '%'. Modulo works on bits as long
		//! as fixed-point numbers are of the same precision.
		const Fp32 operator % (Fp32 r) 
		{
			Fp32 result;
			result.rawVal = rawVal % r.rawVal;
			return result;
		}
		
		bool operator == (Fp32 r) const { return rawVal == r.rawVal; }
		bool operator != (Fp32 r) const { return !(*this == r); }
		bool operator <  (Fp32 r) const { return rawVal < r.rawVal; }
		bool operator >  (Fp32 r) const { return rawVal > r.rawVal; }
		bool operator <= (Fp32 r) const { return rawVal <= r.rawVal; }
		bool operator >= (Fp32 r) const { return rawVal >= r.rawVal; }

		Fp32 operator + (int32_t r) const { Fp32 x = *this; x += r; return x;}
		Fp32 operator - (int32_t r) const { Fp32 x = *this; x -= r; return x;}
		Fp32 operator * (int32_t r) const { Fp32 x = *this; x *= r; return x;}
		Fp32 operator / (int32_t r) const { Fp32 x = *this; x /= r; return x;}
	};

	// Specializations for use with plain integers

	//! @note 		Assumes integer has the same precision as Fp32
	template <int32_t p>
	inline Fp32<p> operator + (int32_t a, Fp32<p> b)
	{ 
		return b + a; 
	}

	//! @note 		Assumes integer has the same precision as Fp32
	template <int32_t p>
	inline Fp32<p> operator - (int32_t a, Fp32<p> b)
	{
		return -b + a;
	}

	//! @note 		Assumes integer has the same precision as Fp32
	template <int32_t p>
	inline Fp32<p> operator * (int32_t a, Fp32<p> b)
	{ return b * a; }

	template <int32_t p>
	inline Fp32<p> operator / (int32_t a, Fp32<p> b)
	{ 
		Fp32<p> r(a); 
		r /= b; 
		return r;
	}

	// math functions
	// no default implementation

	template <int32_t p>
	inline Fp32<p> sin(Fp32<p> a);

	template <int32_t p>
	inline Fp32<p> cos(Fp32<p> a);

	template <int32_t p>
	inline Fp32<p> sqrt(Fp32<p> a);

	template <int32_t p>
	inline Fp32<p> rsqrt(Fp32<p> a);

	template <int32_t p>
	inline Fp32<p> inv(Fp32<p> a);

	template <int32_t p>
	inline Fp32<p> abs(Fp32<p> a)
	{ 
		Fp32<p> r; 
		r.rawVal = a.rawVal > 0 ? a.rawVal : -a.rawVal; 
		return r; 
	}

	// Specializations for 16.16 format

	template <>
	inline Fp32<16> sin(Fp32<16> a)
	{
		Fp32<16> r;
		r.rawVal = fixsin16(a.rawVal);
		return r;
	}

	template <>
	inline Fp32<16> cos(Fp32<16> a)
	{
		Fp32<16> r;
		r.rawVal = fixcos16(a.rawVal);
		return r;
	}


	template <>
	inline Fp32<16> sqrt(Fp32<16> a)
	{
		Fp32<16> r;
		r.rawVal = fixsqrt16(a.rawVal);
		return r;
	}

	template <>
	inline Fp32<16> rsqrt(Fp32<16> a)
	{
		Fp32<16> r;
		r.rawVal = fixrsqrt16(a.rawVal);
		return r;
	}

	template <>
	inline Fp32<16> inv(Fp32<16> a)
	{
		Fp32<16> r;
		r.rawVal = fixinv<16>(a.rawVal);
		return r;
	}

	// The multiply accumulate case can be optimized.
	template <int32_t p>
	inline Fp32<p> multiply_accumulate(
		int32_t count, 
		const Fp32<p> *a,
		const Fp32<p> *b)
	{
		long long result = 0;
		for (int32_t i = 0; i < count; ++i)
			result += static_cast<long long>(a[i].rawVal) * b[i].rawVal;
		Fp32<p> r;
		r.rawVal = static_cast<int32_t>(result >> p);
		return r;
	}

} // namespace Fp

#endif // #ifndef FP32_H

// EOF