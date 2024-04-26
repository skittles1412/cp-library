#include "bits/extc++.h"
#include "template.hpp"
#include "ds/tree.hpp"

#define PROBLEM "https://judge.yosupo.jp/problem/lca"

void solve() {
    int n, q;
    cin >> n >> q;

    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        edges.emplace_back(p, i);
    }

    Tree tree(n, edges);
    LCA lca(tree);

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca.query(u, v) << endl;
    }
}

int main() {
    cin.tie(nullptr);
    cin.exceptions(ios::failbit);
    ios_base::sync_with_stdio(false);
    solve();
}
