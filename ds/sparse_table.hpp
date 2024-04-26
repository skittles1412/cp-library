#ifndef CP_LIBRARY_SPARSE_TABLE
#define CP_LIBRARY_SPARSE_TABLE

#include "template.hpp"

struct MinOp {
    template <typename T>
    T operator()(const T& a, const T& b) const {
        return min(a, b);
    }
};

struct MaxOp {
    template <typename T>
    T operator()(const T& a, const T& b) const {
        return max(a, b);
    }
};

template <typename T, typename Op>
struct SparseTable {
    int n;
    vector<vector<T>> v;
    Op op;

    SparseTable() {}
    explicit SparseTable(const vector<T>& arr, const Op& op = {})
        : n(sz(arr)), v(__lg(max(n, 1)) + 1, vector<T>(n)), op(op) {
        v[0] = arr;

        for (int i = 1; i <= __lg(n); i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                v[i][j] = op(v[i - 1][j], v[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    /**
     * inclusive, exclusive query
     */
    T query(int l, int r) const {
        int k = __lg(r - l);
        return op(v[k][l], v[k][r - (1 << k)]);
    }
};

#endif  // CP_LIBRARY_SPARSE_TABLE
