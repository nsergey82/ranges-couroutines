#ifndef RNG_CRTN_FZBZ_HELPERS_H
#define RNG_CRTN_FZBZ_HELPERS_H

#include <string>

namespace helper
{
    constexpr unsigned marker = 1 << 30;

    template<unsigned div_by, typename T>
    inline T mark_divisibles(T v) {
        // ignore already marked values and non-div
        if (v > marker || v % div_by)
            return v;
        else
            return div_by + marker; // mark
    }

    std::string _str_g(int v) {
        return v < helper::marker ? std::to_string(v) :
                                    std::to_string(v - helper::marker);
    }
}


#endif
