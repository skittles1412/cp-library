#include "bits/extc++.h"
#include "../template.hpp"
#include "dsu.hpp"

#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

void solve() {
    int n, q;
    cin >> n >> q;

    DSU dsu(n);

    while (q--) {
        int ty, u, v;
        cin >> ty >> u >> v;

        if (ty == 0) {
            dsu.merge(u, v);
        } else {
            cout << dsu.query_conn(u, v) << endl;
        }
    }
}

int main() {
    cin.tie(nullptr);
    cin.exceptions(ios::failbit);
    ios_base::sync_with_stdio(false);
    solve();
}
