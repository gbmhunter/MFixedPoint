//!
//! @file 		FixedPoint-Fp64f.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/05/09
//! @brief 		Fixed-point arithmetic for 64-bit numbers. Be careful of overflow!
//! @details
//!				See README.rst in root dir for more info.
//!


//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#ifndef FP64F_H
#define FP64F_H

#include <stdint.h>

namespace Fp
{

	//! @brief		Perform a fixed point multiplication without a 128-bit intermediate result.
	//!	@warning	This is fast but beware of intermediatry overflow!
	template <uint8_t p> 
	inline int64_t FixMulF(int64_t a, int64_t b)
	{
		// Rule with fixed-point multiplication, you have
		// to right-shift result by the precision.
		return (a * b) >> p;
	}
	
	//! @brief		Perform a fixed point division without a 128-bit intermediate result.
	//! @details	No loss of precision since shift is done before division.
	//!	@warning	This is fast but beware of intermediatry overflow!
	template <uint8_t p> 
	inline int64_t FixDiv(int64_t a, int64_t b)
	{
		// Rule with fixed-point division, have to left-shift numerator
		// before dividing by denominator
		return (int64_t)(((a) << p) / b);
	}
	
	//! @brief		Conversion from fixed-point to float.
	//! @details	Good for debugging fixed-point arithmetic.
	//! @warning 	Slow!
	//! @public
	template <uint8_t p>
	float Fix64ToFloat(int64_t f)
	{
		return (float)f / (float)(1 << p);
	}
	
	//! @brief		Conversion from fixed-point to double.
	//! @details	Good for debugging fixed-point arithmetic
	//! @warning 	Slow!
	//! @public
	template <uint8_t p>
	float Fix64ToDouble(int64_t f)
	{
		return (double)f / (double)(1 << p);
	}

	//! @brief		Converts from float to fixed-point
	//! @details	Good for inputting values into fixed-point arithmetic
	//! @warning	Slow!
	template <uint8_t p>
	int64_t FloatToFix64(float f)
	{
		return (int64_t)(f * (1 << p));
	}
	
	//! @brief		Converts from double to fixed-point
	//! @details	Good for inputting values into fixed-point arithmetic
	//! @warning	Slow!
	template <uint8_t p>
	int64_t DoubleToFix64(double f)
	{
		return (int64_t)(f * (double)(1 << p));
	}

	//! @brief		64-bit fixed-point library.
	//! @details	p may vary from 0-64
	template<uint8_t p> class Fp64f
	{
		public:
			//! @brief		The raw fixed-point value, stored as a int64.
			int64_t rawVal;
			
			//! @defgroup Constructors
			//! @{
			
			//! @brief			Default constructor.
			Fp64f()
			{
				// nothing
			}
			
			//! @brief			Constructor taking a int32_t.
			//! @details		Uses initialiser lists. Make sure i is cast
			//!					to 64-bit before shifting, overwise truncation
			//!					will occur.
			Fp64f(int32_t i) : rawVal((int64_t)i << p)
			{
				// nothing
			}
			
			Fp64f(int64_t i) : rawVal(i << p)
			{
				// nothing
			}
			
			Fp64f(float f) : rawVal(FloatToFix64<p>(f))
			{
				// nothing
			}
			Fp64f(double f) : rawVal(FloatToFix64<p>((double)f))
			{
				// nothing
			}
			
			//! @}
			
			
			//! @defgroup Compound Assignment Operators
			//! @{
			
			//! @brief		Override for "+=".
			//! @details	Fixed-point addition and subtractional are done as usual.
			Fp64f& operator += (Fp64f r)
			{
				rawVal += r.rawVal;
				return *this;
			}
			
			//! @brief		Override for "-=".
			//! @details	Fixed-point addition and subtractional are done as usual.
			Fp64f& operator -= (Fp64f r)
			{
				rawVal -= r.rawVal;
				return *this;
			}
			
			//! @brief		Override for "*=".
			//! @details	Used the FixMul() method.
			Fp64f& operator *= (Fp64f r)
			{ 
				rawVal = FixMulF<p>(rawVal, r.rawVal);
				return *this;
			}
			
			//! @brief		Override for "/=".
			//! @details	Used the FixDiv() method.
			Fp64f& operator /= (Fp64f r)
			{ 
				rawVal = FixDiv<p>(rawVal, r.rawVal);
				return *this;
			}
			
			//! @brief		Override for "%=".
			Fp64f& operator %= (Fp64f r)
			{ 
				rawVal = rawVal % r.rawVal;
				return *this;
			}
			
			//! @}
			
			//! @defgroup Arithmetic Operators
			//! @{
			
			//! @brief		Override for '+'. Uses compound assignment operator.
			Fp64f operator + (Fp64f r)
			{
				Fp64f temp = *this;
				temp += r;
				return temp;
			}
			
			//! @brief		Override for '-'. Uses compound assignment operator.
			Fp64f operator - (Fp64f r)
			{
				Fp64f temp = *this;
				temp -= r;
				return temp;
			}
			
			//! @brief		Override for '*'. Uses compound assignment operator.
			Fp64f operator * (Fp64f r)
			{
				Fp64f temp = *this;
				temp *= r;
				return temp;
			}
			
			//! @brief		Override for '/'. Uses compound assignment operator.
			Fp64f operator / (Fp64f r)
			{
				Fp64f temp = *this;
				temp /= r;
				return temp;
			}
			
			//! @brief		Override for '%'. Uses compound assignment operator.
			const Fp64f operator % (Fp64f r) 
			{
				Fp64f temp = *this;
				temp %= r;
				return temp;
			}
			
			//! @}
			
			//! @defgroup Binary Operators
			//! @{
			
			bool operator == (Fp64f r) const
			{
				return rawVal == r.rawVal;
			}
			
			bool operator != (Fp64f r) const
			{
				return !(*this == r);
			}
			
			bool operator <  (Fp64f r) const
			{
				return rawVal < r.rawVal;
			}
			
			bool operator >  (Fp64f r) const
			{
				return rawVal > r.rawVal;
			}
			
			bool operator <= (Fp64f r) const
			{
				return rawVal <= r.rawVal;
			}
			
			bool operator >= (Fp64f r) const
			{
				return rawVal >= r.rawVal;
			}
			
			
			//! @}
		private:
			
		
	};


} // namespace Fp

#endif // #ifndef FP64F_H

// EOF