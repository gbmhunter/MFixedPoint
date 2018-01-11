///
/// \file 				FpF.hpp
/// \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja), Markus Trenkwalder
/// \edited 			n/a
/// \created			2012-10-23
/// \last-modified		2018-01-08
/// \brief 				Fast 32-bit fixed point library.
/// \details
///		See README.rst in root dir for more info.

//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#ifndef MN_MFIXEDPOINT_FpF_H
#define MN_MFIXEDPOINT_FpF_H

// System includes
#include <stdint.h>

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
/// \note 		Slower than FpF::FixMulF()
template <class BaseType, class OverflowType, uint8_t numFracBits>
inline BaseType FpFMultiply(int32_t a, int32_t b) {	
	return (BaseType)(((OverflowType)a * b) >> numFracBits);
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
	x = FpFMultiply<(32-q)>(x,((2<<(32-q)) - FpFMultiply<q>(a,x)));
	x = FpFMultiply<(32-q)>(x,((2<<(32-q)) - FpFMultiply<q>(a,x)));

	if (sign)
		return -x;
	else
		return x;
}

/// \brief		Converts from float to a raw 32-bit fixed-point number.
/// \details	Do not write "myFpNum = FloatToRawFix32()"! This function outputs a raw
///				number, so you would have to use the syntax "myFpNum.rawVal_ = FloatToRawFix32()".
/// \warning	Slow!
template <uint8_t q>
int32_t FloatToRawFix32(float f) {
	return (int32_t)(f * (1 << q));
}

/// \brief		Converts from double to a raw 32-bit fixed-point number.
/// \details	Do not write "myFpNum = DoubleToRawFix32()"! This function outputs a raw
///				number, so you would have to use the syntax "myFpNum.rawVal_ = DoubleToRawFix32()".
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
template <class BaseType, class OverflowType, uint8_t numFracBits>
class FpF {
	
	public:

	//===============================================================================================//
	//================================== CONSTRUCTORS/DESTRUCTORS ===================================//
	//===============================================================================================//		
	
	FpF()
	{
		#if(fpConfig_PRINT_DEBUG_GENERAL == 1)
			//Port::DebugPrint("FP: New fixed-point object created.");
		#endif
	}

	//===============================================================================================//
	//========================================= GETTERS/SETTERS =====================================//
	//===============================================================================================//
	
	/// \brief		Get the raw value (memory representation) of this fixed-point number,
	BaseType GetRawVal() const {
		return rawVal_;
	}
	
	FpF(int8_t i) :
		rawVal_((int32_t)i << numFracBits)	{}
	
	FpF(int16_t i) :
		rawVal_((int32_t)i << numFracBits)	{}
	
	FpF(int32_t i) :
		rawVal_(i << numFracBits) { }
	
	/// \brief		Constructor that accepts a float.
	FpF(float f) :
		rawVal_((BaseType)(f * (float)(1 << numFracBits))) {}
	
	
	FpF(double f) :
		rawVal_((BaseType)(f * (double)(1 << numFracBits))) {}
	
	// Compound Arithmetic Overloads
	
	FpF& operator += (FpF r) {
		rawVal_ += r.rawVal_;
		return *this;
	}
	
	FpF& operator -= (FpF r) {
		rawVal_ -= r.rawVal_;
		return *this;
	}
	
	/// \brief		Overlaod for '*=' operator.
	/// \details	Uses intermediatary casting to int64_t to prevent overflows.
	FpF& operator *= (FpF r) {				
		rawVal_ = FpFMultiply<BaseType, OverflowType, numFracBits>(rawVal_, r.rawVal_);
		return *this;
	}
	
	/// \brief		Overlaod for '/=' operator.
	/// \details	Uses intermediatary casting to int64_t to prevent overflows.
	FpF& operator /= (FpF r) {
		rawVal_ = fixdiv<numFracBits>(rawVal_, r.rawVal_);
		return *this;
	}
	
	/// \brief		Overlaod for '%=' operator.
	FpF& operator %= (FpF r) {
		rawVal_ %= r.rawVal_;
		return *this;
	}
	
	
	FpF& operator *= (int32_t r) {
		rawVal_ *= r;
		return *this;
	}
	
	FpF& operator /= (int32_t r) { 
		rawVal_ /= r;
		return *this;
	}
	
	// Simple Arithmetic Overloads
	
	/// \brief		Overload for '-itself' operator.
	FpF operator - () const	{
		FpF x;
		x.rawVal_ = -rawVal_;
		return x;
	}
	
	/// \brief		Overload for '+' operator.
	/// \details	Uses '+=' operator.
	FpF operator + (FpF r) const {
		FpF x = *this;
		x += r;
		return x;
	}
	
	/// \brief		Overload for '-' operator.
	/// \details	Uses '-=' operator.
	FpF operator - (FpF r) const {
		FpF x = *this;
		x -= r;
		return x;
	}
	
	/// \brief		Overload for '*' operator.
	/// \details	Uses '*=' operator.
	template <class BaseTypeR, class OverflowTypeR, uint8_t numFracBitsR>
	FpF<BaseType, OverflowType, numFracBits> operator * (FpF<BaseTypeR, OverflowTypeR, numFracBitsR> r) const {	
		// Following compile-time checks make sure the two fixed-point numbers have the
		// same template parameters
		static_assert(std::is_same<BaseType, BaseTypeR>::value, "FpF arithmetic must be done with fixed-point numbers whose template parameters are the same.");
		static_assert(std::is_same<OverflowType, OverflowTypeR>::value, "FpF arithmetic must be done with fixed-point numbers whose template parameters are the same.");
		static_assert(numFracBits == numFracBitsR, "FpF arithmetic must be done with fixed-point numbers whose template parameters are the same.");
		FpF<BaseType, OverflowType, numFracBits> x = *this;
		x *= r;
		return x;
	}
	
	/// \brief		Overload for '/' operator.
	/// \details	Uses '/=' operator.
	FpF operator / (FpF r) const
	{
		FpF x = *this;
		x /= r;
		return x;
	}
	
	/// \brief		Overload for '%' operator.
	/// \details	Uses '%=' operator.
	FpF operator % (FpF r) const
	{
		FpF x = *this;
		x %= r;
		return x;
	}
	
	// FpF-FpF Binary Operator Overloads
	
	bool operator == (FpF r) const
	{
		return rawVal_ == r.rawVal_;
	}
	
	bool operator != (const FpF &r)
	{
		return !(*this == r);
	}
	
	bool operator <  (const FpF &r)
	{
		return rawVal_ < r.rawVal_;
	}
	
	bool operator >  (const FpF &r)
	{
		return rawVal_ > r.rawVal_;
	}
	
	bool operator <= (FpF r) const
	{
		return rawVal_ <= r.rawVal_;
	}
	
	bool operator >= (FpF r) const
	{
		return rawVal_ >= r.rawVal_;
	}
	
	/// \defgroup From FpF Conversion Overloads (casts)
	/// \{


	/// \brief		Converts the fixed-point number into an integer.
	/// \details	Always rounds to negative infinity (66.3 becomes 66, -66.3 becomes -67).
	/// \tparam		IntType		The return integer type.
	template <class IntType>
	IntType ToInt() const {
		// Right-shift to get rid of all the decimal bits
		// This rounds towards negative infinity
		return (IntType)(rawVal_ >> numFracBits);
	}

	/// \brief		Converts the fixed-point number to a float.
	float ToFloat() const {
		return (float)rawVal_ / (float)(1 << numFracBits);
	}

	/// \brief		Converts the fixed-point number to a double.
	double ToDouble() const {
		return (double)rawVal_ / (double)(1 << numFracBits);
	}

	/// \brief		Conversion operator from fixed-point to int16_t.
	/// \warning	Possible loss of accuracy from conversion from
	///				int32_t to int16_t.
	operator int16_t() {
		// Right-shift to get rid of all the decimal bits (truncate)
		return (int16_t)(rawVal_ >> numFracBits);
	}
	
	/// \brief		Conversion operator from fixed-point to int32_t.
	operator int32_t() {
		// Right-shift to get rid of all the decimal bits (truncate)
		return (rawVal_ >> numFracBits);
	}
	
	/// \brief		Conversion operator from fixed-point to int64_t.
	operator int64_t() {
		// Right-shift to get rid of all the decimal bits (truncate)
		return (int64_t)(rawVal_ >> numFracBits);
	}
	
	/// \brief		Conversion operator from fixed-point to float.
	operator float() { 
		return (float)rawVal_ / (float)(1 << numFracBits);
	}
	
	/// \brief		Conversion operator from fixed-point to double.
	/// \note		Similar to float conversion.
	operator double() { 
		return (double)rawVal_ / (double)(1 << numFracBits);
	}
	
	/// \}
	
	/// \addgroup Overloads Between FpF And int32_t
	/// \{

	/// \brief		Addition operator overload.
	FpF operator + (int32_t r) const {
		FpF x = *this;
		x += r;
		return x;
	}
	
	FpF operator - (int32_t r) const {
		FpF x = *this;
		x -= r;
		return x;
	}
	
	FpF operator * (int32_t r) const {		
		FpF x = *this;
		x *= r;
		return x;
	}
	
	FpF operator / (int32_t r) const {
		FpF x = *this;
		x /= r;
		return x;
	}
	
	bool operator >  (int32_t r) const {
		return rawVal_ > (r << numFracBits);
	}
	
	bool operator >=  (int32_t r) const {
		return rawVal_ >= (r << numFracBits);
	}
	
	bool operator <  (int32_t r) const {
		return rawVal_ < (r << numFracBits);
	}
	
	bool operator <=  (int32_t r) const	{
		return rawVal_ < (r << numFracBits);
	}
	
	bool operator ==  (int32_t r) const	{
		return rawVal_ == (r << numFracBits);
	}
	
	bool operator !=  (int32_t r) const	{
		return rawVal_ != (r << numFracBits);
	}

	/// \}

	private:

	/// \brief		The fixed-point number is stored in this basic data type.
	BaseType rawVal_;
	
};

template <uint8_t numFracBits>
using FpF8 = FpF<int8_t, int16_t, numFracBits>;

template <uint8_t numFracBits>
using FpF16 = FpF<int16_t, int32_t, numFracBits>;

template <uint8_t numFracBits>
using FpF32 = FpF<int32_t, int64_t, numFracBits>;

template <uint8_t numFracBits>
using FpF64 = FpF<int64_t, int64_t, numFracBits>;

// Specializations for use with plain integers

/// \note 		Assumes integer has the same precision as FpF
// template <uint8_t numFracBits>
// inline FpF<numFracBits> operator + (int32_t a, FpF<numFracBits> b)
// { 
// 	return b + a; 
// }

// /// \note 		Assumes integer has the same precision as FpF
// template <uint8_t numFracBits>
// inline FpF<numFracBits> operator - (int32_t a, FpF<numFracBits> b)
// {
// 	return -b + a;
// }

// /// \note 		Assumes integer has the same precision as FpF
// template <uint8_t numFracBits>
// inline FpF<numFracBits> operator * (int32_t a, FpF<numFracBits> b)
// { return b * a; }

// template <uint8_t numFracBits>
// inline FpF<numFracBits> operator / (int32_t a, FpF<numFracBits> b)
// { 
// 	FpF<numFracBits> r(a); 
// 	r /= b; 
// 	return r;
// }

// math functions
// no default implementation

// template <uint8_t numFracBits>
// inline FpF<numFracBits> sin(FpF<numFracBits> a);

// template <uint8_t numFracBits>
// inline FpF<numFracBits> cos(FpF<numFracBits> a);

// template <uint8_t numFracBits>
// inline FpF<numFracBits> sqrt(FpF<numFracBits> a);

// template <uint8_t numFracBits>
// inline FpF<numFracBits> rsqrt(FpF<numFracBits> a);

// template <uint8_t numFracBits>
// inline FpF<numFracBits> inv(FpF<numFracBits> a);

// template <uint8_t numFracBits>
// inline FpF<numFracBits> abs(FpF<numFracBits> a)
// { 
// 	FpF<numFracBits> r; 
// 	r.rawVal_ = a.rawVal_ > 0 ? a.rawVal_ : -a.rawVal_; 
// 	return r; 
// }

// // Specializations for 16.16 format

// template <>
// inline FpF<16> sin(FpF<16> a)
// {
// 	FpF<16> r;
// 	r.rawVal_ = fixsin16(a.rawVal_);
// 	return r;
// }

// template <>
// inline FpF<16> cos(FpF<16> a)
// {
// 	FpF<16> r;
// 	r.rawVal_ = fixcos16(a.rawVal_);
// 	return r;
// }


// template <>
// inline FpF<16> sqrt(FpF<16> a)
// {
// 	FpF<16> r;
// 	r.rawVal_ = fixsqrt16(a.rawVal_);
// 	return r;
// }

// template <>
// inline FpF<16> rsqrt(FpF<16> a)
// {
// 	FpF<16> r;
// 	r.rawVal_ = fixrsqrt16(a.rawVal_);
// 	return r;
// }

// template <>
// inline FpF<16> inv(FpF<16> a)
// {
// 	FpF<16> r;
// 	r.rawVal_ = fixinv<16>(a.rawVal_);
// 	return r;
// }

// // The multiply accumulate case can be optimized.
// template <uint8_t numFracBits>
// inline FpF<numFracBits> multiply_accumulate(
// 	int32_t count, 
// 	const FpF<numFracBits> *a,
// 	const FpF<numFracBits> *b)
// {
// 	long long result = 0;
// 	for (int32_t i = 0; i < count; ++i)
// 		result += static_cast<long long>(a[i].rawVal_) * b[i].rawVal_;
// 	FpF<numFracBits> r;
// 	r.rawVal_ = static_cast<int32_t>(result >> numFracBits);
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

#endif // #ifndef MN_MFIXEDPOINT_FpF_H

// EOF
