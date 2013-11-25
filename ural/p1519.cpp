#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cassert>

typedef unsigned long long Long;

struct HashMap {
    static const int MAGIC = 30001;
    static const int SIZE = 200000;

    int first[MAGIC], size;
    int next[SIZE];
    Long key[SIZE], value[SIZE];

    void clear() {
        size = 0;
        memset(first, 0, sizeof(first));
    }

    
    void add(Long k, Long v) {
        int hash = k * 131 % MAGIC;
        for (int iter = first[hash]; iter; iter = next[iter]) {
            if (key[iter] == k) {
                value[iter] += v;
                return;
            }
        }
        size ++;
        key[size] = k;
        value[size] = v;
        next[size] = first[hash];
        first[hash] = size;
    }
};

const int N = 15;

char map[N][N];
HashMap dp[2];
int n, m, ex, ey;
Long answer;

int get_value(Long mask, int pivot) {
    return mask >> (pivot * 3) & 7;
}

void set_value(Long& mask, int pivot, int value) {
    static Long full_mask = (1ULL << ((m + 1) * 3)) - 1;
    Long buffer = (7ULL << (pivot * 3)) ^ full_mask;
    mask &= buffer;
    mask |= (Long)value << (pivot * 3);
}

int count[N];

void merge(Long& mask, int a, int b) {
    if (a > b) {
        std::swap(a, b);
    }
    for (int i = 0; i <= m; ++ i) {
        int num = get_value(mask, i);
        if (num == b) {
            set_value(mask, i, a);
        }
    }
}

int code[N];


void decode(Long mask, int* code) {
    for (int i = 0; i <= m; ++ i) {
        code[i] = mask & 7;
        mask >>= 3;
    }
}

int reflect[N];

inline Long encode(int* code) {
    std::fill(reflect, reflect + m, 0);
    int now = 1;
    Long result = 0;
    for (int i = m; i >= 0; -- i) {
        if (code[i] && reflect[code[i]] == 0) {
            reflect[code[i]] = now ++;
        }
        code[i] = reflect[code[i]];
        result = (result << 3) + code[i];
    }
    return result;
}


void update(int x, int y, int now) {
    int next = now ^ 1;
    dp[next].clear();

    if (map[x][y] == '*') {
        for (int iter = 1; iter <= dp[now].size; ++ iter) {
            Long mask = dp[now].key[iter];
            Long value = dp[now].value[iter];
            decode(mask, code);
            code[y] = code[m] = 0;
            dp[next].add(encode(code), value);
        }
    } else {
        for (int iter = 1; iter <= dp[now].size; ++ iter) {
            Long mask = dp[now].key[iter];
            Long value = dp[now].value[iter];
            decode(mask, code);
            int up = code[y];
            int left = code[m];

            if (up && left) {
                if (up == left) {
                    if (x == ex && y == ey) {
                        answer += value;
                    }
                } else {
                    int x = std::min(up, left);
                    for (int i = 0; i <= m; ++ i) {
                        if (code[i] == up || code[i] == left) {
                            code[i] = x;
                        }
                    }
                    code[y] = code[m] = 0;
                    dp[next].add(encode(code), value);
                }
            } else if (up) {
                if (x + 1 < n && map[x + 1][y] != '*') { // up_down
                    code[m] = 0;
                    dp[next].add(encode(code), value);
                }
                if (y + 1 < m && map[x][y + 1] != '*') { // up_right
                    code[m] = up, code[y] = 0;
                    dp[next].add(encode(code), value);
                }
            } else if (left) {
                if (y == 0) {
                    continue;
                }
                if (y + 1 < m && map[x][y + 1] != '*') { // left_right
                    code[m] = left;
                    code[y] = 0;
                    dp[next].add(encode(code), value);
                }
                if (x + 1 < n && map[x + 1][y] != '*') { // left_down
                    code[m] = 0;
                    code[y] = left;
                    dp[next].add(encode(code), value);
                }
            } else if (x + 1 < n && y + 1 < m && map[x + 1][y] != '*' && map[x][y + 1] != '*') {
                code[y] = code[m] = m - 1;
                dp[next].add(encode(code), value);
            }
        }
    }
}


int main() {
    freopen("input", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", map[i]);
        for (int j = 0; j < m; ++ j) {
            if (map[i][j] != '*') {
                ex = i;
                ey = j;
            }
        }
    }

    int now = 0;
    dp[now].clear();
    dp[now].add(0, 1);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            update(i, j, now);
            now ^= 1;
        }
    }
    std::cout << answer << std::endl;
    return 0;
}
