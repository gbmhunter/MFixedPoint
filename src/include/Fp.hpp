//!
//! @file 		Fp.hpp
//! @author 	Markus Trenkwalder
//! @edited 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2012/10/23
//! @brief 		Header file for Fp.cpp
//! @details
//!		<b>Last Modified:			</b> 2013/05/09				\n
//!		<b>Version:					</b> v2.0.0.0					\n
//!		<b>Company:					</b> CladLabs					\n
//!		<b>Project:					</b> Free code libraries		\n
//!		<b>Language:				</b> C++						\n
//!		<b>Compiler:				</b> GCC						\n
//! 	<b>uC Model:				</b> PSoC5						\n
//!		<b>Computer Architecture:	</b> ARM						\n
//! 	<b>Operating System:		</b> FreeRTOS v7.2.0			\n
//!		<b>Documentation Format:	</b> Doxygen					\n
//!		<b>License:					</b> (see below)				\n
//!
//!		Fixed-point library for fast arithmetic operations. Designed
//!		for use on a 32-bit architecture. Fixed-point numbers are
//!		signed. Class supports dynamic precision, determined
//!		with variable p which denotes fractional precision. The
//!		integer precision is (32 bits - p). Overflows will wrap. 
//!		Support operator oveloading for most common fixed-point
//!		arithemetic.
//!
//!		See below for original copyright notice.
//!
//!		CHANGELOG:
//!			v1.1.0 		-> (12/10/23) Merged fixed_func.h into this file. Added
//!				comments. Changed fixed_point to fp.
//!			v1.1.1 		-> (12/11/04) Fixed filename errors. Attributed Markus
//!				Trenkwalder as the original author.
//!			v1.2.0 		-> (12/11/04) Made fp a class with public members, 
//!				rather than structure.
//!			v1.3.0 		-> (12/11/05) Added operator overload for '%'. Tested
//!				and works fine.
//!			v1.3.1 		-> (12/11/05) Added library description.
//!			v1.3.1.1 	-> (13/05/08) Moved Fp.h into ./src/include/. Changed to 4-digit
//!				versioning system. Changed incorrect date.
//!			v1.3.1.2	-> (13/05/08) Indented all namespace objects (formatting issue).
//!			v1.3.2.0	-> (13/05/09) Renamed Fp.h to Fp.hpp. Removed doubling up of
//!							version in both files, now just defined in Fp.hpp. Added dates
//!							to version numbers. Added C++ guard at the start of both Fp.cpp
//!							and Fp.hpp.
//!			v2.0.0.0	-> (13/05/09) Added support for 64-bit fixed point numbers (Fp64.h).

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

#ifndef FP_H
#define FP_H

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

namespace Fp
{

	// The template argument p in all of the following functions refers to the 
	// fixed point precision (e.g. p = 8 gives 24.8 fixed point functions).

	//! @brief		Perform a fixed point multiplication without a 64-bit intermediate result.
	//!	@note 		This is fast but beware of intermediatry overflow!
	template <int p> 
	inline int32_t FixMulF(int32_t a, int32_t b)
	{
		return (a * b) >> p;
	}

	//! @brief		Perform a fixed point multiplication using a 64-bit intermediate result to
	//! 			prevent intermediatry overflow problems.
	//! @note 		Slower than Fp::FixMulF()
	template <int p>
	inline int32_t FixMul(int32_t a, int32_t b)
	{
		return (int32_t)(((int64_t)a * b) >> p);
	}

	// Fixed point division
	template <int p>
	inline int fixdiv(int32_t a, int32_t b)
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
	template <int q>
	inline int fixinv(int32_t a)
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
	template <int p>
	float Fix2Float(int32_t f)
	{
		return (float)f / (1 << p);
	}

	//! @brief		Converts from float to fixed-point
	//! @details	Good for inputting values into fixed-point arithmetic
	//! @warning	Slow!
	template <int p>
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
	template <int p>
	class fp {
		
		public:
		
		int32_t intValue;			//!< Access to raw value
		
		fp() {}
		/*explicit*/ fp(int32_t i) : intValue(i << p) {}
		/*explicit*/ fp(float f) : intValue(Float2Fix<p>(f)) {}
		/*explicit*/ fp(double f) : intValue(Float2Fix<p>((float)f)) {}
		
		fp& operator += (fp r) { intValue += r.intValue; return *this; }
		fp& operator -= (fp r) { intValue -= r.intValue; return *this; }
		fp& operator *= (fp r) { intValue = FixMul<p>(intValue, r.intValue); return *this; }
		fp& operator /= (fp r) { intValue = fixdiv<p>(intValue, r.intValue); return *this; }
		
		fp& operator *= (int32_t r) { intValue *= r; return *this; }
		fp& operator /= (int32_t r) { intValue /= r; return *this; }
		
		fp operator - () const { fp x; x.intValue = -intValue; return x; }
		fp operator + (fp r) const { fp x = *this; x += r; return x;}
		fp operator - (fp r) const { fp x = *this; x -= r; return x;}
		fp operator * (fp r) const { fp x = *this; x *= r; return x;}
		fp operator / (fp r) const { fp x = *this; x /= r; return x;}
		
		//! Operator overload for '%'. Modulo works on bits as long
		//! as fixed-point numbers are of the same precision.
		const fp operator % (fp r) 
		{
			fp result;
			result.intValue = intValue % r.intValue;
			return result;
		}
		
		bool operator == (fp r) const { return intValue == r.intValue; }
		bool operator != (fp r) const { return !(*this == r); }
		bool operator <  (fp r) const { return intValue < r.intValue; }
		bool operator >  (fp r) const { return intValue > r.intValue; }
		bool operator <= (fp r) const { return intValue <= r.intValue; }
		bool operator >= (fp r) const { return intValue >= r.intValue; }

		fp operator + (int32_t r) const { fp x = *this; x += r; return x;}
		fp operator - (int32_t r) const { fp x = *this; x -= r; return x;}
		fp operator * (int32_t r) const { fp x = *this; x *= r; return x;}
		fp operator / (int32_t r) const { fp x = *this; x /= r; return x;}
	};

	// Specializations for use with plain integers

	//! @note 		Assumes integer has the same precision as fp
	template <int p>
	inline fp<p> operator + (int32_t a, fp<p> b)
	{ 
		return b + a; 
	}

	//! @note 		Assumes integer has the same precision as fp
	template <int p>
	inline fp<p> operator - (int32_t a, fp<p> b)
	{
		return -b + a;
	}

	//! @note 		Assumes integer has the same precision as fp
	template <int p>
	inline fp<p> operator * (int32_t a, fp<p> b)
	{ return b * a; }

	template <int p>
	inline fp<p> operator / (int32_t a, fp<p> b)
	{ 
		fp<p> r(a); 
		r /= b; 
		return r;
	}

	// math functions
	// no default implementation

	template <int p>
	inline fp<p> sin(fp<p> a);

	template <int p>
	inline fp<p> cos(fp<p> a);

	template <int p>
	inline fp<p> sqrt(fp<p> a);

	template <int p>
	inline fp<p> rsqrt(fp<p> a);

	template <int p>
	inline fp<p> inv(fp<p> a);

	template <int p>
	inline fp<p> abs(fp<p> a)
	{ 
		fp<p> r; 
		r.intValue = a.intValue > 0 ? a.intValue : -a.intValue; 
		return r; 
	}

	// Specializations for 16.16 format

	template <>
	inline fp<16> sin(fp<16> a)
	{
		fp<16> r;
		r.intValue = fixsin16(a.intValue);
		return r;
	}

	template <>
	inline fp<16> cos(fp<16> a)
	{
		fp<16> r;
		r.intValue = fixcos16(a.intValue);
		return r;
	}


	template <>
	inline fp<16> sqrt(fp<16> a)
	{
		fp<16> r;
		r.intValue = fixsqrt16(a.intValue);
		return r;
	}

	template <>
	inline fp<16> rsqrt(fp<16> a)
	{
		fp<16> r;
		r.intValue = fixrsqrt16(a.intValue);
		return r;
	}

	template <>
	inline fp<16> inv(fp<16> a)
	{
		fp<16> r;
		r.intValue = fixinv<16>(a.intValue);
		return r;
	}

	// The multiply accumulate case can be optimized.
	template <int p>
	inline fp<p> multiply_accumulate(
		int count, 
		const fp<p> *a,
		const fp<p> *b)
	{
		long long result = 0;
		for (int i = 0; i < count; ++i)
			result += static_cast<long long>(a[i].intValue) * b[i].intValue;
		fp<p> r;
		r.intValue = static_cast<int>(result >> p);
		return r;
	}

} // namespace Fp

#endif // #ifndef FIXEDP_CLASS_H_INCLUDED

// EOF