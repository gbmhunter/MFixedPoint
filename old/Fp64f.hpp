//!
//! @file 				Fp64f.h
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2013-05-09
//! @last-modified		2017-12-13
//! @brief 				Fast fixed-point arithmetic for 64-bit numbers. Be careful of overflow!
//! @details
//!		See README.rst in root dir for more info.


//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#ifndef MN_MFIXEDPOINT_FP64F_H
#define MN_MFIXEDPOINT_FP64F_H

#include <stdint.h>

namespace mn {
namespace MFixedPoint {

	//! @brief		Perform a fixed point multiplication without a 128-bit intermediate result.
	//!	@warning	This is fast but beware of intermediary overflow!
	template <uint8_t p> 
	inline int64_t FixMulF(int64_t a, int64_t b)
	{
		// Rule with fixed-point multiplication, you have
		// to right-shift result by the precision.
		return (a * b) >> p;
	}
	
	//! @brief		Perform a fixed point division without a 128-bit intermediate result.
	//! @details	No loss of precision since shift is done before division.
	//!	@warning	This is fast but beware of intermediary overflow!
	template <uint8_t p> 
	inline int64_t FixDiv(int64_t a, int64_t b)
	{
		// Rule with fixed-point division, have to left-shift numerator
		// before dividing by denominator
		return (int64_t)(((a) << p) / b);
	}

	//! @brief		Converts from float to a raw fixed-point number.
	//! @details	Do not write "myFpNum = FloatToRawFix64()"! This function outputs a raw
	//!				number, so you would have to use the syntax "myFpNum.rawVal = FloatToRawFix64()".
	//! @warning	Slow!
	template <uint8_t p>
	int64_t FloatToRawFix64(float f)
	{
		return (int64_t)(f * (1 << p));
	}
	
	//! @brief		Converts from float to a raw fixed-point number.
	//! @details	Do not write "myFpNum = DoubleToRawFix64()"! This function outputs a raw
	//!				number, so you would have to use the syntax "myFpNum.rawVal = DoubleToRawFix64()".
	//! @warning	Slow!
	template <uint8_t p>
	int64_t DoubleToRawFix64(double f)
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
			//!					to 64-bit before shifting, otherwise truncation
			//!					will occur.
			Fp64f(int32_t i) :
				rawVal((int64_t)i << p)
			{
				// nothing
			}
			
			Fp64f(int64_t i) :
				rawVal(i << p)
			{
				// nothing
			}
			
			Fp64f(float f) :
				rawVal(FloatToRawFix64<p>(f))
			{
				// nothing
			}
			Fp64f(double f) :
				rawVal(FloatToRawFix64<p>((double)f))
			{
				// nothing
			}
			
			//! @} Constructors
			
			
			//! @defgroup Compound Assignment Operator Overloads
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
			
			//! @} Compound Assignment Operator Overloads
			
			//! @defgroup Arithmetic Operator Overloads
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
			
			//! @} Arithmetic Operator Overloads
			
			//! @defgroup Explicit Binary Operator Overloads
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
			
			/// @}
			
			/// \defgroup Explicit "From Fp64f" Conversion Overloads (casts)
			/// @{
			
			/// \brief		Conversion operator from fixed-point to float.
			operator float() { 
				return (float)rawVal / (float)(1 << p);
			}
			
			/// \brief		Conversion operator from fixed-point to double.
			/// \note		Similar to float conversion.
			operator double() { 
				return (double)rawVal / (double)(1 << p);
			}
			
			//! @}
			
		private:
			
			// none
	};

	//===============================================================================================//
	//======================================== GRAVEYARD ============================================//
	//===============================================================================================//
	
	/*
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
	double Fix64ToDouble(int64_t f)
	{
		return (double)f / (double)(1 << p);
	}*/

} // namespace MFixedPoint
} // namesapce mn

#endif // #ifndef MN_MFIXEDPOINT_FP64F_H

// EOF
