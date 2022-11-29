#include <bits/stdc++.h>

#define MAXN 111

#define S 110
#define E 109

std::vector < int > ed[MAXN];
int c[MAXN][MAXN], fl[MAXN][MAXN], cost[MAXN][MAXN], inque[MAXN], dist[MAXN], dp[MAXN];

int spfa(int src, int dest) {
    memset(dist, 0x3f, sizeof dist);
    memset(inque, 0, sizeof inque);
    std::queue < int > q;
    q.push(src); dist[src] = 1; inque[src] = 1;
    int ok = 0;
    for (; !q.empty(); ) {
        int x = q.front(); q.pop();
        inque[x] = 0;
        ok |= x == dest;
        for (auto& it : ed[x]) {
            if (dist[it] <= dist[x] + cost[x][it] || c[x][it] <= fl[x][it]) continue;
            dist[it] = dist[x] + cost[x][it];
            dp[it] = x;
            if (!inque[it]) {
                q.push(it); inque[it] = 1;
            }
        }
    }
    return ok;
}

int get_min_cost_max_flow(int src, int dest) {
    int res = 0;
    for (; spfa(src, dest); ) {
        int flow = 2147483647;
        for (int i = dest; i != src; i = dp[i]) {
            flow = std::min(flow, c[dp[i]][i] - fl[dp[i]][i]);
        }
        res += dist[dest] * flow;
        for (int i = dest; i != src; i = dp[i]) {
            fl[dp[i]][i] += flow;
            fl[i][dp[i]] -= flow;
        }
    }
    return res;
}

void add(int p, int q, int cap, int cst) {
    ed[p].push_back(q); c[p][q] += cap; cost[p][q] += -cst;
    ed[q].push_back(p); c[q][p] += 0; cost[q][p] += cst;
}

int main() {
    add(S, 1, 2, 10);
    add(S, 2, 10, 11);
    add(1, 2, 1, 12);
    add(2, 3, 9, 13);
    add(2, 4, 100, 14);
    add(3, 4, 10, 15);
    add(4, E, 1000, 16);
    printf("%d\n", get_min_cost_max_flow(S, E));
    return 0;
}