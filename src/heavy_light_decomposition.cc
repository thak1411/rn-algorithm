#include <bits/stdc++.h>

#define MAXN 101010
#define MAX_LOG 17

typedef std::pair < int, int > pii;
#define f first
#define s second

std::vector < pii > ed[MAXN];
int sz[MAXN], par[MAXN], hroot[MAXN], hv[MAXN], dep[MAXN], ar[MAXN], seg[1 << MAX_LOG + 1];
// sz: subtree size, par: parent, hroot: hld chain root, hv: hld chain element number
// dep: hld chain depth, ar: raw element value, seg: segment tree

int dfs(int x, int c) {
    sz[x] = 1;
    par[x] = c;
    for (auto& it : ed[x]) {
        auto y = it.f; auto d = it.s;
        if (y == c) continue;
        int tmp = dfs(y, x);
        sz[x] += tmp;
        if (ed[x][0].f == c || sz[ed[x][0].f] < tmp) std::swap(ed[x][0], it);
    }
    return sz[x];
}

void hld(int x, int c) {
    static int clock = 1;
    hv[x] = clock++;
    int f = 0;
    for (auto& it : ed[x]) {
        auto y = it.f; auto d = it.s;
        if (y == c) continue;
        if (!f++) {
            hroot[y] = hroot[x];
            dep[y] = dep[x];
        } else {
            hroot[y] = y;
            dep[y] = dep[x] + 1;
        }
        hld(y, x);
    }
}

int main() {
    ed[1].emplace_back(2, 1); ed[2].emplace_back(1, 1);
    ed[1].emplace_back(3, 2); ed[3].emplace_back(1, 2);
    ed[1].emplace_back(4, 3); ed[4].emplace_back(1, 3);
    ed[2].emplace_back(5, 4); ed[5].emplace_back(2, 4);
    ed[2].emplace_back(6, 5); ed[6].emplace_back(2, 5);
    ed[3].emplace_back(7, 6); ed[7].emplace_back(3, 6);

    int root = 1;
    dfs(root, root);
    hroot[root] = root;
    hld(root, root);
    // lca(x, y) ex
    int x = 6, y = 4;
    if (dep[x] < dep[y]) std::swap(x, y);
    for (; dep[x] > dep[y]; ) {
        x = par[hroot[x]];
    }
    for (; hroot[x] != hroot[y]; ) {
        x = par[hroot[x]]; y = par[hroot[y]];
    }
    int lca = std::min(hv[x], hv[y]);
    printf("%d\n", lca);
    return 0;
}