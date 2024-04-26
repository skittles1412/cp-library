#ifndef CP_LIBRARY_HASH
#define CP_LIBRARY_HASH

#include "misc/mint.hpp"

template <typename A, typename B>
struct PairNum {
    A a;
    B b;

    constexpr PairNum() : a(), b() {}
    constexpr PairNum(long x) : a(x), b(x) {}
    constexpr PairNum(const A& a, const B& b) : a(a), b(b) {}

    bool operator==(const PairNum& x) const {
        return a == x.a && b == x.b;
    }
    bool operator!=(const PairNum& x) const {
        return !(*this == x);
    }

    bool operator<(const PairNum& x) const {
        if (a == x.a) {
            return b < x.b;
        }
        return a < x.a;
    }

    PairNum& operator+=(const PairNum& x) {
        a += x.a;
        b += x.b;
        return *this;
    }
    PairNum& operator-=(const PairNum& x) {
        a -= x.a;
        b -= x.b;
        return *this;
    }
    PairNum& operator*=(const PairNum& x) {
        a *= x.a;
        b *= x.b;
        return *this;
    }
    PairNum& operator/=(const PairNum& x) {
        a /= x.a;
        b /= x.b;
        return *this;
    }

    friend PairNum operator+(PairNum a, const PairNum& b) {
        return a += b;
    }
    friend PairNum operator-(PairNum a, const PairNum& b) {
        return a -= b;
    }
    friend PairNum operator*(PairNum a, const PairNum& b) {
        return a *= b;
    }
    friend PairNum operator/(PairNum a, const PairNum& b) {
        return a /= b;
    }
};

template <typename C>
struct HashView {
    using T = typename C::T;

    int len;
    T v;

    bool operator==(const HashView& x) const {
        return len == x.len && v == x.v;
    }
    bool operator!=(const HashView& x) const {
        return !(*this == x);
    }

    bool operator<(const HashView& x) const {
        if (len == x.len) {
            return v < x.v;
        }
        return len < x.len;
    }

    HashView& operator+=(const HashView& x) {
        v = v * C::POW_COMP[x.len] + x.v;
        len += x.len;
        return *this;
    }

    HashView strip_pref(const HashView& x) const {
        return {len - x.len, v - x.v * C::POW_COMP.pow(len - x.len)};
    }

    HashView strip_suff(const HashView& x) const {
        return {len - x.len, (v - x.v) * C::POW_COMP.ipow(x.len)};
    }

    friend HashView operator+(HashView a, const HashView& b) {
        return a += b;
    }
};

template <typename C, typename T>
struct Hasher {
    using C_T = typename C::T;

    vector<T> arr;
    vector<C_T> psum;

    Hasher(const vector<T>& arr) : arr(arr), psum {0} {
        for (auto& a : arr) {
            psum.push_back(psum.back() * C::BASE + a);
        }

        C::POW_COMP.resize(sz(arr) + 5);
    }

    void push_back(const T& x) {
        arr.push_back(x);
        psum.push_back(psum.back() * C::BASE + x);
    }

    void pop_back() {
        arr.pop_back();
        psum.pop_back();
    }

    HashView<C> query(int l, int r) const {
        return HashView<C> {r, psum[r]}.strip_pref(HashView<C> {l, psum[l]});
    }
};

template <typename T>
struct PowPcomp {
    vector<T> v, iv;
    T base, ibase;

    PowPcomp(const T& base) : v {1}, iv {1}, base(base), ibase(T(1) / base) {}

    void resize(int n) {
        while (sz(v) < n) {
            v.push_back(v.back() * base);
        }
    }

    const T& pow(int ind) const {
        return v[ind];
    }
    const T& ipow(int ind) const {
        return v[ind];
    }
};

struct HashConfig {
    using T =
        PairNum<Mint<int(1e9 + 7)>,
                Mint<int(1e9 + 9)>>;  // 1e9 + 21, 33, 87, 93, 97, 103, 123, 181

    static constexpr T BASE = 1412;

    static inline PowPcomp<T> POW_COMP {BASE};
};

#endif  // CP_LIBRARY_HASH
