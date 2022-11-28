#include <bits/stdc++.h>

#define MAXN 101010
#define MAX_LOG 18

std::vector < int > ed[MAXN];
int par[MAXN][MAX_LOG], dep[MAXN];

void dfs(int x, int c) {
    par[x][0] = c;
    for (auto& it : ed[x]) {
        if (it == c) continue;
        dep[it] = dep[x] + 1;
        dfs(it, x);
    }
}

void make_sparse(int n) {
    for (int i = 1; i < MAX_LOG; ++i) {
        for (int j = 1; j <= n; ++j) {
            par[j][i] = par[par[j][i - 1]][i - 1];
        }
    }
}

int lca(int p, int q) {
    if (dep[p] > dep[q]) std::swap(p, q);
    int diff = dep[q] - dep[p];
    for (int i = MAX_LOG; i--; ) {
        if (diff & (1 << i)) q = par[q][i];
    }
    if (p == q) return p;
    for (int i = MAX_LOG; i--; ) {
        if (par[p][i] != par[q][i]) {
            p = par[p][i];
            q = par[q][i];
        }
    }
    return par[p][0];
}

int main() {
    ed[1].push_back(2); ed[2].push_back(1);
    ed[1].push_back(3); ed[3].push_back(1);
    ed[2].push_back(4); ed[4].push_back(2);
    ed[2].push_back(5); ed[5].push_back(2);
    ed[3].push_back(6); ed[6].push_back(3);
    dfs(1, 1);
    make_sparse(6);

    printf("%d\n", lca(4, 5)); // 2
    printf("%d\n", lca(4, 6)); // 1
    printf("%d\n", lca(5, 6)); // 1
    printf("%d\n", lca(2, 2)); // 2
    printf("%d\n", lca(3, 6)); // 3
    return 0;
}
