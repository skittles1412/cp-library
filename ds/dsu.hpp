#ifndef CP_LIBRARY_DSU
#define CP_LIBRARY_DSU

#include "template.hpp"

struct DSU {
    int comps;
    vector<int> p;

    DSU() {}
    explicit DSU(int n) : comps(n), p(n, -1) {}

    int find(int u) {
        return p[u] < 0 ? u : (p[u] = find(p[u]));
    }

    int size(int u) {
        return -p[find(u)];
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            return false;
        }
        if (p[u] < p[v]) {
            swap(u, v);
        }
        p[v] += p[u];
        p[u] = v;
        comps--;
        return true;
    }

    bool query_conn(int u, int v) {
        return find(u) == find(v);
    }
};

#endif  // CP_LIBRARY_DSU
