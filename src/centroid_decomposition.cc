#include <bits/stdc++.h>

typedef std::pair < int, int > pii;
#define f first
#define s second

std::vector < pii > ed[202020];
int sz[202020], use[202020];

void dfs(int x, int c) {
    sz[x] = 1;
    for (auto& it : ed[x]) {
        if (it.f == c || use[it.f]) continue;
        dfs(it.f, x);
        sz[x] += sz[it.f];
    }
}

int cent(int x, int c, int w) {
    for (auto& it : ed[x]) {
        if (it.f == c || use[it.f]) continue;
        if (sz[it.f] > w) return cent(it.f, x, w);
    }
    return x;
}

void query(int x) {
    if (use[x]) return;
    dfs(x, x);
    int ct = cent(x, x, sz[x] / 2);
    use[ct] = 1;
    // some query
    printf("ct: %d\n", ct);
    // some query
    for (auto& it : ed[ct]) query(it.f);
}

int main() {
    ed[0].emplace_back(1, 1); ed[1].emplace_back(0, 1);
    ed[1].emplace_back(2, 2); ed[2].emplace_back(1, 2);
    ed[1].emplace_back(3, 4); ed[3].emplace_back(1, 4);
    
    query(0);
    return 0;
}