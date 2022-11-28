#include <bits/stdc++.h>

#define f first
#define s second
#define all(v) (v).begin(), (v).end()
typedef long long ll;
typedef std::pair < int, int > pii;
typedef std::pair < ll, ll > pll;
#define f first
#define s second

ll ccw(pll i, pll j, pll k) {
    return (i.f * j.s + i.s * k.f + j.f * k.s)
        - (j.f * i.s + j.s * k.f + k.s * i.f);
}

int point_in_convex_polygon(std::vector < pll >& ch, pll pt, int include_line) {
    if (ch.size() == 0) return 0;
    if (ch.size() == 1) return include_line && ch[0] == pt;
    // if (ch.size() == 2) return include_line && intersect(ch[0], ch[1], pt, pt);
    int l = 1, r = ch.size() - 2, f = 1;
    for (; l < r; ) {
        int m = l + r + 1 >> 1;
        ll cw = ccw(ch[0], ch[m], pt);
        if (cw >= 0) l = m;
        else r = m - 1;
    }
    if (l == 1) {
        if (ccw(ch[0], ch[1], pt) + include_line <= 0) f = 0;
    } else if (l == ch.size() - 2) {
        if (ccw(ch[0], ch[ch.size() - 1], pt) - include_line >= 0) f = 0;
    }
    if (ccw(ch[0], ch[l], pt) < 0) f = 0;
    if (ccw(ch[l], ch[l + 1], pt) + include_line <= 0) f = 0;
    if (ccw(ch[l + 1], ch[0], pt) < 0) f = 0;
    return f;
}

int main() {
    // sorted by ccw
    std::vector < pll > ch;
    ch.emplace_back(0, 0);
    ch.emplace_back(10, 0);
    ch.emplace_back(10, 10);
    ch.emplace_back(0, 10);
    printf("%d\n", point_in_convex_polygon(ch, {0, 0}, 0));
    printf("%d\n", point_in_convex_polygon(ch, {0, 0}, 1));
    printf("%d\n", point_in_convex_polygon(ch, {9, 1}, 0));
    printf("%d\n", point_in_convex_polygon(ch, {1, 9}, 1));
    return 0;
}