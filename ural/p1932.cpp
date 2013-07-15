#include <cstdio>
#include <iostream>
#include <set>
#include <map>

int trans(char token) {
    if ('0' <= token && token <= '9') {
        return token - '0';
    }
    return token - 'a' + 10;
}

const int N = 70000;
const int S = 16;

char string[N][5];
long long only[S], total[S];
int n;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

void solve_4() {
    std::map<int, int> map;
    for (int i = 0; i < n; ++ i) {
        int hash = 0;
        for (int j = 0; j < 4; ++ j) {
            hash = hash * 16 + trans(string[i][j]);
        }
        map[hash] ++;
    }
    long long total = 0;
    foreach(iter, map) {
        long long x = (*iter).second;
        total += x * (x - 1) / 2;
    }
    only[15] = total;
}

void solve(int count) {
    for (int mask = 0; mask < S; ++ mask) {
        if (__builtin_popcount(mask) == count) {
            std::map<int, int> map;
            for (int i = 0; i < n; ++ i) {
                int hash = 0;
                for (int j = 0; j < 4; ++ j) {
                    if (1 << j & mask) {
                        hash = hash * 16 + trans(string[i][j]);
                    }
                }
                map[hash] ++;
            }
            long long total = 0;
            foreach(iter, map) {
                long long x = (*iter).second;
                total += x * (x - 1) / 2;
            }
            int full_mask = mask ^ (S - 1);
            for (int x = full_mask; x; x = (x - 1) & full_mask) {
                total -= only[mask | x];
            }
            only[mask] = total;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", string[i]);
    }

    solve_4();
    for (int i = 3; i >= 1; -- i) {
        solve(i);
    }

    long long number[5] = {0};
    for (int count = 1; count <= 4; ++ count) {
        for (int mask = 0; mask < S; ++ mask) {
            if (__builtin_popcount(mask) == count) {
                number[count] += only[mask];
            }
        }
    }
    long long answer[5] = {0};
    answer[1] = number[3];
    answer[2] = number[2];
    answer[3] = number[1];
    answer[4] = (long long)n * (n - 1) / 2 - number[1] - number[2] - number[3] - number[4];
    for (int i = 1; i <= 4; ++ i) {
        std::cout << answer[i] << (i == 4 ? '\n' : ' ');
    }
    return 0;
}
