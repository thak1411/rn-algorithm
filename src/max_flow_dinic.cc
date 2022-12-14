#include <bits/stdc++.h>

#define MAXN 1010
#define S 1009
#define E 1008

std::vector < int > ed[MAXN];
int dp1[MAXN], dp2[MAXN], c[MAXN][MAXN], fl[MAXN][MAXN];

int bfs(int x, int dest) {
    memset(dp1, 0, sizeof dp1);
    memset(dp2, 0, sizeof dp2);
    std::queue < int > q;
    q.push(x); dp1[x] = 1;
    for (; !q.empty(); ) {
        x = q.front(); q.pop();
        for (auto& it : ed[x]) {
            if (dp1[it] || c[x][it] <= fl[x][it]) continue;
            q.push(it); dp1[it] = dp1[x] + 1;
        }
    }
    return dp1[dest] > 0;
}

int dfs(int x, int f, int dest) {
    if (x == dest) return f;
    for (; dp2[x] < ed[x].size(); ++dp2[x]) {
        int it = ed[x][dp2[x]];
        if (dp1[it] != dp1[x] + 1 || c[x][it] <= fl[x][it]) continue;
        int flow = dfs(it, std::min(f, c[x][it] - fl[x][it]), dest);
        if (flow > 0) {
            fl[x][it] += flow;
            fl[it][x] -= flow;
            return flow;
        }
    }
    return 0;
}

int get_max_flow(int src, int dest) {
    int res = 0;
    for (; bfs(src, dest); ) {
        int flow = 0;
        for (; (flow = dfs(src, 2147483647, dest)); ) res += flow;
    }
    return res;
}

void add(int p, int q, int cap) {
    ed[p].push_back(q); c[p][q] += cap;
    ed[q].push_back(p);
}

int main() {
    add(S, 1, 2);
    add(S, 2, 10);
    add(1, 2, 1);
    add(2, 3, 9);
    add(2, 4, 100);
    add(3, 4, 10);
    add(4, E, 1000);
    printf("%d\n", get_max_flow(S, E));
    return 0;
}