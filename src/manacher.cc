#include <bits/stdc++.h>

#define MAXN 1010101

char str[MAXN], ar[MAXN * 2];
int res[MAXN * 2];

int manacher(int n) {
    ar[0] = str[0];
    for (int i = 1; i < n; ++i) {
        ar[i * 2 - 1] = '#';
        ar[i * 2] = str[i];
    }
    int p = 0, c = 0;
    int max_pal = 0;
    for (int i = 0; i < n * 2 - 1; ++i) {
        int pc = 0;
        if (i <= p) pc = std::min(res[c * 2 - i], p - i);
        for (; i - pc - 1 >= 0 && i + pc + 1 < 2 * n - 1 && ar[i - pc - 1] == ar[i + pc + 1]; ++pc);
        res[i] = pc;
        if (i + pc > p) {
            p = i + pc;
            c = i;
        }
        max_pal = std::max(max_pal, res[i] + 1 - ((res[i] % 2) ^ (i % 2)));
    }
    return max_pal;
}

int main() {
    strcpy(str, "abacaba");
    printf("%d\n", manacher(7));
    strcpy(str, "abacabaaaabb");
    printf("%d\n", manacher(12));
    return 0;
}