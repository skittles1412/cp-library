#ifndef CP_LIBRARY_PSA
#define CP_LIBRARY_PSA

#include "template.hpp"

template <typename T>
struct PSA {
    vector<T> psum;

    template <typename U>
    explicit PSA(const vector<U>& arr) {
        psum.push_back(0);
        for (auto& a : arr) {
            psum.push_back(psum.back() + a);
        }
    }

    /**
     * inclusive, exclusive
     */
    T query(int l, int r) const {
        return psum[r] - psum[l];
    }
};

#endif  // CP_LIBRARY_PSA
