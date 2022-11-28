#include <bits/stdc++.h>

typedef long long ll;
typedef __int128 lll;

lll rnpow(lll x, lll y, lll mod) {
    if (y == 0) return 1;
    if (y & 1) return rnpow(x, y - 1, mod) * x % mod;
    lll res = rnpow(x, y >> 1LL, mod) % mod;
    return res * res % mod;
}

int miller(lll n, lll a) {
    if (n % a == 0) return n == a;
    lll k = n - 1;
    for (; ;) {
        lll p = rnpow(a, k, n);
        if (p == n - 1) return 1;
        if (k % 2LL) return p == 1 || p == n - 1;
        k /= 2LL;
    }
}

int isPrime(ll n) {
    if (n < 2) return 0;
    std::vector < lll > pv = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 };
    int f = 1;
    for (auto& it : pv) f &= miller(n, it);
    return f;
}

int main() {
    for (int i = 0; i < 100; ++i) {
        if (isPrime(i)) printf("%d\n", i);
    }
    return 0;
}