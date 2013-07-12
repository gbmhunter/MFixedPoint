//!
//! @file 		Fp64.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/05/09
//! @brief 		Fixed-point arithmetic for 64-bit numbers. Be careful of overflow!
//! @details
//!		<b>Last Modified:			</b> 2013/05/09					\n
//!		<b>Version:					</b> (see Fp.hpp)				\n
//!		<b>Company:					</b> CladLabs					\n
//!		<b>Project:					</b> CladLabs Free Code Libs	\n
//!		<b>Language:				</b> C							\n
//!		<b>Compiler:				</b> GCC						\n
//! 	<b>uC Model:				</b> PSoC5						\n
//!		<b>Computer Architecture:	</b> ARM						\n
//! 	<b>Operating System:		</b> FreeRTOS v7.2.0			\n
//!		<b>Documentation Format:	</b> Doxygen					\n
//!		<b>License:					</b> (see below)				\n
//!
//! 64-bit fixed-point numbers do not have the same multiplication/division overflow protection that 32-bit
//! ones do (Fp.h). This is because a 128-bit intermediatry would be needed, which is
//! largely unsupported on embedded platforms.


//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#ifndef FP64_H
#define FP64_H

#include <stdint.h>

namespace Fp
{

	//! @brief		Perform a fixed point multiplication without a 128-bit intermediate result.
	//!	@warning	This is fast but beware of intermediatry overflow!
	template <int p> 
	inline int64_t FixMulF(int64_t a, int64_t b)
	{
		// Rule with fixed-point multiplication, you have
		// to right-shift result by the precision.
		return (a * b) >> p;
	}
	
	//! @brief		Perform a fixed point division without a 128-bit intermediate result.
	//! @details	No loss of precision since shift is done before division.
	//!	@warning	This is fast but beware of intermediatry overflow!
	template <int p> 
	inline int64_t FixDiv(int64_t a, int64_t b)
	{
		// Rule with fixed-point division, have to left-shift numerator
		// before dividing by denominator
		return (int32_t)(((a) << p) / b);
	}
	
	//! @brief		Conversion from fixed-point to float
	//! @details	Good for debugging fixed-point arithmetic
	//! @warning 	Slow!
	//! @public
	template <int p>
	float Fix2Float(int64_t f)
	{
		return (float)f / (1 << p);
	}

	//! @brief		Converts from float to fixed-point
	//! @details	Good for inputting values into fixed-point arithmetic
	//! @warning	Slow!
	template <int p>
	int64_t Float2Fix(float f)
	{
		return (int64_t)(f * (1 << p));
	}

	//! @brief		64-bit fixed-point library.
	//! @details	p may vary from 0-64
	template<uint8_t p> class Fp64
	{
		public:
			//! @brief		The raw fixed-point value, stored as a int64.
			int64_t rawVal;
			
			//! @defgroup Constructors
			//! @{
			
			//! @brief			Default constructor.
			Fp64()
			{
				// nothing
			}
			
			//! @brief			Constructor taking a int32_t.
			//! @details		Uses initialiser lists. Make sure i is cast
			//!					to 64-bit before shifting, overwise truncation
			//!					will occur.
			Fp64(int32_t i) : rawVal((int64_t)i << p)
			{
				// nothing
			}
			
			//! @}
			
			
			//! @defgroup Compound Assignment Operators
			//! @{
			
			//! @brief		Override for "+=".
			//! @details	Fixed-point addition and subtractional are done as usual.
			Fp64& operator += (Fp64 r)
			{
				rawVal += r.rawVal;
				return *this;
			}
			
			//! @brief		Override for "-=".
			//! @details	Fixed-point addition and subtractional are done as usual.
			Fp64& operator -= (Fp64 r)
			{
				rawVal -= r.rawVal;
				return *this;
			}
			
			//! @brief		Override for "*=".
			//! @details	Used the FixMul() method.
			Fp64& operator *= (Fp64 r)
			{ 
				rawVal = FixMulF<p>(rawVal, r.rawVal);
				return *this;
			}
			
			//! @brief		Override for "/=".
			//! @details	Used the FixDiv() method.
			Fp64& operator /= (Fp64 r)
			{ 
				rawVal = FixDiv<p>(rawVal, r.rawVal);
				return *this;
			}
			
			//! @}
			
			//! @defgroup Binary Arithmetic Operators
			//! @{
			
			//! @brief		Override for '+'. Uses compound assignment operator.
			Fp64 operator + (Fp64 r)
			{
				Fp64 temp = *this;
				temp += r;
				return temp;
			}
			
			//! @brief		Override for '-'. Uses compound assignment operator.
			Fp64 operator - (Fp64 r)
			{
				Fp64 temp = *this;
				temp -= r;
				return temp;
			}
			
			//! @brief		Override for '*'. Uses compound assignment operator.
			Fp64 operator * (Fp64 r)
			{
				Fp64 temp = *this;
				temp *= r;
				return temp;
			}
			
			//! @brief		Override for '/'. Uses compound assignment operator.
			Fp64 operator / (Fp64 r)
			{
				Fp64 temp = *this;
				temp /= r;
				return temp;
			}
			
			//! @brief		Override for '%'.
			const Fp64 operator % (Fp64 r) 
			{
				Fp64 result;
				result.rawVal = rawVal % r.rawVal;
				return result;
			}
			
			//! @}
		private:
			
		
	};


} // namespace Fp

#endif // #ifndef FP64_H

// EOF