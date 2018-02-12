///
/// @file 				FpS.hpp
/// @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
/// @edited 			n/a
/// @created			2013-07-22
/// @last-modified		2018-01-09
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

// System includes
#include <stdint.h>
#include <type_traits>

namespace mn {
namespace MFixedPoint {

/// \brief 		A class which represents a "slow" fixed-point number, where each instance supports an arbitrary number of fractional bits,
///				and arithmetic is supported between these instances.
/// \tparam		BaseType		The underlying data type which will be store the raw fixed point data. It is recommended that
///								this should be a signed integer type (e.g. int32_t).
/// \tparam		OverflowType	The type that the basetype will be cast to before doing fixed point operations
///								that have a possibility of intermediate overflowing (e.g. multiplication, division).
///								It is recommended that this should be twice the bit size of the BaseType 
///								(e.g. if BaseType = int32_t, OverflowType = int64_t).
template <class BaseType, class OverflowType>
class FpS {
	
	public:
	
	//===============================================================================================//
	//================================== CONSTRUCTORS/DESTRUCTORS ===================================//
	//===============================================================================================//
	
	/// \brief		Create a fixed-point value from a integer and a num. of fractional bits.
	FpS(int32_t integer, uint8_t numFracBits)	{
		static_assert(std::is_integral<BaseType>::value, "Integral BaseType required for FpS class.");
		rawVal_ = integer << numFracBits;
		numFracBits_ = numFracBits;
	}
	
	/// \brief		Create a fixed-point value from a double and a num. of fractional bits.
	FpS(double dbl, uint8_t numFracBits) {
		static_assert(std::is_integral<BaseType>::value, "Integral BaseType required for FpS class.");
		rawVal_ = (BaseType)(dbl * ((BaseType)1 << numFracBits));
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

	//===============================================================================================//
	//================================== COMPOUND ARITHMETIC OPERATORS ==============================//
	//===============================================================================================//	
	
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
	/// \details	Result has the same num. frac bits as the lowest num. frac bits of the two inputs.
	FpS& operator -= (FpS r) { 
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_) {
			// Q the same for both numbers
			rawVal_ = rawVal_ - r.rawVal_;
			// No need to change Q, both are the same
		}
		else if(numFracBits_ > r.numFracBits_) {
			// Second number has smaller Q, so result is in that precision
			rawVal_ = (rawVal_ >> (numFracBits_ - r.numFracBits_)) - r.rawVal_; 
			// Change Q
			numFracBits_ = r.numFracBits_;
		} else { // numFracBits_ < r.numFracBits_		
			// First number has smaller Q, so result is in that precision
			rawVal_ = rawVal_ - (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
			// No need to change Q
		}
		return *this;
	}
	
	/// \brief		Overlaod for '*=' operator.
	/// \details	Uses intermediatary casting to OverflowType to prevent overflows.
	FpS& operator *= (FpS r) {

		// Optimised for when numFracBits_ is the same for both
	
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_) {
			// Q the same for both numbers, shift right by Q
			rawVal_ = (BaseType)(((OverflowType)rawVal_ * (OverflowType)r.rawVal_) >> numFracBits_);
		
			// No need to change Q, both are the same
		
		}
		else if(numFracBits_ > r.numFracBits_) {
			// Second number has smaller Q, so result is in that precision
			rawVal_ = (BaseType)((((OverflowType)rawVal_ >> (numFracBits_ - r.numFracBits_)) * (OverflowType)r.rawVal_) >> r.numFracBits_);  
		
			// Change Q
			numFracBits_ = r.numFracBits_;
		} else { // numFracBits_ < r.numFracBits_	
			// First number has smaller Q, so result is in that precision
			rawVal_ = (BaseType)(((OverflowType)rawVal_ * ((OverflowType)r.rawVal_ >> (r.numFracBits_ - numFracBits_))) >> numFracBits_); 
			// No need to change Q
		}
		return *this;
	}
	
	/// \brief		Overlaod for '/=' operator.
	/// \details	Uses intermediatary casting to OverflowType to prevent overflows.
	FpS& operator /= (FpS r) { 

		// Optimised for when numFracBits_ is the same for both 
	
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_) {
			// Q the same for both numbers, shift right by Q 
		
			rawVal_ = (BaseType)((((OverflowType)rawVal_ << numFracBits_) / (OverflowType)r.rawVal_)); 
		
			// No need to change Q, both are the same
		} else if(numFracBits_ > r.numFracBits_) {
			// Second number has smaller Q, so result is in that precision
			rawVal_ = (BaseType)(((((OverflowType)rawVal_ >> (numFracBits_ - r.numFracBits_)) << r.numFracBits_) / (OverflowType)r.rawVal_));  
		
			// Change Q 
		
			numFracBits_ = r.numFracBits_;
		} else { // numFracBits_ < r.numFracBits_		
			// First number has smaller Q, so result is in that precision
			rawVal_ = (BaseType)(((OverflowType)rawVal_ << numFracBits_) / ((OverflowType)r.rawVal_ >> (r.numFracBits_ - numFracBits_))); 
			// No need to change Q
		}
		return *this;
	}
	
	/// \brief		Overload for '%=' operator.
	FpS& operator %= (FpS r) {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_) {
			// Q the same for both numbers
			rawVal_ = rawVal_ % r.rawVal_;
			// No need to change Q, both are the same
		} else if(numFracBits_ > r.numFracBits_) {
			// Second number has smaller Q, so result is in that precision
			rawVal_ = (rawVal_ >> (numFracBits_ - r.numFracBits_)) % r.rawVal_; 
			// Change Q
			numFracBits_ = r.numFracBits_;
		} else { // numFracBits_ < r.numFracBits_		
			// First number has smaller Q, so result is in that precision
			rawVal_ = rawVal_ % (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
			// No need to change Q
		}
		return *this;
	}
	
	//===============================================================================================//
	//==================================== SIMPLE ARITHMETIC OPERATORS ==============================//
	//===============================================================================================//	
	
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
	
	//===============================================================================================//
	//====================================== COMPARISON OVERLOADS ===================================//
	//===============================================================================================//
	
	/// \brief		Overload for the '==' operator.
	bool operator == (FpS r) const {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_) {
			// Q the same for both numbers
			return rawVal_ == r.rawVal_;
		} else if(numFracBits_ > r.numFracBits_) {
			// Second number has smaller Q, so result is in that precision
			return (rawVal_ >> (numFracBits_ - r.numFracBits_)) == r.rawVal_; 
		} else { // numFracBits_ < r.numFracBits_		
			// First number has smaller Q, so result is in that precision
			return rawVal_ == (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
		}
	}
	
	/// \brief		Overload for the '!=' operator.
	bool operator != (FpS r) const {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_) {
			// Q the same for both numbers
			return rawVal_ != r.rawVal_;
		} else if(numFracBits_ > r.numFracBits_) {
			// Second number has smaller Q, so result is in that precision
			return (rawVal_ >> (numFracBits_ - r.numFracBits_)) != r.rawVal_; 
		} else { // numFracBits_ < r.numFracBits_		
			// First number has smaller Q, so result is in that precision
			return rawVal_ != (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
		}
	}
	
	/// \brief		Overload for the '<' operator.
	bool operator < (FpS r) const {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_) {
			// Q the same for both numbers
			return rawVal_ < r.rawVal_;
		} else if(numFracBits_ > r.numFracBits_) {
			// Second number has smaller Q, so result is in that precision
			return (rawVal_ >> (numFracBits_ - r.numFracBits_)) < r.rawVal_; 
		} else { // numFracBits_ < r.numFracBits_		
			// First number has smaller Q, so result is in that precision
			return rawVal_ < (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
		}
	}

	/// \brief		Overload for the '>' operator.
	bool operator > (FpS r) const {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_) {
			// Q the same for both numbers
			return rawVal_ > r.rawVal_;
		} else if(numFracBits_ > r.numFracBits_) {
			// Second number has smaller Q, so result is in that precision
			return (rawVal_ >> (numFracBits_ - r.numFracBits_)) > r.rawVal_; 
		} else { // numFracBits_ < r.numFracBits_		
			// First number has smaller Q, so result is in that precision
			return rawVal_ > (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
		}
	}
	
	/// \brief		Overload for the '<=' operator.
	bool operator <= (FpS r) const {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_) {
			// Q the same for both numbers
			return rawVal_ <= r.rawVal_;
		} else if(numFracBits_ > r.numFracBits_) {
			// Second number has smaller Q, so result is in that precision
			return (rawVal_ >> (numFracBits_ - r.numFracBits_)) <= r.rawVal_; 
		} else { // numFracBits_ < r.numFracBits_
			// First number has smaller Q, so result is in that precision
			return rawVal_ <= (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
		}
	}
	
	/// \brief		Overload for the '>=' operator.
	bool operator >= (FpS r) const {
		// Optimised for when numFracBits_ is the same for both
		// operators (first if statement).
		if(numFracBits_ == r.numFracBits_) {
			// Q the same for both numbers
			return rawVal_ >= r.rawVal_;
		} else if(numFracBits_ > r.numFracBits_) {
			// Second number has smaller Q, so result is in that precision
			return (rawVal_ >> (numFracBits_ - r.numFracBits_)) >= r.rawVal_; 
		} else { // numFracBits_ < r.numFracBits_		
			// First number has smaller Q, so result is in that precision
			return rawVal_ >= (r.rawVal_ >> (r.numFracBits_ - numFracBits_)); 
		}
	}

	//===============================================================================================//
	//======================================= CONVERSION METHODS ====================================//
	//===============================================================================================//
	
	/// \brief		Converts the fixed-point number into an integer.
	/// \details	Always rounds to negative infinity (66.3 becomes 66, -66.3 becomes -67).
	/// \tparam		IntType		The return integer type.
	template <class IntType>
	IntType ToInt() const {
		// Right-shift to get rid of all the decimal bits
		// This rounds towards negative infinity
		return (IntType)(rawVal_ >> numFracBits_);
	}

	/// \brief		Converts the fixed-point number to a float.
	float ToFloat() const {
		return (float)rawVal_ / (float)((BaseType)1 << numFracBits_);
	}

	/// \brief		Converts the fixed-point number to a double.
	double ToDouble() const {
		return (double)rawVal_ / (double)((BaseType)1 << numFracBits_);
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

    //===============================================================================================//
    //====================================== STRING/STREAM RELATED ==================================//
    //===============================================================================================//

	/// \brief		Converts the fixed-point number into a string representation, using a fixed-point->double->string
	/// 				conversion process.
	std::string ToString() const {
		return std::to_string(ToDouble());
	}

    /// \brief      Overload so we can print to a ostream (e.g. std::cout).
    friend std::ostream&operator<<(std::ostream& stream, FpS obj) {
        stream << obj.ToDouble();
        return stream;
    }

	private:

	/// \brief		The fixed-point number is stored in this basic data type.
	BaseType rawVal_;			
	
	/// \brief		This stores the number of fractional bits (specified in the
	///				constructor).
	uint8_t numFracBits_;
	
}; // class FpS

//===============================================================================================//
//========================================= SPECIALIZATIONS =====================================//
//===============================================================================================//

using FpS8 = FpS<int8_t, int16_t>;
using FpS16 = FpS<int16_t, int32_t>;
using FpS32 = FpS<int32_t, int64_t>;
using FpS64 = FpS<int64_t, int64_t>; // Not protected from overflow!

} // namespace MFixedPoint
} // namespace mn

#endif // #ifndef MN_MFIXEDPOINT_FPS_H

// EOF
