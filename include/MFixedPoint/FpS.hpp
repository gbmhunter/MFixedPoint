///
/// @file 				FpS.hpp
/// @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
/// @edited 			n/a
/// @created			2018-01-08
/// @last-modified		2017-01-08
/// \brief 				A slower, more powerful fixed point library.
/// \details
///		See README.rst in root dir for more info.

//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#ifndef MN_MFIXEDPOINT_FPS_H
#define MN_MFIXEDPOINT_FPS_H

#include <stdint.h>

// Fixed-point configuration file
#include "Config.hpp"

// Port-specific code
#include "Port.hpp"

namespace mn {
namespace MFixedPoint {

/// \brief 	The template argument p in all of the following functions refers to the 
/// 		fixed point precision (e.g. p = 8 gives 24.8 fixed point functions).
/// 		Contains mathematical operator overloading. Doesn't have modulus (%) overloading.
template <class BaseType>
class FpS {
	
	public:
	
	//===============================================================================================//
	//================================== CONSTRUCTORS/DESTRUCTORS ===================================//
	//===============================================================================================//
	
	/// \brief		Create a fixed-point value from a integer and a num. of fractional bits.
	FpS(int32_t integer, uint8_t numFracBits)	{
		rawVal_ = integer << numFracBits;
		numFracBits_ = numFracBits;
	}
	
	/// \brief		Create a fixed-point value from a double and a num. of fractional bits.
	FpS(double dbl, uint8_t numFracBits) {
		rawVal_ = (BaseType)(dbl * (1 << numFracBits));
		numFracBits_ = numFracBits;
	}

	//===============================================================================================//
	//========================================= GETTERS/SETTERS =====================================//
	//===============================================================================================//
	
	/// \brief		Get the raw value (memory representation) of this fixed-point number,
	BaseType GetRawVal() const {
		return rawVal_;
	}

	/// \brief		Returns the number of fractional bits used in this fixed-point number.
	uint8_t GetNumFracBits() const {
		return numFracBits_;
	}

	// Compound Arithmetic Operators
	
	/// \brief		Overload for '+=' operator.
	/// \details	Result has the same num. frac bits as the lowest num. frac bits of the two inputs.
	FpS& operator += (FpS r) { 
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_) {			
			rawVal_ = rawVal_ + r.rawVal_;
			// No need to change num. frac. bits, both are the same
		} else if(numFracBits_ > r.numFracBits_) {
			// Second number has smaller num. of frac. bits, so result is in that precision
			rawVal_ = (rawVal_ >> (numFracBits_ - r.numFracBits_)) + r.rawVal_; 			
			numFracBits_ = r.numFracBits_;
		} else { // numFracBits_ < r.numFracBits_
			// First number has smaller num. of frac. bits, so result is in that precision
			rawVal_ = rawVal_ + (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
			// No need to change num. frac. bits
		}
		return *this;
	}
	
	/// \brief		Overload for '-=' operator.
	FpS& operator -= (FpS r) { 
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_)
		{
			// Q the same for both numbers
			rawVal_ = rawVal_ - r.rawVal_;
			// No need to change Q, both are the same
		}
		else if(numFracBits_ > r.numFracBits_)
		{
			// Second number has smaller Q, so result is in that precision
			rawVal_ = (rawVal_ >> (numFracBits_ - r.numFracBits_)) - r.rawVal_; 
			// Change Q
			numFracBits_ = r.numFracBits_;
		}
		else // numFracBits_ < r.numFracBits_
		{
			// First number has smaller Q, so result is in that precision
			rawVal_ = rawVal_ - (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
			// No need to change Q
		}
		return *this;
	}
	
	/// \brief		Overlaod for '*=' operator.
	/// \details	Uses intermediatary casting to int64_t to prevent overflows.
	FpS& operator *= (FpS r) {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_)
		{
			// Q the same for both numbers, shift right by Q
			rawVal_ = (int32_t)(((int64_t)rawVal_ * (int64_t)r.rawVal_) >> numFracBits_);
			// No need to change Q, both are the same
		}
		else if(numFracBits_ > r.numFracBits_)
		{
			// Second number has smaller Q, so result is in that precision
			rawVal_ = (int32_t)((((int64_t)rawVal_ >> (numFracBits_ - r.numFracBits_)) * (int64_t)r.rawVal_) >> r.numFracBits_); 
			// Change Q
			numFracBits_ = r.numFracBits_;
		}
		else // numFracBits_ < r.numFracBits_
		{
			// First number has smaller Q, so result is in that precision
			rawVal_ = (int32_t)(((int64_t)rawVal_ * ((int64_t)r.rawVal_ >> (r.numFracBits_ - numFracBits_))) >> numFracBits_); 
			// No need to change Q
		}
		return *this;
	}
	
	/// \brief		Overlaod for '/=' operator.
	/// \details	Uses intermediatary casting to int64_t to prevent overflows.
	FpS& operator /= (FpS r) {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_)
		{
			// Q the same for both numbers, shift right by Q
			rawVal_ = (int32_t)((((int64_t)rawVal_ << numFracBits_) / (int64_t)r.rawVal_));
			// No need to change Q, both are the same
		}
		else if(numFracBits_ > r.numFracBits_)
		{
			// Second number has smaller Q, so result is in that precision
			rawVal_ = (int32_t)(((((int64_t)rawVal_ >> (numFracBits_ - r.numFracBits_)) << r.numFracBits_) / (int64_t)r.rawVal_)); 
			// Change Q
			numFracBits_ = r.numFracBits_;
		}
		else // numFracBits_ < r.numFracBits_
		{
			// First number has smaller Q, so result is in that precision
			rawVal_ = (int32_t)(((int64_t)rawVal_ << numFracBits_) / ((int64_t)r.rawVal_ >> (r.numFracBits_ - numFracBits_))); 
			// No need to change Q
		}
		return *this;
	}
	
	/// \brief		Overlaod for '%=' operator.
	FpS& operator %= (FpS r) {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_)
		{
			// Q the same for both numbers
			rawVal_ = rawVal_ % r.rawVal_;
			// No need to change Q, both are the same
		}
		else if(numFracBits_ > r.numFracBits_)
		{
			// Second number has smaller Q, so result is in that precision
			rawVal_ = (rawVal_ >> (numFracBits_ - r.numFracBits_)) % r.rawVal_; 
			// Change Q
			numFracBits_ = r.numFracBits_;
		}
		else // numFracBits_ < r.numFracBits_
		{
			// First number has smaller Q, so result is in that precision
			rawVal_ = rawVal_ % (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
			// No need to change Q
		}
		return *this;
	}
	
	// Simple Arithmetic Operators
	
	/// \brief		Overload for '+' operator.
	/// \details	Uses '+=' operator.
	FpS operator + (FpS r) const {
		FpS x = *this;
		x += r;
		return x;
	}
	
	/// \brief		Overload for '-' operator.
	/// \details	Uses '-=' operator.
	FpS operator - (FpS r) const {
		FpS x = *this;
		x -= r;
		return x;
	}
	
	/// \brief		Overload for '*' operator.
	/// \details	Uses '*=' operator.
	FpS operator * (FpS r) const {
		FpS x = *this;
		x *= r;
		return x;
	}
	
	/// \brief		Overload for '/' operator.
	/// \details	Uses '/=' operator.
	FpS operator / (FpS r) const {
		FpS x = *this;
		x /= r;
		return x;
	}
	
	/// \brief		Overload for '%' operator.
	/// \details	Uses '%=' operator.
	FpS operator % (FpS r) const {
		FpS x = *this;
		x %= r;
		return x;
	}
	
	// Binary Operator Overloads
	
	/// \brief		Overload for the '==' operator.
	bool operator == (FpS r) const {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_)
		{
			// Q the same for both numbers
			return rawVal_ == r.rawVal_;
		}
		else if(numFracBits_ > r.numFracBits_)
		{
			// Second number has smaller Q, so result is in that precision
			return (rawVal_ >> (numFracBits_ - r.numFracBits_)) == r.rawVal_; 
		}
		else // numFracBits_ < r.numFracBits_
		{
			// First number has smaller Q, so result is in that precision
			return rawVal_ == (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
		}
	}
	
	/// \brief		Overload for the '!=' operator.
	bool operator != (FpS r) const {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_)
		{
			// Q the same for both numbers
			return rawVal_ != r.rawVal_;
		}
		else if(numFracBits_ > r.numFracBits_)
		{
			// Second number has smaller Q, so result is in that precision
			return (rawVal_ >> (numFracBits_ - r.numFracBits_)) != r.rawVal_; 
		}
		else // numFracBits_ < r.numFracBits_
		{
			// First number has smaller Q, so result is in that precision
			return rawVal_ != (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
		}
	}
	
	/// \brief		Overload for the '<' operator.
	bool operator < (FpS r) const {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_)
		{
			// Q the same for both numbers
			return rawVal_ < r.rawVal_;
		}
		else if(numFracBits_ > r.numFracBits_)
		{
			// Second number has smaller Q, so result is in that precision
			return (rawVal_ >> (numFracBits_ - r.numFracBits_)) < r.rawVal_; 
		}
		else // numFracBits_ < r.numFracBits_
		{
			// First number has smaller Q, so result is in that precision
			return rawVal_ < (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
		}
	}

	/// \brief		Overload for the '>' operator.
	bool operator > (FpS r) const {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_)
		{
			// Q the same for both numbers
			return rawVal_ > r.rawVal_;
		}
		else if(numFracBits_ > r.numFracBits_)
		{
			// Second number has smaller Q, so result is in that precision
			return (rawVal_ >> (numFracBits_ - r.numFracBits_)) > r.rawVal_; 
		}
		else // numFracBits_ < r.numFracBits_
		{
			// First number has smaller Q, so result is in that precision
			return rawVal_ > (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
		}
	}
	
	/// \brief		Overload for the '<=' operator.
	bool operator <= (FpS r) const {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_)
		{
			// Q the same for both numbers
			return rawVal_ <= r.rawVal_;
		}
		else if(numFracBits_ > r.numFracBits_)
		{
			// Second number has smaller Q, so result is in that precision
			return (rawVal_ >> (numFracBits_ - r.numFracBits_)) <= r.rawVal_; 
		}
		else // numFracBits_ < r.numFracBits_
		{
			// First number has smaller Q, so result is in that precision
			return rawVal_ <= (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
		}
	}
	
	/// \brief		Overload for the '>=' operator.
	bool operator >= (FpS r) const {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_)
		{
			// Q the same for both numbers
			return rawVal_ >= r.rawVal_;
		}
		else if(numFracBits_ > r.numFracBits_)
		{
			// Second number has smaller Q, so result is in that precision
			return (rawVal_ >> (numFracBits_ - r.numFracBits_)) >= r.rawVal_; 
		}
		else // numFracBits_ < r.numFracBits_
		{
			// First number has smaller Q, so result is in that precision
			return rawVal_ >= (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
		}
	}

	//===============================================================================================//
	//======================================= CONVERSION METHODS ====================================//
	//===============================================================================================//
	
	/// \brief		Converts the fixed-point number into an integer.
	/// \details	Always rounds to negative infinity (66.3 becomes 66, -66.3 becomes -67).
	template <class IntType>
	IntType ToInt() const {
		// Right-shift to get rid of all the decimal bits
		// This rounds towards negative infinity
		return (IntType)(rawVal_ >> numFracBits_);
	}

	float ToFloat() const {
		return (float)rawVal_ / (float)(1 << numFracBits_);
	}

	double ToDouble() const {
		return (double)rawVal_ / (double)(1 << numFracBits_);
	}

	// Explicit Conversion Operator Overloads (casts)
	
	/// \brief		Conversion operator from fixed-point to int32_t.
	operator int32_t() const {
		return ToInt<int32_t>();
	}
	
	/// \brief		Conversion operator from fixed-point to int64_t.
	operator int64_t() const {		
		return ToInt<int64_t>();
	}
	
	/// \brief		Conversion operator from fixed-point to float.
	/// \note		Similar to double conversion.
	operator float() const { 
		return ToFloat();
	}
	
	/// \brief		Conversion operator from fixed-point to double.
	/// \note		Similar to float conversion.
	operator double() const { 
		return ToDouble();
	}

	private:

	/// \brief		The fixed-point number is stored in this basic data type.
	BaseType rawVal_;			
	
	/// \brief		This stores the number of fractional bits.
	uint8_t numFracBits_;
	
};

} // namespace MFixedPoint
} // namespace mn

#endif // #ifndef MN_MFIXEDPOINT_FPS_H

// EOF
