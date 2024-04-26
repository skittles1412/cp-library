#include "bits/extc++.h"
#include "template.hpp"
#include "misc/pfact.hpp"

#define PROBLEM \
    "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"

void test_small() {
    int n = 1000;
    PFact pfact(n);

    auto is_prime = [&](int x) -> bool {
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                return false;
            }
        }
        return true;
    };

    assert(!pfact.is_prime(0) && !pfact.is_prime(1));
    for (int i = 2; i <= n; i++) {
        assert(pfact.is_prime(i) == is_prime(i));
    }

    vector<int> facts[n + 1];
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            facts[j].push_back(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        auto facts2 = pfact.enumerate_factors(i);
        sort(begin(facts2), end(facts2));
        assert(facts[i] == facts2);
        assert(pfact.count_factors(i) == sz(facts[i]));
    }
}

int main() {
    cin.tie(nullptr);
    cin.exceptions(ios::failbit);
    ios_base::sync_with_stdio(false);

    test_small();

    cout << "Hello World" << endl;
}
