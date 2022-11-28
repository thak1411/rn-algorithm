#include <bits/stdc++.h>

#define MAXN 1010
#define S 1009
#define E 1008

std::vector < int > ed[MAXN];
int dp[MAXN], c[MAXN][MAXN], fl[MAXN][MAXN];

int get_max_flow() {
    int res = 0;
    for (; ;) {
        memset(dp, -1, sizeof dp);
        std::queue < int > q;
        q.push(S); dp[S] = 0;
        for (; !q.empty(); ) {
            int x = q.front(); q.pop();
            for (auto& it : ed[x]) {
                if (dp[it] != -1 || c[x][it] <= fl[x][it]) continue;
                q.push(it); dp[it] = x;
            }
        }
        if (dp[E] == -1) break;
        int flow = 2147483647;
        for (int i = E; i != S; i = dp[i]) {
            flow = std::min(flow, c[dp[i]][i] - fl[dp[i]][i]);
        }
        if (flow == 0) break;
        for (int i = E; i != S; i = dp[i]) {
            fl[dp[i]][i] += flow;
            fl[i][dp[i]] -= flow;
        }
        res += flow;
    }
    return res;
}

int main() {
    ed[S].push_back(1); ed[1].push_back(S); c[S][1] = 2;
    ed[S].push_back(2); ed[2].push_back(S); c[S][2] = 10;
    ed[1].push_back(2); ed[2].push_back(1); c[1][2] = 1;
    ed[2].push_back(3); ed[3].push_back(2); c[2][3] = 9;
    ed[2].push_back(4); ed[4].push_back(2); c[2][4] = 100;
    ed[3].push_back(4); ed[4].push_back(3); c[3][4] = 10;
    ed[4].push_back(E); ed[E].push_back(4); c[4][E] = 1000;
    printf("%d\n", get_max_flow());
    return 0;
}