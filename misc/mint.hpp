#ifndef CP_LIBRARY_MINT
#define CP_LIBRARY_MINT

#include "template.hpp"

template <int MOD>
struct Mint {
    template <typename T>
    static constexpr int norm(T x) {
		if (0 <= x && x < MOD) {
			return int(x);
		} else if (-MOD < x && x < 0) {
		    return int(MOD - x);
		}

        x %= MOD;
        if (x < 0) {
            x += MOD;
        }
        return int(x);
    }

    static constexpr Mint pow(Mint base, long exp) {
        Mint ans = 1;
        while (exp) {
            if (exp & 1) {
                ans *= base;
            }
            base *= base;
            exp >>= 1;
        }
        return ans;
    }

    static constexpr int inv(int x) {
        int y = MOD, vx = 1, vy = 0;
        while (x) {
            int k = y / x;
            y %= x;
            vy -= k * vx;
            swap(x, y);
            swap(vx, vy);
        }
        assert(y == 1);
        if (vy < 0) {
            vy += MOD;
        }
        return vy;
    }

	static constexpr Mint inv(Mint x) {
		return x.inv();
	}

    int x;

    constexpr Mint() : x(0) {}
    constexpr Mint(int x) : x(norm(x)) {}
    constexpr Mint(long x) : x(norm(x)) {}

    static constexpr Mint from_unchecked(int x) {
        Mint m;
        m.x = x;
        return m;
    }

    friend istream& operator>>(istream& in, Mint& m) {
        long x;
        in >> x;
        m = x;
        return in;
    }
    friend ostream& operator<<(ostream& out, const Mint& m) {
        return out << m.x;
    }

    explicit operator int() const {
        return x;
    }
    explicit operator long() const {
        return x;
    }

    bool operator==(const Mint& m) const {
        return x == m.x;
    }
    bool operator!=(const Mint& m) const {
        return x != m.x;
    }

    bool operator<(const Mint& m) const {
        return x < m.x;
    }

    Mint operator-() const {
        return !x ? 0 : Mint::from_unchecked(MOD - x);
    }
    Mint operator+() const {
        return *this;
    }

    Mint inv() const {
        return Mint::from_unchecked(Mint::inv(x));
    }

    Mint& operator++() {
        x++;
        if (x == MOD) {
            x = 0;
        }
        return *this;
    }
    Mint& operator--() {
        if (!x) {
            x = MOD - 1;
        } else {
            x--;
        }
        return *this;
    }

    Mint& operator+=(const Mint& m) {
        x += m.x;
        if (x >= MOD) {
            x -= MOD;
        }
        return *this;
    }
    Mint& operator-=(const Mint& m) {
        return *this += -m;
    }

    Mint& operator*=(const Mint& m) {
        x = int((long(x) * m.x) % MOD);
        return *this;
    }
    Mint& operator/=(const Mint& m) {
        return *this *= m.inv();
    }

    friend Mint operator++(Mint& a, int) {
        Mint ans = a;
        ++a;
        return ans;
    }
    friend Mint operator--(Mint& a, int) {
        Mint ans = a;
        --a;
        return ans;
    }
    friend Mint operator+(Mint a, const Mint& b) {
        return a += b;
    }
    friend Mint operator-(Mint a, const Mint& b) {
        return a -= b;
    }
    friend Mint operator*(Mint a, const Mint& b) {
        return a *= b;
    }
    friend Mint operator/(Mint a, const Mint& b) {
        return a /= b;
    }
};

#endif  // CP_LIBRARY_MINT
