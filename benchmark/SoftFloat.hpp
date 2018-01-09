using f32 = uint32_t;
using u32 = uint32_t;
using i32 = int32_t;

class SoftFloat {

public:
    static f32 Add(f32 a, f32 b) {
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

private:
    static u32 shift32RightJamming(int a, int count) {
        if(count == 0)
            return a;
        else if(count < 32)
            return (a >> count) | ((a << ((-count) & 31)) != 0);
        else
            return a != 0;
    }

}; // class SoftFloat