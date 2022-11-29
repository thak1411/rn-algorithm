#include <bits/stdc++.h>

typedef long long ll;
typedef std::pair < ll, ll > pll;
#define f first
#define s second

#define MAXN 1010
std::vector < int > ed[MAXN];
int l[MAXN], r[MAXN], dist[MAXN], vis[MAXN];

int bfs(int n) {
    int ok = 0;
    std::queue < int > q;
    memset(dist, -1, sizeof dist);
    for (int i = 0; i < n; ++i) {
        if (l[i] != -1) continue;
        q.push(i); dist[i] = 0;
    }
    for (; !q.empty(); ) {
        int t = q.front(); q.pop();
        for (auto& it : ed[t]) {
            if (r[it] == -1) ok = 1;
            else if (dist[r[it]] == -1) {
                q.push(r[it]); dist[r[it]] = dist[t] + 1;
            }
        }
    }
    return ok;
}
 
int dfs(int x) {
    if (vis[x]++) return 0;
    for (auto& it : ed[x]) {
        if (r[it] == -1 || (dist[r[it]] == dist[x] + 1 && dfs(r[it]))) {
            l[x] = it;
            r[it] = x;
            return 1;
        }
    }
    return 0;
}
 
int bipartite_matching(int n) {
    int res = 0;
    memset(l, -1, sizeof l);
    memset(r, -1, sizeof r);
    for (; bfs(n); ) {
        memset(vis, 0, sizeof vis);
        for (int i = 0; i < n; ++i) if (l[i] == -1 && dfs(i)) ++res;
    }
    return res;
}

int main() {
    int n = 5;
    // 0 0
    // 1 1
    // 2 2
    // 3 3
    // 4
    ed[0].push_back(0);
    ed[1].push_back(0);
    ed[2].push_back(2);
    ed[2].push_back(3);
    ed[3].push_back(2);
    ed[4].push_back(3);
    printf("%d\n", bipartite_matching(n));
    return 0;
}