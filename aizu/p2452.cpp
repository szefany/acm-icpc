#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef unsigned long long Long;

const int M = 12;

struct HashMap {
    static const int MAGIC = 131111;
    static const int SIZE = 2000000;

    int first[MAGIC], size;
    int next[SIZE];
    Long key1[SIZE], key2[SIZE];
    int value[SIZE];

    void clear() {
        size = 0;
        memset(first, 0, sizeof(first));
    }

    
    int get_key(Long k1, Long k2) {
        return (k1 + k2) % MAGIC;
        // return (k1 + k2) & (MAGIC - 1);
    }

    
    void add(Long k1, Long k2, Long v) {
        int key = get_key(k1, k2);
        for (int iter = first[key]; iter; iter = next[iter]) {
            if (key1[iter] == k1 && key2[iter] == k2) {
                value[iter] += v;
                return;
            }
        }
        size ++;
        key1[size] = k1;
        key2[size] = k2;
        value[size] = v;
        next[size] = first[key];
        first[key] = size;
    }
};

const int N = 20;

HashMap dp[2];
int amount[M], n, m;
Long answer;


void set_value(Long& contain, int pivot, Long value, int total) {
    Long full = (1ULL << (total << 2)) - 1;
    Long buffer = (15ULL << (pivot << 2)) ^ full;
    contain &= buffer;
    contain |= value << (pivot << 2);
}

bool has_down(int token) {
    return token == 1 || token == 4 || token == 5 || token == 7 || token == 8 || token == 9 || token == 11;
}

bool has_right(int token) {
    return token == 2 || token == 3 || token == 4 || token == 7 || token == 8 || token == 10 || token == 11;
}

bool has_up(int token) {
    return token == 1 || token == 3 || token == 6 || token == 7 || token == 9 || token == 10 || token == 11;
}

bool has_left(int token) {
    return token == 2 || token == 5 || token == 6 || token == 8 || token == 9 || token == 10 || token == 11;
}

void decode(Long mask, int* amount, int* count) {
    std::fill(count, count + m + 1, 0);
    for (int i = 0; i < m + 1; ++ i) {
        amount[i] = mask & 15;
        count[amount[i]] ++;
        mask >>= 4;
    }
}

Long encode_contain(int* amount) {
    Long result = 0;
    for (int i = M - 1; i >= 0; -- i) {
        result = (result << 4) + amount[i];
    }
    return result;
}

int reflect[N];

Long encode_connect(int* state) {
    std::fill(reflect, reflect + m + 2, 0);
    int now = 2;
    Long result = 0;
    for (int i = m; i >= 0; -- i) {
        if (state[i] > 1) {
            if (reflect[state[i]] == 0) {
                reflect[state[i]] = now ++;
            }
            state[i] = reflect[state[i]];
        }
        result = (result << 4) + state[i];
    }
    return result;
}

int state[N], count[N];


void update(int x, int y, int now) {
    int next = now ^ 1;
    dp[next].clear();

    for (int iter = 1; iter <= dp[now].size; ++ iter) {
        Long connect = dp[now].key1[iter];
        Long contain = dp[now].key2[iter];
        Long value = dp[now].value[iter];

        decode(connect, state, count);
        if (count[1] == 0 && x + y) {
            continue;
        }

        int up = connect >> (y << 2) & 15;
        int left = connect >> (m << 2) & 15;

        for (int i = 0; i < M; ++ i) {
            int number = contain >> (i << 2) & 15;
            if (number == 0) {
                continue;
            }
            Long new_contain = contain;
            set_value(new_contain, i, number - 1, M);

            decode(connect, state, count);
            
            int pivot = (x + y == 0) ? 1 : m + 1;
            if (x && state[y] && has_up(i)) {
                pivot = up;
            }
            if (y && state[m] && has_left(i) && state[m] != pivot) {
                int x = std::min(state[m], pivot);
                for (int j = 0; j <= m; ++ j) {
                    if (state[j] == pivot || state[j] == state[m]) {
                        state[j] = x;
                    }
                }
                pivot = x;
            }
            state[y] = has_down(i) ? pivot : 0;
            state[m] = has_right(i) ? pivot : 0;
            dp[next].add(encode_connect(state), new_contain, value);
            if (x == n - 1 && y == m - 1 && pivot == 1) {
                answer += value;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < M; ++ i) {
        scanf("%d", amount + i);
    }

    answer = 0;
    int now = 0;
    dp[now].clear();
    dp[now].add(0, encode_contain(amount), 1);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            update(i, j, now);
            now ^= 1;
        }
    }
    std::cout << answer << std::endl;
    return 0;
}
