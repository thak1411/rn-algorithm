#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include <functional>
#include <algorithm>
#include <iostream>
#include <utility>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <bitset>
#include <vector>
#include <random>
#include <cstdio>
#include <string>
#include <cmath>
#include <queue>
#include <stack>
#include <ctime>
#include <tuple>
#include <list>
#include <map>
#include <set>
#define MOD 1000000007LL
#define f first
#define s second
#define all(v) (v).begin(), (v).end()
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef std::pair < int, int > pii;
typedef std::pair < int, pii > piii;
typedef std::pair < ll, ll > pll;
typedef std::pair < ll, pll > plll;
int dx[8] = { 1, 0, -1, 0, 1, 1, -1, -1 };
int dy[8] = { 0, -1, 0, 1, 1, -1, -1, 1 };
ll rnpow(ll x, ll y, ll mod = MOD) {
    if (y == 0) return 1;
    if (y & 1) return rnpow(x, y - 1, mod) * x % mod;
    ll res = rnpow(x, y >> 1LL, mod) % mod;
    return res * res % mod;
}
ull rnpow(ull x, ull y, ull mod = MOD) {
    if (y == 0) return 1;
    if (y & 1) return rnpow(x, y - 1, mod) * x % mod;
    ull res = rnpow(x, y >> 1ULL, mod) % mod;
    return res * res % mod;
}
int gcd(int i, int j) { return i ? gcd(j % i, i) : j; }
ll gcd(ll i, ll j) { return i ? gcd(j % i, i) : j; }
int lcm(int i, int j) { return i / gcd(i, j) * j; }
ll lcm(ll i, ll j) { return i / gcd(i, j) * j; }
ll fac(ll x) { return x ? fac(x - 1) * x : 1; }
ll ccw(pll i, pll j, pll k) { return (i.f * j.s + i.s * k.f + j.f * k.s) - (j.f * i.s + j.s * k.f + k.s * i.f); }

int main() {
    
    return 0;
}
