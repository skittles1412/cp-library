#ifndef CP_LIBRARY_PSA
#define CP_LIBRARY_PSA

#include "template.hpp"

template <typename T>
struct PSA {
    vector<T> psum;

    PSA() {}
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

template <typename T>
struct RPSA {
    vector<T> psum;

    RPSA() {}
    explicit RPSA(int n) : psum(n) {}

    /**
     * inclusive, exclusive
     */
    void update_add(int l, int r, T x) {
        psum[l] += x;
        if (r < sz(psum)) {
            psum[r] -= x;
        }
    }

    vector<T> build() const {
        auto ans = psum;
        partial_sum(begin(ans), end(ans), begin(ans));
        return ans;
    }
};

#endif  // CP_LIBRARY_PSA
