//!
//! @file 		Fp32Q.hpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/07/22
//! @brief 		32-bit fixed point library that also stores Q.
//! @details
//!				See README.rst in root dir for more info.

//===============================================================================================//
//====================================== HEADER GUARD ===========================================//
//===============================================================================================//

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

#ifndef FP32Q_H
#define FP32Q_H

#include <stdint.h>

// Fixed-point configuration file
#include "FixedPoint-Config.hpp"

// Port-specific code
#include "FixedPoint-Port.hpp"

namespace Fp
{

	//! The template argument p in all of the following functions refers to the 
	//! fixed point precision (e.g. p = 8 gives 24.8 fixed point functions).
	//! Contains mathematical operator overloading. Doesn't have modulus (%) overloading
	class Fp32Q {
		
		public:
		
		//! @brief		The fixed-point number is stored in this basic data type.
		int32_t rawVal;			
		
		//! @brief		This stores the number of fractional bits.
		uint8_t q;
		
		Fp32Q()
		{
			#if(fpConfig_PRINT_DEBUG_GENERAL == 1)
				//Port::DebugPrint("FP: New fixed-point object created.");
			#endif
		}
		
		Fp32Q(int32_t i, uint8_t qin)
		{
			rawVal = i << qin;
			q = qin;
		}
		
		Fp32Q(double dbl, uint8_t qin)
		{
			rawVal = (int32_t)(dbl * (1 << qin));
			q = qin;
		}
		
		Fp32Q& operator += (Fp32Q r)
		{ 
			if(q > r.q)
			{
				// First number smaller
				rawVal = (rawVal > (q - r.q)) + Fp32Qr.rawVal; 
				q = q - r.q;
			}
			return *this;
		}
		
		//! @brief		Conversion operator from fixed-point to double.
		operator double()
		{ 
			return (double)rawVal / (double)(1 << q);
		}
		
		/*
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
		*/
	};

} // namespace Fp32Q

#endif // #ifndef FP32Q_H

// EOF
