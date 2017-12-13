//!
//! @file 				Fp64s.hpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-07-22
//! @last-modified		2017-12-13
//! @brief 				A slower, more powerful 64-bit fixed point library (than Fp64f).
//! @details
//!		See README.rst in root dir for more info.

//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#ifndef MN_MFIXEDPOINT_FP64S_H
#define MN_MFIXEDPOINT_FP64S_H

// System includes
#include <stdint.h>

// User includes
#include "Config.hpp" // Fixed-point configuration file
#include "Port.hpp" // Port-specific code

namespace mn {
namespace MFixedPoint {

/// \brief		Fixed-point, 64-bit, slow (slower than Fp64f), but more powerful, library
class Fp64s {
	
	public:
	
	//! @brief		The fixed-point number is stored in this basic data type.
	int64_t rawVal;			
	
	//! @brief		This stores the number of fractional bits.
	uint8_t q;
	
	Fp64s()
	{
		#if(fpConfig_PRINT_DEBUG_GENERAL == 1)
			//Port::DebugPrint("FP: New fixed-point object created.");
		#endif
	}
	
	Fp64s(int32_t i, uint8_t qin)
	{
		// Cast to 64-bit before shifting so truncation does not occur
		rawVal = (int64_t)i << qin;
		q = qin;
	}
	
	Fp64s(int64_t i, uint8_t qin)
	{
		rawVal = i << qin;
		q = qin;
	}
	
	Fp64s(double dbl, uint8_t qin)
	{
		rawVal = (int32_t)(dbl * (1 << qin));
		q = qin;
	}
	
	// Compound Arithmetic Operators
	
	//! @brief		Overload for '+=' operator.
	Fp64s& operator += (Fp64s r)
	{ 
		// Optimised for when q is the same for both
		// operators (first if statement).
		if(q == r.q)
		{
			// First number smaller
			rawVal = rawVal + r.rawVal;
			// No need to change Q, both are the same
		}
		else if(q > r.q)
		{
			// Second number has smaller Q, so result is in that precision
			rawVal = (rawVal >> (q - r.q)) + r.rawVal; 
			// Change Q
			q = r.q;
		}
		else // q < r.q
		{
			// First number has smaller Q, so result is in that precision
			rawVal = rawVal + (r.rawVal >> (r.q - q)); 
			// No need to change Q
		}
		return *this;
	}
	
	//! @brief		Overload for '-=' operator.
	Fp64s& operator -= (Fp64s r)
	{ 
		// Optimised for when q is the same for both
		// operators (first if statement).
		if(q == r.q)
		{
			// Q the same for both numbers
			rawVal = rawVal - r.rawVal;
			// No need to change Q, both are the same
		}
		else if(q > r.q)
		{
			// Second number has smaller Q, so result is in that precision
			rawVal = (rawVal >> (q - r.q)) - r.rawVal; 
			// Change Q
			q = r.q;
		}
		else // q < r.q
		{
			// First number has smaller Q, so result is in that precision
			rawVal = rawVal - (r.rawVal >> (r.q - q)); 
			// No need to change Q
		}
		return *this;
	}
	
	//! @brief		Overlaod for '*=' operator.
	//! @details	Uses intermediatary casting to int64_t to prevent overflows.
	Fp64s& operator *= (Fp64s r)
	{
		// Optimised for when q is the same for both
		// operators (first if statement).
		if(q == r.q)
		{
			// Q the same for both numbers, shift right by Q
			rawVal = (int32_t)(((int64_t)rawVal * (int64_t)r.rawVal) >> q);
			// No need to change Q, both are the same
		}
		else if(q > r.q)
		{
			// Second number has smaller Q, so result is in that precision
			rawVal = (int32_t)((((int64_t)rawVal >> (q - r.q)) * (int64_t)r.rawVal) >> r.q); 
			// Change Q
			q = r.q;
		}
		else // q < r.q
		{
			// First number has smaller Q, so result is in that precision
			rawVal = (int32_t)(((int64_t)rawVal * ((int64_t)r.rawVal >> (r.q - q))) >> q); 
			// No need to change Q
		}
		return *this;
	}
	
	//! @brief		Overlaod for '/=' operator.
	//! @details	Uses intermediatary casting to int64_t to prevent overflows.
	Fp64s& operator /= (Fp64s r)
	{
		// Optimised for when q is the same for both
		// operators (first if statement).
		if(q == r.q)
		{
			// Q the same for both numbers, shift right by Q
			rawVal = (int32_t)((((int64_t)rawVal << q) / (int64_t)r.rawVal));
			// No need to change Q, both are the same
		}
		else if(q > r.q)
		{
			// Second number has smaller Q, so result is in that precision
			rawVal = (int32_t)(((((int64_t)rawVal >> (q - r.q)) << r.q) / (int64_t)r.rawVal)); 
			// Change Q
			q = r.q;
		}
		else // q < r.q
		{
			// First number has smaller Q, so result is in that precision
			rawVal = (int32_t)(((int64_t)rawVal << q) / ((int64_t)r.rawVal >> (r.q - q))); 
			// No need to change Q
		}
		return *this;
	}
	
	//! @brief		Overlaod for '%=' operator.
	Fp64s& operator %= (Fp64s r)
	{
		// Optimised for when q is the same for both
		// operators (first if statement).
		if(q == r.q)
		{
			// Q the same for both numbers
			rawVal = rawVal % r.rawVal;
			// No need to change Q, both are the same
		}
		else if(q > r.q)
		{
			// Second number has smaller Q, so result is in that precision
			rawVal = (rawVal >> (q - r.q)) % r.rawVal; 
			// Change Q
			q = r.q;
		}
		else // q < r.q
		{
			// First number has smaller Q, so result is in that precision
			rawVal = rawVal % (r.rawVal >> (r.q - q)); 
			// No need to change Q
		}
		return *this;
	}
	
	// Simple Arithmetic Operators
	
	//! @brief		Overload for '+' operator.
	//! @details	Uses '+=' operator.
	Fp64s operator + (Fp64s r) const
	{
		Fp64s x = *this;
		x += r;
		return x;
	}
	
	//! @brief		Overload for '-' operator.
	//! @details	Uses '-=' operator.
	Fp64s operator - (Fp64s r) const
	{
		Fp64s x = *this;
		x -= r;
		return x;
	}
	
	//! @brief		Overload for '*' operator.
	//! @details	Uses '*=' operator.
	Fp64s operator * (Fp64s r) const
	{
		Fp64s x = *this;
		x *= r;
		return x;
	}
	
	//! @brief		Overload for '/' operator.
	//! @details	Uses '/=' operator.
	Fp64s operator / (Fp64s r) const
	{
		Fp64s x = *this;
		x /= r;
		return x;
	}
	
	//! @brief		Overload for '%' operator.
	//! @details	Uses '%=' operator.
	Fp64s operator % (Fp64s r) const
	{
		Fp64s x = *this;
		x %= r;
		return x;
	}
	
	// Binary Operator Overloads
	
	//! @brief		Overload for the '==' operator.
	bool operator == (Fp64s r) const
	{
		// Optimised for when q is the same for both
		// operators (first if statement).
		if(q == r.q)
		{
			// Q the same for both numbers
			return rawVal == r.rawVal;
		}
		else if(q > r.q)
		{
			// Second number has smaller Q, so result is in that precision
			return (rawVal >> (q - r.q)) == r.rawVal; 
		}
		else // q < r.q
		{
			// First number has smaller Q, so result is in that precision
			return rawVal == (r.rawVal >> (r.q - q)); 
		}
	}
	
	//! @brief		Overload for the '!=' operator.
	bool operator != (Fp64s r) const
	{
		// Optimised for when q is the same for both
		// operators (first if statement).
		if(q == r.q)
		{
			// Q the same for both numbers
			return rawVal != r.rawVal;
		}
		else if(q > r.q)
		{
			// Second number has smaller Q, so result is in that precision
			return (rawVal >> (q - r.q)) != r.rawVal; 
		}
		else // q < r.q
		{
			// First number has smaller Q, so result is in that precision
			return rawVal != (r.rawVal >> (r.q - q)); 
		}
	}
	
	//! @brief		Overload for the '<' operator.
	bool operator < (Fp64s r) const
	{
		// Optimised for when q is the same for both
		// operators (first if statement).
		if(q == r.q)
		{
			// Q the same for both numbers
			return rawVal < r.rawVal;
		}
		else if(q > r.q)
		{
			// Second number has smaller Q, so result is in that precision
			return (rawVal >> (q - r.q)) < r.rawVal; 
		}
		else // q < r.q
		{
			// First number has smaller Q, so result is in that precision
			return rawVal < (r.rawVal >> (r.q - q)); 
		}
	}

	//! @brief		Overload for the '>' operator.
	bool operator > (Fp64s r) const
	{
		// Optimised for when q is the same for both
		// operators (first if statement).
		if(q == r.q)
		{
			// Q the same for both numbers
			return rawVal > r.rawVal;
		}
		else if(q > r.q)
		{
			// Second number has smaller Q, so result is in that precision
			return (rawVal >> (q - r.q)) > r.rawVal; 
		}
		else // q < r.q
		{
			// First number has smaller Q, so result is in that precision
			return rawVal > (r.rawVal >> (r.q - q)); 
		}
	}
	
	//! @brief		Overload for the '<=' operator.
	bool operator <= (Fp64s r) const
	{
		// Optimised for when q is the same for both
		// operators (first if statement).
		if(q == r.q)
		{
			// Q the same for both numbers
			return rawVal <= r.rawVal;
		}
		else if(q > r.q)
		{
			// Second number has smaller Q, so result is in that precision
			return (rawVal >> (q - r.q)) <= r.rawVal; 
		}
		else // q < r.q
		{
			// First number has smaller Q, so result is in that precision
			return rawVal <= (r.rawVal >> (r.q - q)); 
		}
	}
	
	//! @brief		Overload for the '>=' operator.
	bool operator >= (Fp64s r) const
	{
		// Optimised for when q is the same for both
		// operators (first if statement).
		if(q == r.q)
		{
			// Q the same for both numbers
			return rawVal >= r.rawVal;
		}
		else if(q > r.q)
		{
			// Second number has smaller Q, so result is in that precision
			return (rawVal >> (q - r.q)) >= r.rawVal; 
		}
		else // q < r.q
		{
			// First number has smaller Q, so result is in that precision
			return rawVal >= (r.rawVal >> (r.q - q)); 
		}
	}
	
	// Conversion Operator Overloads (casts)
	
	//! @brief		Conversion operator from fixed-point to int32_t.
	//! @warning	Possible truncation of number.
	operator int32_t()
	{
		// Right-shift to get rid of all the decimal bits,
		// then convert
		return (int32_t)(rawVal >> q);
	}
	
	//! @brief		Conversion operator from fixed-point to int64_t.
	operator int64_t()
	{
		// Right-shift to get rid of all the decimal bits
		return (rawVal >> q);
	}
	
	//! @brief		Conversion operator from fixed-point to float.
	//! @note		Similar to double conversion.
	operator float()
	{ 
		return (float)rawVal / (float)(1 << q);
	}
	
	//! @brief		Conversion operator from fixed-point to double.
	//! @note		Similar to float conversion.
	operator double()
	{ 
		return (double)rawVal / (double)(1 << q);
	}
	

};

} // namespace MFixedPoint
} // namesapce mn

#endif // #ifndef MN_MFIXEDPOINT_FP64S_H

// EOF
