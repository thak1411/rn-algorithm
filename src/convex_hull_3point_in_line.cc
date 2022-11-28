#include <bits/stdc++.h>

typedef long long ll;
typedef std::pair < int, int > pii;
typedef std::pair < ll, ll > pll;
#define f first
#define s second
#define all(v) (v).begin(), (v).end()

ll ccw(pll i, pll j, pll k) {
    return (i.f * j.s + i.s * k.f + j.f * k.s)
        - (j.f * i.s + j.s * k.f + k.s * i.f);
}

std::vector < pii > get_convex_hull(std::vector < pii > v) {
    std::vector < pii > ch;

    std::sort(all(v), [] (pii i, pii j) {
        return i.f == j.f ? i.s < j.s : i.f < j.f;
    });
    std::sort(1 + all(v), [&] (pii i, pii j) {
        ll l = 1LL * (i.s - v[0].s) * (j.f - v[0].f), r = 1LL * (j.s - v[0].s) * (i.f - v[0].f);
        return l == r ? hypot(i.s - v[0].s, i.f - v[0].f) < hypot(j.s - v[0].s, j.f - v[0].f) : l < r;
    });
    int pv = v.size() - 1;
    for (int i = v.size() - 1; i--; ) {
        ll l = 1LL * (v[i].s - v[0].s) * (v[i + 1].f - v[0].f), r = 1LL * (v[i + 1].s - v[0].s) * (v[i].f - v[0].f);
        if (l == r) pv = i;
        else break;
    }
    std::reverse(v.begin() + pv, v.end());
    ch.push_back(v[0]);
    if (v.size() > 1) ch.push_back(v[1]);
    for (int i = 2; i < v.size(); ++i) {
        for (; ch.size() > 1 && ccw(ch[ch.size() - 2], ch[ch.size() - 1], v[i]) <= 0; ) ch.pop_back();
        ch.push_back(v[i]);
    }
    for (; ch.size() > 1 && ccw(ch[ch.size() - 2], ch[ch.size() - 1], ch[0]) <= 0; ) ch.pop_back();
    return ch;
}

int main() {
    std::vector < pii > v;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            v.emplace_back(i, j);
        }
    }
    auto ch = get_convex_hull(v);
    for (auto& it : ch) {
        printf("(%d, %d)\n", it.f, it.s);
    }
    return 0;
}