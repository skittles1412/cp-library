#include "bits/extc++.h"
#include "template.hpp"
#include "ds/sparse_table.hpp"

#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (auto& a : arr) {
        cin >> a;
    }

    SparseTable<int, MinOp> st(arr);

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r) << endl;
    }
}

int main() {
    cin.tie(nullptr);
    cin.exceptions(ios::failbit);
    ios_base::sync_with_stdio(false);
    solve();
}
