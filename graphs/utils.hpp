#ifndef CP_LIBRARY_GRAPHS_UTILS
#define CP_LIBRARY_GRAPHS_UTILS

#include "template.hpp"

template <bool UNDIRECTED>
vector<vector<int>> edges_to_adj(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> graph(n);

    for (auto& [u, v] : edges) {
        graph[u].push_back(v);
        if constexpr (UNDIRECTED) {
            graph[v].push_back(u);
        }
    }

    return graph;
}

#endif  // CP_LIBRARY_GRAPHS_UTILS
