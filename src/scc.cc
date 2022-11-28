#include <bits/stdc++.h>

#define all(v) (v).begin(), (v).end()
#define MAXN 101010

std::vector < int > ed[MAXN], st;
std::vector < std::vector < int > > scc;
int vis[MAXN], fin[MAXN];

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

void get_scc(int n) {
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) dfs(i);
    }
    std::reverse(all(scc));
}

int main() {
    ed[1].push_back(2);
    ed[2].push_back(3);
    ed[3].push_back(1);
    ed[3].push_back(4);
    ed[4].push_back(5);
    ed[5].push_back(6);
    ed[6].push_back(5);
    ed[1].push_back(7);

    get_scc(7);
    for (auto& it : scc) {
        for (auto& jt : it) {
            printf("%d ", jt);
        }
        puts("");
    }
    return 0;
}