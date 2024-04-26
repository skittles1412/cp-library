#ifndef CP_LIBRARY_UTILS
#define CP_LIBRARY_UTILS

#include "template.hpp"

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& arr) {
    out << "[";
    for (int i = 0; i < sz(arr); i++) {
        if (i) {
            out << ", ";
        }
        out << arr[i];
    }
    return out << "]";
}

template <typename T, size_t N>
ostream& operator<<(ostream& out, const array<T, N>& arr) {
    out << "[";
    for (size_t i = 0; i < N; i++) {
        if (i) {
            out << ", ";
        }
        out << arr[i];
    }
    return out << "]";
}

template <typename A, typename B>
ostream& operator<<(ostream& out, const pair<A, B>& p) {
    return out << "(" << p.first << ", " << p.second << ")";
}

/**
 * Computes the first x in [l, r) such that cb(x) is true.
 *
 * If no x in that range is true, returns r
 */
template <typename Cb>
int first_true(int l, int r, const Cb& cb) {
    while (l < r) {
        int mid = (l + r) / 2;
        if (cb(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

/**
 * Computes the last x in (l, r] such that cb(x) is true.
 *
 * If no x in that range is true, returns l
 */
template <typename Cb>
int last_true(int l, int r, const Cb& cb) {
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (cb(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

template <typename T>
T reversed(T arr) {
    reverse(begin(arr), end(arr));
    return arr;
}

template <typename T>
bool is_palin(const T& arr) {
    return arr == reversed(arr);
}

template <typename T, bool STRICT>
vector<int> comp_prev_helper(const vector<T>& arr) {
    int n = sz(arr);

    vector<int> ans(n);

    vector<pair<int, int>> st;
    for (int i = 0; i < n; i++) {
        auto cmp = [&]() -> bool {
            if constexpr (STRICT) {
                return st.back().first <= arr[i];
            } else {
                return st.back().first < arr[i];
            }
        };
        while (sz(st) && cmp()) {
            st.pop_back();
        }

        if (sz(st)) {
            ans[i] = st.back().second;
        } else {
            ans[i] = -1;
        }
        st.emplace_back(arr[i], i);
    }

    return ans;
}

/**
 * Computes ans[i], the closest index j to the left of i where arr[j] > arr[i]
 *
 * ans[i] = -1 if no such j exists
 */
template <typename T>
vector<int> comp_prev_gt(const vector<T>& arr) {
    return comp_prev_helper<true>(arr);
}

/**
 * Computes ans[i], the closest index j to the left of i where arr[j] >= arr[i]
 *
 * ans[i] = -1 if no such j exists
 */
template <typename T>
vector<int> comp_prev_ge(const vector<T>& arr) {
    return comp_prev_helper<false>(arr);
}

/**
 * reverses an array of indices
 *
 * specifically, it reverses the array and computes arr[i] = n - 1 - arr[i]
 */
vector<int> reverse_indices(vector<int> arr) {
    int n = sz(arr);

    reverse(begin(arr), end(arr));
    for (auto& a : arr) {
        a = n - 1 - a;
    }

    return arr;
}

/**
 * Computes ans[i], the closest index j to the right of i where arr[j] > arr[i]
 *
 * ans[i] = -1 if no such j exists
 */
template <typename T>
vector<int> comp_next_gt(vector<T> arr) {
    reverse(begin(arr), end(arr));

    return reverse_indices(comp_prev_gt(arr));
}

/**
 * Computes ans[i], the closest index j to the right of i where arr[j] >= arr[i]
 *
 * ans[i] = -1 if no such j exists
 */
template <typename T>
vector<int> comp_next_ge(vector<T> arr) {
    reverse(begin(arr), end(arr));

    return reverse_indices(comp_prev_ge(arr));
}

#endif  // CP_LIBRARY_UTILS
