// Codeforces Beta Round #11
// Problem D, A Simple Task
#include <iostream>
#include <cstdio>

const int N = 19;
const int S = 1 << N;

bool g[N][N];
long long number[S][N];
int n, m;

int main () {
    scanf ("%d%d", &n, &m);
    while (m --) {
        int u, v;
        scanf ("%d%d", &u, &v);
        u --, v --;
        g[u][v] = g[v][u] = true;
    }
    for (int i = 0; i < n; ++ i) {
        number[1 << i][i] = 1;
    }
    long long answer = 0;
    for (int mask = 0; mask < 1 << n; ++ mask) {
        int start = __builtin_ctz (mask);
        for (int i = 0; i < n; ++ i) {
            if (mask & 1 << i && number[mask][i]) {
                if (g[i][start] && __builtin_popcount (mask) > 2) {
                    answer += number[mask][i];
                }
                for (int j = start + 1; j < n; ++ j) {
                    if (!(1 << j & mask) && g[i][j]) {
                        number[mask | 1 << j][j] += number[mask][i];
                    }
                }
            }
        }
    }
    std::cout << (answer >> 1) << std::endl;
    return 0;
}
