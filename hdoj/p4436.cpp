#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>

const int N = 200000 + 10;
const int M = N << 1;

int children[M][11], prev[M], step[M], order[M], links[M], value[M], front[M];
int node_count, last;

void clear(int u) {
    memset(children[u], 0, sizeof(children[u]));
    prev[u] = step[u] = links[u] = value[u] = front[u] = 0;
}

void copy_data(int to, int from) {
    memcpy(children[to], children[from], sizeof(children[from]));
    prev[to] = prev[from];
    step[to] = step[from];
    links[to] = links[from];
    value[to] = value[from];
    front[to] = front[from];
}

void initialise() {
    node_count = 1;
    last = 1;
    clear(1);
}

int get_key(char token) {
    return token == '#' ? 10 : token - '0';
}

void insert(char token) {
    int key = get_key(token);
    int u = ++ node_count, node;
    clear(u);
    step[u] = step[last] + 1;
    links[u] = key;
    for (node = last; node && children[node][key] == 0; node = prev[node]) {
        children[node][key] = u;
    }
    if (node == 0) {
        prev[u] = 1;
    } else {
        int v = children[node][key];
        if (step[v] == step[node] + 1) {
            prev[u] = v;
        } else {
            int nv = ++ node_count;
            copy_data(nv, v);
            step[nv] = step[node] + 1;
            prev[u] = prev[v] = nv;
            for (; node && children[node][key] == v; node = prev[node]) {
                children[node][key] = nv;
            }
        }
    }
    last = u;
}

bool cmp(int a, int b) {
    return step[a] < step[b];
}

const int MOD = 2012;

int n;

int main() {
    std::ios::sync_with_stdio(false);
    while (std::cin >> n) {
        initialise();
        for (int i = 1; i <= n; ++ i) {
            std::string string;
            std::cin >> string;
            for (int j = 0; j < string.length(); ++ j) {
                insert(string[j]);
            }
            insert('#');
        }

        for (int i = 1; i <= node_count; ++ i) {
            order[i] = i;
        }
        std::sort(order + 1, order + node_count + 1, cmp);

        int answer = 0;
        front[1] = 1;
        
        for (int i = 1; i <= node_count; ++ i) {
            int u = order[i];
            if (links[u] == 10) {
                continue;
            }
            for (int key = 0; key <= 9; ++ key) {
                int v = children[u][key];
                if (u == 1 && key == 0) {
                    continue;
                }
                if (v) {
                    (front[v] += front[u]) %= MOD;
                }
            }
        }

        for (int i = 1; i <= node_count; ++ i) {
            int u = order[i];
            if (links[u] == 10) {
                continue;
            }
            int times = front[u] % MOD;
            int temp = times * links[u] % MOD;
            (value[u] += temp) %= MOD;
            (answer += value[u]) %= MOD;
            for (int key = 0; key <= 9; ++ key) {
                int v = children[u][key];
                if (v) {
                    (value[v] += value[u] * 10) %= MOD;
                }
            }
        }
/*
        for (int u = 1; u <= node_count; ++ u) {
            printf("%d: ", u);
            for (int i = 0; i <= 9; ++ i) {
                int v = children[u][i];
                if (v) {
                    printf("(%d, %d)", i, v);
                }
            }
            printf("%d %d %d\n", front[u], rear[u], value[u]);
        }
*/
        printf("%d\n", answer);
    }
    return 0;
}
