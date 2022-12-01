#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1e9 + 7;

#define MAXN 101010

ll fdp[MAXN];

ll rnpow(ll x, ll y, ll mod) {
    if (y == 0) return 1;
    if (y & 1) return rnpow(x, y - 1, mod) * x % mod;
    ll res = rnpow(x, y >> 1LL, mod);
    return res * res % mod;
}

ll inv(ll x, ll mod) {
    return rnpow(x, mod - 2, mod);
}

ll fac(ll x, ll mod) {
    if (fdp[x]) return fdp[x];
    return fdp[x] = x ? fac(x - 1, mod) * x % mod : 1;
}

ll catalan(ll n, ll mod) {
    ll res = fac(2 * n, mod);
    res = res * inv(fac(n + 1, mod), mod) % mod;
    res = res * inv(fac(n, mod), mod) % mod;
    return res;
}

int main() {
    for (int i = 0; i < 10; ++i) printf("%lld\n", catalan(i, MOD));
    // 1 1 2 5 14 42 132 429 1430 4862
    return 0;
}