#ifndef CP_LIBRARY_TIMESET
#define CP_LIBRARY_TIMESET

#include "template.hpp"

struct TimeSet {
    int t;
    vector<int> v;

    TimeSet() {}
    explicit TimeSet(int n) : t(0), v(n, -1) {}

    bool operator[](int ind) const {
        return v[ind] == t;
    }

    void insert(int ind) {
        v[ind] = t;
    }

    void erase(int ind) {
        v[ind] = -1;
    }

    void clear() {
        t++;
    }
};

#endif  // CP_LIBRARY_TIMESET
