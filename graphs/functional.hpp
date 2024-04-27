#ifndef CP_LIBRARY_FUNCTIONAL_GRAPH
#define CP_LIBRARY_FUNCTIONAL_GRAPH

#include "template.hpp"

struct FunctionalGraph {
    int n, comps;
    vector<int> comp_id;
    vector<bool> in_cyc;
    vector<vector<int>> igraph, cycs;

    FunctionalGraph() {}
    FunctionalGraph(int n, const vector<int>& arr)
        : n(n), comps(0), comp_id(n, -1), in_cyc(n), igraph(n) {
        for (int i = 0; i < n; i++) {
            igraph[arr[i]].push_back(i);
        }

        vector<int> st;
        for (int i = 0; i < n; i++) {
            if (comp_id[i] != -1) {
                continue;
            }

            st.clear();

            int u = i;
            while (comp_id[u] == -1) {
                comp_id[u] = -2;
                st.push_back(u);
                u = arr[u];
            }

            if (comp_id[u] == -2) {
                comp_id[u] = sz(cycs);
                cycs.emplace_back(find(begin(st), end(st), u), end(st));
                for (auto& a : cycs.back()) {
                    in_cyc[a] = true;
                }
            }
            for (auto& a : st) {
                comp_id[a] = comp_id[u];
            }
        }

        comps = sz(cycs);
    }

    vector<vector<int>> components() const {
        vector<vector<int>> ans(comps);

        for (int i = 0; i < n; i++) {
            ans[comp_id[i]].push_back(i);
        }

        return ans;
    }
};

#endif  // CP_LIBRARY_FUNCTIONAL_GRAPH
