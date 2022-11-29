#include <bits/stdc++.h>

#define MAXN 1010
#define S 1009
#define E 1008

std::vector < int > ed[MAXN];
int dp[MAXN], c[MAXN][MAXN], fl[MAXN][MAXN];

int get_max_flow(int src, int dest) {
    int res = 0;
    for (; ;) {
        memset(dp, -1, sizeof dp);
        std::queue < int > q;
        q.push(src); dp[src] = 0;
        for (; !q.empty(); ) {
            int x = q.front(); q.pop();
            for (auto& it : ed[x]) {
                if (dp[it] != -1 || c[x][it] <= fl[x][it]) continue;
                q.push(it); dp[it] = x;
            }
        }
        if (dp[dest] == -1) break;
        int flow = 2147483647;
        for (int i = dest; i != src; i = dp[i]) {
            flow = std::min(flow, c[dp[i]][i] - fl[dp[i]][i]);
        }
        if (flow == 0) break;
        for (int i = dest; i != src; i = dp[i]) {
            fl[dp[i]][i] += flow;
            fl[i][dp[i]] -= flow;
        }
        res += flow;
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