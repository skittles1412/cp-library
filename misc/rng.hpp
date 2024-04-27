#ifndef CP_LIBRARY_RAND
#define CP_LIBRARY_RAND

#include "template.hpp"

struct Rng {
    mt19937_64 cowng;

    Rng() : Rng(chrono::steady_clock::now().time_since_epoch().count()) {}
    Rng(u64 seed) : cowng(seed) {}

    long rint(long l, long r) {
        return uniform_int_distribution(l, r)(cowng);
    }
};

#endif  // CP_LIBRARY_RAND
