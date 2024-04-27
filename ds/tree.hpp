#ifndef CP_LIBRARY_TREE
#define CP_LIBRARY_TREE

#include "template.hpp"
#include "graphs/utils.hpp"
#include "ds/sparse_table.hpp"

struct Tree {
    int n, root;
    vector<int> depth, par, tin, tout, ord;
    vector<vector<int>> graph, graph_ch;

    Tree() {}
    Tree(int n, const vector<pair<int, int>>& edges, int root = 0)
        : Tree(n, edges_to_adj<true>(n, edges), root) {}
    /**
     * graph should be undirected
     */
    Tree(int n, const vector<vector<int>>& graph, int root = 0)
        : n(n),
          root(root),
          depth(n),
          par(n),
          tin(n),
          tout(n),
          graph(graph),
          graph_ch(graph) {
        dfs(root, -1, 0);
    }

    void dfs(int u, int p, int d) {
        depth[u] = d;
        par[u] = p;
        tin[u] = sz(ord);
        ord.push_back(u);

        for (auto& v : graph_ch[u]) {
            graph_ch[v].erase(find(begin(graph_ch[v]), end(graph_ch[v]), u));
            dfs(v, u, d + 1);
        }

        tout[u] = sz(ord);
    }

    bool anc(int u, int v) const {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }
};

struct LCA {
    const Tree& tree;
    vector<int> tin;
    vector<pair<int, int>> ord;
    SparseTable<pair<int, int>, MinOp> st_ord;

    LCA(const Tree& tree) : tree(tree), tin(tree.n) {
        dfs(tree.root);

        st_ord = SparseTable<pair<int, int>, MinOp>([&]() {
            vector<pair<int, int>> res;
            for (auto& [v, ei] : ord) {
                res.emplace_back(tin[v], ei);
            }
            return res;
        }());
    }

    void dfs(int u) {
        tin[u] = sz(ord);

        for (int i = 0; i < sz(tree.graph_ch[u]); i++) {
            int v = tree.graph_ch[u][i];

            ord.emplace_back(u, -i);
            dfs(v);
        }
        if (!sz(tree.graph_ch[u])) {
            ord.emplace_back(u, INT_MIN);
        }
    }

    int query(int u, int v) const {
        if (tin[u] > tin[v]) {
            swap(u, v);
        }
        dbg(tin[u], tin[v], st_ord.query(tin[u], tin[v] + 1).first,
            ord[3].first, ord[4].first);
        return ord[st_ord.query(tin[u], tin[v] + 1).first].first;
    }

    int immediate_child(int u, int v) const {
        assert(tree.anc(u, v));
        assert(u != v);

        return tree.graph_ch[u][-st_ord.query(tin[u], tin[v]).second];
    }
};

#endif  // CP_LIBRARY_TREE
