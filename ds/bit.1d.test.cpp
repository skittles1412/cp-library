#include "bits/extc++.h"
#include "template.hpp"
#include "ds/bit.hpp"

#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (auto& a : arr) {
        cin >> a;
    }

    BIT<long> st(arr);

    while (q--) {
        int ty;
        cin >> ty;

        if (ty == 0) {
            int ind, x;
            cin >> ind >> x;
            st.update_add(ind, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.query(l, r) << endl;
        }
    }
}

int main() {
    cin.tie(nullptr);
    cin.exceptions(ios::failbit);
    ios_base::sync_with_stdio(false);
    solve();
}
