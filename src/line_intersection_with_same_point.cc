#include <bits/stdc++.h>

typedef long long ll;

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    bool operator<= (Point p) {
        return x == p.x ? y <= p.y : x <= p.x;
    }
};

struct Line {
    Point s, e;
    Line() {}
    Line(int x1, int y1, int x2, int y2) : s(x1, y1), e(x2, y2) { }
};

int ccw(Point i, Point j, Point k) {
    ll cw = 1LL * i.x * j.y + 1LL * i.y * k.x + 1LL * j.x * k.y - (1LL * i.x * k.y + 1LL * i.y * j.x + 1LL * j.y * k.x);
    return cw > 0 ? 1 : cw < 0 ? -1 : 0;
}

int intersect(Line i, Line j) {
    int a = ccw(i.s, i.e, j.s) * ccw(i.s, i.e, j.e), b = ccw(j.s, j.e, i.s) * ccw(j.s, j.e, i.e);
    if (a == 0 && b == 0) {
        if (i.e <= i.s) std::swap(i.e, i.s);
        if (j.e <= j.s) std::swap(j.e, j.s);
        return i.s <= j.e && j.s <= i.e;
    }
    return a <= 0 && b <= 0;
}

int main() {
    std::vector < Line > v;
    v.emplace_back(1, 1, 5, 5); // (1, 1) - (5, 5)
    v.emplace_back(1, 5, 5, 1); // (1, 5) - (5, 1)

    v.emplace_back(1, 1, 5, 5); // (1, 1) - (5, 5)
    v.emplace_back(6, 10, 10, 6); // (6, 10) - (10, 6)

    v.emplace_back(1, 1, 5, 5); // (1, 1) - (5, 5)
    v.emplace_back(5, 5, 1, 1); // (5, 5) - (1, 1)

    printf("%d\n%d\n%d\n", intersect(v[0], v[1]), intersect(v[2], v[3]), intersect(v[4], v[5]));
    return 0;
}