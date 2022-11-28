#include <bits/stdc++.h>

typedef long long ll;

#define MAXN 101010
#define MIN_SIZE (ll)0
#define MAX_SIZE (ll)1e9
#define MAX_SIZE_LOG 40

struct Line {
    ll a, b;
    Line() : a(0), b(9e18) { }
    Line(ll a, ll b) : a(a), b(b) { }

    ll get(ll x) { return a * x + b; }
};

struct Node {
    int l, r;
    Line v;
    Node() { }
    Node(int l, int r, Line v) : l(l), r(r), v(v) { }
};
Node node[MAXN * MAX_SIZE_LOG];
ll dp[MAXN], a[MAXN], b[MAXN], c[MAXN];

int newNode() {
    static int cnt = 1;
    return ++cnt;
}

void ins(int nd, ll l, ll r, Line d) {
    ll m = l + r >> 1LL;
    Line lo = node[nd].v, hi = d;
    if (lo.get(l) > hi.get(l)) std::swap(lo, hi);

    if (lo.get(r) <= hi.get(r)) {
        node[nd].v = lo;
        return;
    }
    if (lo.get(m) < hi.get(m)) {
        node[nd].v = lo;
        if (!node[nd].r) node[nd].r = newNode();
        ins(node[nd].r, m + 1, r, hi);
    } else {
        node[nd].v = hi;
        if (!node[nd].l) node[nd].l = newNode();
        ins(node[nd].l, l, m, lo);
    }
}

ll query(int nd, ll l, ll r, ll x) {
    if (!nd) return 9e18;
    ll m = l + r >> 1LL;
    if (x <= m) return std::min(node[nd].v.get(x), query(node[nd].l, l, m, x));
    return std::min(node[nd].v.get(x), query(node[nd].r, m + 1, r, x));
}

int main() {
    // dp[i] = min(a[i] * dp[j] + b[i] + c[j]) (0 <= j < i)
    // dp[i] = min(a[i] * dp[j] + c[j]) + b[i] (0 <= j < i)
    // Ax + b / A: dp[j], x: a[i], b = c[j]
    int n = 4;
    for (int i = 1; i <= n; ++i) a[i] = 7 - i;
    for (int i = 1; i <= n; ++i) b[i] = 10;
    for (int i = 1; i <= n; ++i) c[i] = 10 * i;
    dp[1] = b[1];
    for (int i = 2; i <= n; ++i) {
        int j = i - 1;
        ins(1, MIN_SIZE, MAX_SIZE, Line(dp[j], c[j]));
        dp[i] = query(1, MIN_SIZE, MAX_SIZE, a[i]) + b[i];
    }
    for (int i = 1; i <= n; ++i) printf("%lld ", dp[i]); puts("");
    return 0;
}