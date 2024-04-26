#ifndef CP_LIBRARY_SEGTREE
#define CP_LIBRARY_SEGTREE

#include "template.hpp"

template <typename Node_T, typename Operation = plus<Node_T>, bool debug_assertions = true>
class SegTree {
   private:
    static constexpr Node_T noT {};

   public:
    int n;
    Operation operation;

    vector<Node_T> v, arr;

    constexpr SegTree() : n(0) {}
    explicit SegTree(const vector<Node_T>& _arr,
                     const Operation& _operation = Operation())
        : n(sz(_arr)), operation(_operation), v(4 * n), arr(_arr) {
        if (n) {
            build(1, 0, n - 1);
        }
    }

   private:
    void build(int o, int l, int r) {
        if (l == r) {
            v[o] = arr[l];
            return;
        }
        int mid = (l + r) / 2, lc = o * 2, rc = lc + 1;

        build(lc, l, mid);
        build(rc, mid + 1, r);

        v[o] = operation(v[lc], v[rc]);
    }

    template <typename F>
    void set_func(int o, int l, int r, int ind, const F& f) {
        if (l == r) {
            f(arr[l]);
            v[o] = arr[l];
            return;
        }

        int mid = (l + r) / 2, lc = o * 2, rc = lc + 1;

        if (ind <= mid) {
            set_func(lc, l, mid, ind, f);
        } else {
            set_func(rc, mid + 1, r, ind, f);
        }

        v[o] = operation(v[lc], v[rc]);
    }

    [[nodiscard]] Node_T query(int o, int l, int r, int ql, int qr) const {
        if (ql <= l && r <= qr) {
            return v[o];
        }
        int mid = (l + r) / 2, lc = o * 2, rc = lc + 1;

        if (ql <= mid) {
            if (mid < qr) {
                return operation(query(lc, l, mid, ql, qr),
                                 query(rc, mid + 1, r, ql, qr));
            }
            return query(lc, l, mid, ql, qr);
        }
        return query(rc, mid + 1, r, ql, qr);
    }

    template <typename Predicate, bool first>
    [[nodiscard]] int bsearch(int o,
                              int l,
                              int r,
                              const Node_T& pref,
                              const Predicate& predicate) const {
        if (l == r) {
            return l;
        }

        int mid = (l + r) / 2, lc = o * 2, rc = lc + 1;
        Node_T npref;
        if (first) {
            npref = operation(pref, v[lc]);
        } else {
            npref = v[rc];
        }

        if (predicate(npref)) {
            return bsearch<Predicate, first>(lc, l, mid, pref, predicate);
        }
        return bsearch<Predicate, true>(rc, mid + 1, r, npref,
                                        predicate);
    }

    template <typename Predicate>
    [[nodiscard]] pair<int, Node_T> bsearchl(int o,
                                             int l,
                                             int r,
                                             int ql,
                                             const Node_T& pref,
                                             const Predicate& predicate) const {
        if (ql <= l) {
            Node_T npref;
            if (ql < l) {
                npref = operation(pref, v[o]);
            } else {
                npref = v[o];
            }
            if (!predicate(npref)) {
                return {r + 1, npref};
            }
            if (ql < l) {
                return {bsearch<Predicate, true>(o, l, r, pref, predicate),
                        npref};
            } else {
                return {bsearch<Predicate, false>(o, l, r, pref, predicate),
                        npref};
            }
        } else {
            int mid = (l + r) / 2;
            if (ql <= mid) {
                auto [ans, npref] =
                    bsearchl(o * 2, l, mid, ql, pref, predicate);
                if (ans <= mid) {
                    return {ans, operation(npref, v[o * 2 + 1])};
                }
                return bsearchl(o * 2 + 1, mid + 1, r, ql, npref, predicate);
            }
            return bsearchl(o * 2 + 1, mid + 1, r, ql, pref, predicate);
        }
    }

   public:
    /**
     * inclusive, exclusive query
     */
    [[nodiscard]] Node_T query(int l, int r) const {
        if constexpr (debug_assertions) {
            assert(0 <= l);
            assert(l < n);
            assert(0 <= r);
            assert(r < n);
            assert(l <= r);
        }
        return query(1, 0, n - 1, l, r + 1);
    }

    void update_set(int ind, const Node_T& x) {
        update(ind, [&](Node_T& t) { t = x; });
    }

    /**
     * applies the function f to arr[ind]
     * f should be of signature (Node_T&) -> void
     */
    template <typename F>
    void update(int ind, const F& f) {
        if constexpr (debug_assertions) {
            assert(0 <= ind);
            assert(ind < n);
        }
        set_func(1, 0, n - 1, ind, f);
    }

    /**
     * computes the first index i such that predicate(query(0, i)) returns true
     * or n, if no such index exists
     */
    template <typename Predicate>
    [[nodiscard]] int bsearch(const Predicate& predicate) const {
        if (!predicate(v[1])) {
            return n;
        }
        return bsearch<Predicate, true>(1, 0, n - 1, noT, predicate);
    }

    /**
     * computes the first index i (i >= l) such that predicate(query(l, i))
     * returns true or n, if no such index exists
     */
    template <typename Predicate>
    [[nodiscard]] int bsearchl(int l, const Predicate& predicate) const {
        return bsearchl(1, 0, n - 1, l, noT, predicate).first;
    }
};

#endif  // CP_LIBRARY_SEGTREE
