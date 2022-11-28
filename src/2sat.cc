#include <bits/stdc++.h>

#define all(v) (v).begin(), (v).end()
#define MAXN 101010
#define OFFSET (MAXN + 1)

typedef std::pair < int, int > pii;

std::vector < int > ed[MAXN * 2 + 4], st;
std::vector < std::vector < int > > scc;
int vis[MAXN * 2 + 4], fin[MAXN * 2 + 4], mem[MAXN * 2 + 4];

int dfs(int x) {
    static int cnt = 1;
    int res = cnt;
    vis[x] = cnt++;
    st.push_back(x);

    for (auto& it : ed[x]) {
        if (!vis[it]) res = std::min(res, dfs(it));
        else if (!fin[it]) res = std::min(res, vis[it]);
    }
    if (res == vis[x]) {
        std::vector < int > tmp;
        for (; ;) {
            int t = st.back(); st.pop_back();
            tmp.push_back(t);
            fin[t] = scc.size() + 1;
            if (t == x) break;
        }
        std::reverse(all(tmp));
        scc.push_back(tmp);
    }
    return res;
}

int twosat(int n) {
    for (int i = 1; i <= n; ++i) {
        if (!vis[OFFSET + i]) dfs(OFFSET + i);
        if (!vis[OFFSET - i]) dfs(OFFSET - i);
    }
    int res = 1;
    for (int i = 1; i <= n; ++i) res &= fin[OFFSET + i] != fin[OFFSET - i];
    return res;
}

std::vector < int > backtrack(int n) {
    std::vector < int > res;
    std::reverse(all(scc));
    memset(mem, -1, sizeof mem);
    for (auto& it : scc) {
        for (auto& jt : it) {
            if (mem[jt] == -1) mem[jt] = 0, mem[OFFSET * 2 - jt] = 1;
        }
    }
    for (int i = 1; i <= n; ++i) res.push_back(mem[OFFSET + i]);
    return res;
}

int main() {
    // (a v b) ^ (a v c) ^ (!c v d)
    // a: 1, b: 2, c: 3, d: 4 / !a = -1, !b = -2, !c = -3, !d = -4
    ed[OFFSET - 1].push_back(OFFSET + 2); // !a -> b
    ed[OFFSET - 2].push_back(OFFSET + 1); // !b -> a
    ed[OFFSET - 1].push_back(OFFSET + 3); // !a -> c
    ed[OFFSET - 3].push_back(OFFSET + 1); // !c -> a
    ed[OFFSET + 3].push_back(OFFSET + 4); // !!c -> d
    ed[OFFSET - 4].push_back(OFFSET - 3); // !d -> !c
    int res = twosat(3);
    printf("%d\n", res);
    if (!res) return 0;
    auto t = backtrack(3);
    for (auto& it : t) printf("%d ", it); puts(""); // a b c
    return 0;
}