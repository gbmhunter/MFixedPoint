using f32 = uint32_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i32 = int32_t;

typedef struct { uint16_t v; } float16_t;
typedef struct { uint32_t v; } float32_t;
typedef struct { uint64_t v; } float64_t;
typedef struct { uint64_t v[2]; } float128_t;

union ui16_f16 { uint16_t ui; float16_t f; };
union ui32_f32 { uint32_t ui; float32_t f; };
union ui64_f64 { uint64_t ui; float64_t f; };

#define signF32UI( a ) ((bool) ((uint32_t) (a)>>31))
#define expF32UI( a ) ((int_fast16_t) ((a)>>23) & 0xFF)
#define fracF32UI( a ) ((a) & 0x007FFFFF)
#define packToF32UI( sign, exp, sig ) (((uint32_t) (sign)<<31) + ((uint32_t) (exp)<<23) + (sig))
#define softfloat_isSigNaNF32UI( uiA ) ((((uiA) & 0x7FC00000) == 0x7F800000) && ((uiA) & 0x003FFFFF))
#define defaultNaNF32UI 0xFFC00000
#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & 0x007FFFFF))

struct exp16_sig32 { int_fast16_t exp; uint_fast32_t sig; };

const uint_least8_t softfloat_countLeadingZeros8[256] = {
    8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


enum {
    softfloat_tininess_beforeRounding = 0,
    softfloat_tininess_afterRounding  = 1
};


enum {
    softfloat_round_near_even   = 0,
    softfloat_round_minMag      = 1,
    softfloat_round_min         = 2,
    softfloat_round_max         = 3,
    softfloat_round_near_maxMag = 4,
    softfloat_round_odd         = 5
};



enum {
    softfloat_flag_inexact   =  1,
    softfloat_flag_underflow =  2,
    softfloat_flag_overflow  =  4,
    softfloat_flag_infinite  =  8,
    softfloat_flag_invalid   = 16
};


/// \details    Code from http://www.jhauser.us/arithmetic/SoftFloat.html.
class SoftFloat {

public:

    
    /// \warning    Only works if a and b are of equal sign.
    f32 Add(f32 a, f32 b) {
        int zExp;
        u32 zFrac;
        u32 aFrac = a & 0x007FFFFF;
        u32 bFrac = b & 0x007FFFFF;
        int aExp = (a >> 23) & 0xFF;
        int bExp = (b >> 23) & 0xFF;
        u32 aSign = a >> 31;
        u32 bSign = b >> 31;
        u32 zSign = aSign;
        int expDiff = aExp - bExp;
        aFrac <<= 6;
        bFrac <<= 6;
        // align exponents if needed

        if(expDiff > 0) {
            if(bExp == 0)
                --expDiff;
            else 
                bFrac |= 0x20000000;
            bFrac = shift32RightJamming(bFrac, expDiff);
            zExp = aExp;
        } else if(expDiff < 0) {
            if(aExp == 0)
                ++expDiff;
            else 
                aFrac |= 0x20000000;
            aFrac = shift32RightJamming(aFrac, -expDiff);
            zExp = bExp;
        } else if(expDiff == 0) {
            if(aExp == 0) return (zSign << 31) | ((aFrac + bFrac) >> 13);
            zFrac = 0x40000000 + aFrac + bFrac;
            zExp = aExp;
            return (zSign << 31) | ((zExp << 23) + (zFrac >> 7));
        }

        aFrac |= 0x20000000;
        zFrac = (aFrac + bFrac) << 1;
        --zExp;

        if((i32)zFrac < 0) {
            zFrac = aFrac + bFrac;
            ++zExp;
        }

        // reconstruct the float; I've removed the rounding code and just truncate
        return (zSign << 31) | ((zExp << 23) + (zFrac >> 7));
    }

    f32 Multiply(f32 in1, f32 in2) {
        float32_t a;
        float32_t b;

        a.v = in1;
        b.v = in2;

        union ui32_f32 uA;
        uint_fast32_t uiA;
        bool signA;
        int_fast16_t expA;
        uint_fast32_t sigA;
        union ui32_f32 uB;
        uint_fast32_t uiB;
        bool signB;
        int_fast16_t expB;
        uint_fast32_t sigB;
        bool signZ;
        uint_fast32_t magBits;
        struct exp16_sig32 normExpSig;
        int_fast16_t expZ;
        uint_fast32_t sigZ, uiZ;
        union ui32_f32 uZ;

        /*------------------------------------------------------------------------
        *------------------------------------------------------------------------*/
        uA.f = a;
        uiA = uA.ui;
        signA = signF32UI( uiA );
        expA  = expF32UI( uiA );
        sigA  = fracF32UI( uiA );
        uB.f = b;
        uiB = uB.ui;
        signB = signF32UI( uiB );
        expB  = expF32UI( uiB );
        sigB  = fracF32UI( uiB );
        signZ = signA ^ signB;
        /*------------------------------------------------------------------------
        *------------------------------------------------------------------------*/
        if ( expA == 0xFF ) {
            if ( sigA || ((expB == 0xFF) && sigB) ) goto propagateNaN;
            magBits = expB | sigB;
            goto infArg;
        }
        if ( expB == 0xFF ) {
            if ( sigB ) goto propagateNaN;
            magBits = expA | sigA;
            goto infArg;
        }
        /*------------------------------------------------------------------------
        *------------------------------------------------------------------------*/
        if ( ! expA ) {
            if ( ! sigA ) goto zero;
            normExpSig = softfloat_normSubnormalF32Sig( sigA );
            expA = normExpSig.exp;
            sigA = normExpSig.sig;
        }
        if ( ! expB ) {
            if ( ! sigB ) goto zero;
            normExpSig = softfloat_normSubnormalF32Sig( sigB );
            expB = normExpSig.exp;
            sigB = normExpSig.sig;
        }
        /*------------------------------------------------------------------------
        *------------------------------------------------------------------------*/
        expZ = expA + expB - 0x7F;
        sigA = (sigA | 0x00800000)<<7;
        sigB = (sigB | 0x00800000)<<8;
        sigZ = softfloat_shortShiftRightJam64( (uint_fast64_t) sigA * sigB, 32 );
        if ( sigZ < 0x40000000 ) {
            --expZ;
            sigZ <<= 1;
        }
        return softfloat_roundPackToF32( signZ, expZ, sigZ ).v;
        /*------------------------------------------------------------------------
        *------------------------------------------------------------------------*/
    propagateNaN:
        uiZ = softfloat_propagateNaNF32UI( uiA, uiB );
        goto uiZ;
        /*------------------------------------------------------------------------
        *------------------------------------------------------------------------*/
    infArg:
        if ( ! magBits ) {
            softfloat_raiseFlags( softfloat_flag_invalid );
            uiZ = defaultNaNF32UI;
        } else {
            uiZ = packToF32UI( signZ, 0xFF, 0 );
        }
        goto uiZ;
        /*------------------------------------------------------------------------
        *------------------------------------------------------------------------*/
    zero:
        uiZ = packToF32UI( signZ, 0, 0 );
    uiZ:
        uZ.ui = uiZ;
        return uZ.f.v;

    }

private:
    static u32 shift32RightJamming(int a, int count) {
        if(count == 0)
            return a;
        else if(count < 32)
            return (a >> count) | ((a << ((-count) & 31)) != 0);
        else
            return a != 0;
    }

    uint_fast32_t
    softfloat_propagateNaNF32UI( uint_fast32_t uiA, uint_fast32_t uiB ) {
        bool isSigNaNA, isSigNaNB;
        uint_fast32_t uiNonsigA, uiNonsigB, uiMagA, uiMagB;

        /*------------------------------------------------------------------------
        *------------------------------------------------------------------------*/
        isSigNaNA = softfloat_isSigNaNF32UI( uiA );
        isSigNaNB = softfloat_isSigNaNF32UI( uiB );
        /*------------------------------------------------------------------------
        | Make NaNs non-signaling.
        *------------------------------------------------------------------------*/
        uiNonsigA = uiA | 0x00400000;
        uiNonsigB = uiB | 0x00400000;
        /*------------------------------------------------------------------------
        *------------------------------------------------------------------------*/
        if ( isSigNaNA | isSigNaNB ) {
            softfloat_raiseFlags( softfloat_flag_invalid );
            if ( isSigNaNA ) {
                if ( isSigNaNB ) goto returnLargerMag;
                return isNaNF32UI( uiB ) ? uiNonsigB : uiNonsigA;
            } else {
                return isNaNF32UI( uiA ) ? uiNonsigA : uiNonsigB;
            }
        }
    returnLargerMag:
        uiMagA = uiNonsigA & 0x7FFFFFFF;
        uiMagB = uiNonsigB & 0x7FFFFFFF;
        if ( uiMagA < uiMagB ) return uiNonsigB;
        if ( uiMagB < uiMagA ) return uiNonsigA;
        return (uiNonsigA < uiNonsigB) ? uiNonsigA : uiNonsigB;

    }

    float32_t softfloat_roundPackToF32( bool sign, int_fast16_t exp, uint_fast32_t sig ) {
        uint_fast8_t roundingMode;
        bool roundNearEven;
        uint_fast8_t roundIncrement, roundBits;
        bool isTiny;
        uint_fast32_t uiZ;
        union ui32_f32 uZ;

        /*------------------------------------------------------------------------
        *------------------------------------------------------------------------*/
        roundingMode = softfloat_roundingMode;
        roundNearEven = (roundingMode == softfloat_round_near_even);
        roundIncrement = 0x40;
        if ( ! roundNearEven && (roundingMode != softfloat_round_near_maxMag) ) {
            roundIncrement =
                (roundingMode
                    == (sign ? softfloat_round_min : softfloat_round_max))
                    ? 0x7F
                    : 0;
        }
        roundBits = sig & 0x7F;
        /*------------------------------------------------------------------------
        *------------------------------------------------------------------------*/
        if ( 0xFD <= (unsigned int) exp ) {
            if ( exp < 0 ) {
                /*----------------------------------------------------------------
                *----------------------------------------------------------------*/
                isTiny =
                    (softfloat_detectTininess == softfloat_tininess_beforeRounding)
                        || (exp < -1) || (sig + roundIncrement < 0x80000000);
                sig = softfloat_shiftRightJam32( sig, -exp );
                exp = 0;
                roundBits = sig & 0x7F;
                if ( isTiny && roundBits ) {
                    softfloat_raiseFlags( softfloat_flag_underflow );
                }
            } else if ( (0xFD < exp) || (0x80000000 <= sig + roundIncrement) ) {
                /*----------------------------------------------------------------
                *----------------------------------------------------------------*/
                softfloat_raiseFlags(
                    softfloat_flag_overflow | softfloat_flag_inexact );
                uiZ = packToF32UI( sign, 0xFF, 0 ) - ! roundIncrement;
                goto uiZ;
            }
        }
        /*------------------------------------------------------------------------
        *------------------------------------------------------------------------*/
        sig = (sig + roundIncrement)>>7;
        if ( roundBits ) {
            softfloat_exceptionFlags |= softfloat_flag_inexact;
    #ifdef SOFTFLOAT_ROUND_ODD
            if ( roundingMode == softfloat_round_odd ) {
                sig |= 1;
                goto packReturn;
            }
    #endif
        }
        sig &= ~(uint_fast32_t) (! (roundBits ^ 0x40) & roundNearEven);
        if ( ! sig ) exp = 0;
        /*------------------------------------------------------------------------
        *------------------------------------------------------------------------*/
    packReturn:
        uiZ = packToF32UI( sign, exp, sig );
    uiZ:
        uZ.ui = uiZ;
        return uZ.f;

    }

    uint_fast8_t softfloat_countLeadingZeros32(uint32_t a){
        uint_fast8_t count;

        count = 0;
        if ( a < 0x10000 ) {
            count = 16;
            a <<= 16;
        }
        if ( a < 0x1000000 ) {
            count += 8;
            a <<= 8;
        }
        count += softfloat_countLeadingZeros8[a>>24];
        return count;

    }

    struct exp16_sig32 softfloat_normSubnormalF32Sig(uint_fast32_t sig){
        int_fast8_t shiftDist;
        struct exp16_sig32 z;

        shiftDist = softfloat_countLeadingZeros32( sig ) - 8;
        z.exp = 1 - shiftDist;
        z.sig = sig<<shiftDist;
        return z;

    }

    uint64_t softfloat_shortShiftRightJam64( uint64_t a, uint_fast8_t dist ) { 
        return a>>dist | ((a & (((uint_fast64_t) 1<<dist) - 1)) != 0);
    }    

    void softfloat_raiseFlags(uint_fast8_t flags) {
        softfloat_exceptionFlags |= flags;
    }

    uint32_t softfloat_shiftRightJam32( uint32_t a, uint_fast16_t dist ) {
        return
            (dist < 31) ? a>>dist | ((uint32_t) (a<<(-dist & 31)) != 0) : (a != 0);
    }

    uint_fast8_t softfloat_exceptionFlags;
    uint_fast8_t softfloat_roundingMode = softfloat_round_near_even;
    uint_fast8_t softfloat_detectTininess = softfloat_tininess_beforeRounding;

}; // class SoftFloat