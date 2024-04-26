#ifndef CP_LIBRARY_BIT
#define CP_LIBRARY_BIT

#include "template.hpp"

template <typename T, bool TRACK_VALUES = false>
struct BIT {
    int n;
    vector<T> v, arr;

    BIT() {}
    explicit BIT(int n) : n(n), v(n + 1) {}
    template <typename U>
    explicit BIT(const vector<U>& arr) : n(sz(arr)), v(n + 1) {
        if constexpr (TRACK_VALUES) {
            this->arr.resize(n);
        }

        // TODO: O(n) bit build
        for (int i = 0; i < n; i++) {
            update_add(i, arr[i]);
        }
    }

    void update_add(int ind, const T& x) {
        if constexpr (TRACK_VALUES) {
            arr[ind] += x;
        }

        ind++;
        while (ind <= n) {
            v[ind] += x;
            ind += ind & -ind;
        }
    }

    T psum(int ind) const {
        T ans {};
        while (ind > 0) {
            ans += v[ind];
            ind -= ind & -ind;
        }
        return ans;
    }

    /**
     * inclusive, exclusive query
     */
    T query(int l, int r) const {
        return psum(r) - psum(l);
    }
};

template <typename T>
struct BIT<T, true> {
    void update_set(int ind, const T& x) {
        update_add(ind, x - this->arr[ind]);
    }
};

template <typename T, bool TRACK_VALUES = false>
struct BIT2 {
    int n;
    vector<BIT<T, TRACK_VALUES>> v;

    explicit BIT2(int n, int m) : n(n), v(n + 1, BIT<T, TRACK_VALUES>(m)) {}
    template <typename U>
    explicit BIT2(const vector<vector<U>>& arr) : n(sz(arr)) {
        v.emplace_back();
        for (auto& a : arr) {
            v.emplace_back(a);
        }
    }

    void update_add(int ind, int y, const T& val) {
        ind++;
        while (ind <= n) {
            v[ind].update_add(y, val);
            ind += ind & -ind;
        }
    }

    T psum(int ind, int y) const {
        T ans {};
        while (ind > 0) {
            ans += v[ind].query(y);
            ind -= ind & -ind;
        }
        return ans;
    }

    /**
     * inclusive, exclusive query
     */
    T query(int x1, int x2, int y1, int y2) const {
        return psum(y1, y2) - psum(x1, y2) - psum(x2, y1) + psum(x1, y1);
    }
};

template <typename T>
struct BIT2<T, true> {
    void update_set(int ind, int y, const T& x) {
        ind++;
        while (ind <= this->n) {
            this->v[ind].update_set(y, this->val);
            ind += ind & -ind;
        }
    }
};

#endif  // CP_LIBRARY_BIT
