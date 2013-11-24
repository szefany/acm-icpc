#include <cstdio>
#include <cstring>
#include <iostream>
 
using std::max;
 
const int S = 1 << 16;
 
int bit_count[S];
 
struct HashMap {
    static const int MAGIC = 16384;
    static const int SIZE = 200000;
 
    int first[MAGIC], size;
    int next[SIZE], key[SIZE], value[SIZE];
     
    void clear() {
        memset(first, -1, sizeof(first));
        size = 0;
    }
 
    void update(int k, int v) {
        int hash = k & 16383;
        for (int iter = first[hash]; iter != -1; iter = next[iter]) {
            if (k == key[iter]) {
                value[iter] = max(value[iter], v);
                return;
            }
        }
        key[size] = k;
        value[size] = v;
        next[size] = first[hash];
        first[hash] = size ++;
    }
};
 
const int N = 130;
 
char string[N][20];
int length[N];
int n, m;
HashMap dp[2];
 
void update(int x, int y, int now) {
    int full_mask = (1 << m) - 1;
    int next = now ^ 1;
    dp[next].clear();
    for (int iter = 0; iter < dp[now].size; ++ iter) {
        int mask = dp[now].key[iter];
        int value = dp[now].value[iter];
 
        int current = bit_count[mask & ((1 << y) - 1)];
        int last = bit_count[mask] - current;
        // 0:
        if (m - 1 - y + current >= length[x]) {
            int new_mask = mask & (full_mask ^ (1 << y));
            dp[next].update(new_mask, value);
        }
 
        // 1:
        if (current + 1 <= length[x]) {
            int new_value = value;
            if (x && (mask & 1 << y)) {
                int pivot = length[x - 1] - last;
                if (string[x - 1][pivot] == string[x][current]) {
                    new_value += 2;
                }
            }
            if (y && (mask & 1 << (y - 1))) {
                if (string[x][current - 1] == string[x][current]) {
                    new_value += 2;
                }
            }
 
            int new_mask = mask | (1 << y);
            dp[next].update(new_mask, new_value);
        }
    }
}
 
int main() {
    for (int i = 0; i < S; ++ i) {
        bit_count[i] = __builtin_popcount(i);
    }
 
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", string[i]);
        length[i] = strlen(string[i]);
    }
 
    int now = 0;
    dp[now].clear();
    dp[now].update(0, 0);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            update(i, j, now);
            now ^= 1;
        }
    }
     
    int answer = 0;
    for (int iter = 0; iter < dp[now].size; ++ iter) {
        answer = max(answer, dp[now].value[iter]);
    }
    printf("%d\n", answer);
    return 0;
}
