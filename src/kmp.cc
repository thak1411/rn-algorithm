#include <bits/stdc++.h>

#define MAXN 101010

char str[MAXN], target[MAXN];
int pi[MAXN];

void getPi(int m) {
    for (int i = 1, mat = 0; i < m; ++i) {
        if (target[i] == target[mat]) {
            pi[i] = ++mat;
        } else if(mat != 0) {
            --i;
            mat = pi[mat - 1];
        }
    }
}

int kmp(int n, int m) {
    for (int i = 0, mat = 0; i < n; ++i) {
        if (str[i] == target[mat]) {
            if (++mat == m) {
                return i - m + 1;
                mat = pi[mat - 1];
            }
        } else if (mat != 0) {
            --i;
            mat = pi[mat - 1];
        }
    }
    return -1;
}

int main() {
    strcpy(str, "ABC ABCDAB ABCDABCDABDE");
    strcpy(target, "ABCDABD");
    int n = strlen(str), m = strlen(target);
    getPi(m);
    printf("%d\n", kmp(n, m));
    return 0;
}