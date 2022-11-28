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
        return 1LL * (i.s - v[0].s) * (j.f - v[0].f) < 1LL * (j.s - v[0].s) * (i.f - v[0].f);
    });
    ch.push_back(v[0]);
    if (v.size() > 1) ch.push_back(v[1]);
    for (int i = 2; i < v.size(); ++i) {
        for (; ch.size() > 1 && ccw(ch[ch.size() - 2], ch[ch.size() - 1], v[i]) <= 0; ) ch.pop_back();
        ch.push_back(v[i]);
    }
    for (; ch.size() > 1 && ccw(ch[ch.size() - 2], ch[ch.size() - 1], ch[0]) <= 0; ) ch.pop_back();
    return ch;
}

ll rotating_calipers(std::vector < pii > v) {
    ll res = 0;
    auto ch = get_convex_hull(v);
    if (ch.size() == 1) {
        return 0;
    }
    if (ch.size() == 2) {
        return 1LL * (ch[1].f - ch[0].f) * (ch[1].f - ch[0].f) + 1LL * (ch[1].s - ch[0].s) * (ch[1].s - ch[0].s);
    }
    for (int i = 0, j = 1; i < ch.size(); ++i) {
        int ni = (i + 1) % ch.size();
        for (; ;) {
            int nj = (j + 1) % ch.size();
            if (ccw(ch[i], ch[ni], pii(ch[nj].f - ch[j % ch.size()].f + ch[ni].f, ch[nj].s - ch[j % ch.size()].s + ch[ni].s)) <= 0) break;
            int k = 0;
            res = std::max(res, 1LL * (ch[i].f - ch[(j + k + ch.size()) % ch.size()].f) * (ch[i].f - ch[(j + k + ch.size()) % ch.size()].f) + 1LL * (ch[i].s - ch[(j + k + ch.size()) % ch.size()].s) * (ch[i].s - ch[(j + k + ch.size()) % ch.size()].s));
            ++j;
        }
        for (int k = -3; k <= 3; ++k) {
            res = std::max(res, 1LL * (ch[i].f - ch[(j + k + ch.size()) % ch.size()].f) * (ch[i].f - ch[(j + k + ch.size()) % ch.size()].f) + 1LL * (ch[i].s - ch[(j + k + ch.size()) % ch.size()].s) * (ch[i].s - ch[(j + k + ch.size()) % ch.size()].s));
        }
    }
    return res;
}

int main() {
    std::vector < pii > v;
    v.emplace_back(1, 1);
    v.emplace_back(5, 1);
    v.emplace_back(3, 3);
    v.emplace_back(2, 4);
    v.emplace_back(6, 5);
    printf("%lld\n", rotating_calipers(v));
    return 0;
}