#include "bits/extc++.h"
#include "template.hpp"
#include "ds/psa.hpp"

#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (auto& a : arr) {
        cin >> a;
    }
    PSA<long> psa(arr);

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << psa.query(l, r) << endl;
    }
}

int main() {
    cin.tie(nullptr);
    cin.exceptions(ios::failbit);
    ios_base::sync_with_stdio(false);
    solve();
}
