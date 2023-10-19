#include <bits/stdc++.h>

#define MAXN 505050

char str[MAXN];
int n, sfa[MAXN], ord[MAXN], nord[MAXN], cnt[MAXN], tn[MAXN], lcp[MAXN];

void init() {
    for (int i = 0; i <= n; ++i) {
        sfa[i] = i;
        ord[i] = str[i];
    }
}

void getSA() {
    for (int sz = 1; sz <= n; sz <<= 1) {
        auto f = [&] (int i, int j) -> bool {
            if (ord[i] != ord[j]) return ord[i] < ord[j];
            i += sz; j += sz;
            return i < n && j < n ? ord[i] < ord[j] : i > j;
        };
        memset(cnt, 0, sizeof(int) * std::max(256, n + 1));
        for (int i = 0; i < n; ++i) ++cnt[ord[std::min(i + sz, n)]];
        for (int i = 1; i <= n || i <= 255; ++i) cnt[i] += cnt[i - 1];
        for (int i = n; i--; ) tn[--cnt[ord[std::min(i + sz, n)]]] = i;
        memset(cnt, 0, sizeof(int) * std::max(256, n + 1));
        for (int i = 0; i < n; ++i) ++cnt[ord[i]];
        for (int i = 1; i <= n || i <= 255; ++i) cnt[i] += cnt[i - 1];
        for (int i = n; i--; ) sfa[--cnt[ord[tn[i]]]] = tn[i];
        nord[sfa[0]] = 1;
        for (int i = 1; i < n; ++i) {
            nord[sfa[i]] = nord[sfa[i - 1]] + f(sfa[i - 1], sfa[i]);
        }
        memcpy(ord, nord, sizeof(int) * n);
    }
    for (int i = n; i--; ) --ord[i];
}

void getLCP() {
    for (int i = 0, k = 0; i < n; ++i, k = std::max(k - 1, 0)) {
        if (ord[i] == 0) continue;
        for (int j = sfa[ord[i] - 1]; str[i + k] == str[j + k]; ) ++k;
        lcp[ord[i]] = k;
    }
}

int main() {
    scanf("%s", str); // abracadabra
    n = strlen(str);

    init(); getSA(); getLCP();

    for (int i = 0; i < n; ++i) printf("%d ", sfa[i] + 1); puts("");
    // 11 8 1 4 6 9 2 5 7 10 3
    for (int i = 1; i < n; ++i) printf("%d ", lcp[i]); puts("");
    //  _ 1 4 1 1 0 3 0 0  0 2
    return 0;
}
