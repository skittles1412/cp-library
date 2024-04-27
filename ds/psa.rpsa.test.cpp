#include "bits/extc++.h"
#include "template.hpp"
#include "utils.hpp"
#include "misc/rng.hpp"
#include "ds/psa.hpp"

#define PROBLEM \
    "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

Rng R;

template <typename T>
struct RPSASlow {
    vector<T> arr;

    RPSASlow(int n) : arr(n) {}

    void update_add(int l, int r, T x) {
        for (int i = l; i < r; i++) {
            arr[i] += x;
        }
    }

    vector<T> build() const {
        return arr;
    }
};

void run_test() {
    int n = R.rint(1, 10), q = 100;

    RPSA<int> fast(n);
    RPSASlow<int> slow(n);
    while (q--) {
        int l = R.rint(0, n - 1), r = R.rint(l, n - 1), x = R.rint(-100, 100);

        fast.update_add(l, r, x);
        slow.update_add(l, r, x);
        assert(fast.build() == slow.build());
    }
}

int main() {
    cin.tie(nullptr);
    cin.exceptions(ios::failbit);
    ios_base::sync_with_stdio(false);
    int tcs = 1000;
    while (tcs--) {
        run_test();
    }

    cout << "Hello World" << endl;
}
