#ifndef CP_LIBRARY_PFACT
#define CP_LIBRARY_PFACT

struct PFact {
    vector<int> mdiv, primes;

    PFact() {}
    explicit PFact(int n) : mdiv(n + 1, -1) {
        for (int i = 2; i <= n; i++) {
            if (mdiv[i] == -1) {
                primes.push_back(i);
                mdiv[i] = i;
            }

            for (auto& a : primes) {
                if (a * i > n || a > mdiv[i]) {
                    break;
                }

                mdiv[a * i] = a;
            }
        }
    }

    bool is_prime(int x) const {
        return mdiv[x] == x;
    }

    /**
     * cb called with (prime, exponent)
     */
    template <typename Cb>
    void factorize(int x, const Cb& cb) const {
        while (x > 1) {
            int p = mdiv[x], e = 0;
            while (x % p == 0) {
                e++;
                x /= p;
            }
            cb(p, e);
        }
    }

    /**
     * vector of (prime, exponent)
     */
    vector<pair<int, int>> factorize(int x) const {
        vector<pair<int, int>> ans;
        factorize(x, [&](int p, int e) -> void {
            ans.emplace_back(p, e);
        });
        return ans;
    }

    int count_factors(int x) const {
        int ans = 1;
        factorize(x, [&](int, int e) -> void {
            ans *= e + 1;
        });
        return ans;
    }

    template <typename Cb>
    void enumerate_factors(int x, const Cb& cb) const {
        assert(x);

        auto pf = factorize(x);
        enumerate_factors(1, 0, pf, cb);
    }

    vector<int> enumerate_factors(int x) const {
        vector<int> ans;
        enumerate_factors(x, [&](int o) -> void {
            ans.push_back(o);
        });
        return ans;
    }

   private:
    template <typename Cb>
    void enumerate_factors(int cmul,
                           int ind,
                           const vector<pair<int, int>>& pf,
                           const Cb& cb) const {
        if (ind == sz(pf)) {
            cb(cmul);
            return;
        }

        enumerate_factors(cmul, ind + 1, pf, cb);
        auto& [p, e] = pf[ind];
        for (int i = 0; i < e; i++) {
            cmul *= p;
            enumerate_factors(cmul, ind + 1, pf, cb);
        }
    }
};

#endif  // CP_LIBRARY_PFACT
