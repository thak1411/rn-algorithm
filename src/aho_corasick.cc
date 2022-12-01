#include <bits/stdc++.h>

#define MAXNODE 1010101
#define NEXTSZ 26
#define MAXN 101010

int trie[MAXNODE][NEXTSZ], fin[MAXNODE], fail[MAXNODE], ts;

int conv(char c) {
    return c - 'a';
}

void init(std::vector < std::string >& words) {
    for (auto& it : words) {
        int p = 0;
        for (auto& jt : it) {
            if (!trie[p][conv(jt)]) trie[p][conv(jt)] = ++ts;
            p = trie[p][conv(jt)];
        }
        fin[p] = 1;
    }
    std::queue < int > q;
    for (int i = 0; i < NEXTSZ; ++i) {
        if (trie[0][i]) q.push(trie[0][i]);
    }
    for (; !q.empty(); ) {
        int x = q.front(); q.pop();
        for (int i = 0; i < NEXTSZ; ++i) {
            if (!trie[x][i]) continue;
            int p = fail[x];
            for (; p && !trie[p][i]; ) p = fail[p];
            p = trie[p][i];
            fail[trie[x][i]] = p;
            fin[trie[x][i]] |= fin[p];
            q.push(trie[x][i]);
        }
    }
}

int query(std::string& s) {
    int p = 0;
    for (auto& it : s) {
        for (; p && !trie[p][conv(it)]; ) p = fail[p];
        p = trie[p][conv(it)];
        if (fin[p]) return 1;
    }
    return 0;
}

int main() {
    std::vector < std::string > w;
    w.emplace_back("www");
    w.emplace_back("woo");
    w.emplace_back("jun");
    init(w);
    std::string s = "myungwoo";
    printf("%d\n", query(s)); // 1
    s = "hongjun";
    printf("%d\n", query(s)); // 1
    s = "dooho";
    printf("%d\n", query(s)); // 0
    return 0;
}