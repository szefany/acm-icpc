#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int N = 100000 + 10;
const int M = N << 1;

int children[M][26], prev[M], step[M], times[N];
int node_count, last;

void clear(int u) {
    memset(children[u], 0, sizeof(children[u]));
    prev[u] = step[u] = 0;
}

void copy_data(int to, int from) {
    memcpy(children[to], children[from], sizeof(children[from]));
    prev[to] = prev[from];
    step[to] = step[from];
}

void initialise() {
    node_count = 1;
    last = 1;
    clear(1);
}

int get_key(char token) {
    return token - 'a';
}

void insert(char token) {
    int key = get_key(token);
    int u = ++ node_count, node;
    clear(u);
    step[u] = step[last] + 1;
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

long long trans(long long x) {
    return x * (x + 1) / 2;
}

char string[N];
int order[M];

int main() {
    scanf("%s", string);
    int n = strlen(string);
    
    initialise();
    for (int i = 0; i < n; ++ i) {
        insert(string[i]);
    }

    for (int i = 1; i <= node_count; ++ i) {
        order[i] = i;
    }
    std::sort(order + 1, order + node_count + 1, cmp);

    for (int i = 0, u = 1; i < n; ++ i) {
        int key = get_key(string[i]);
        while (u && children[u][key] == 0) {
            u = prev[u];
        }
        u = u == 0 ? 1 : children[u][key];
        times[u] ++;
    }
    for (int i = node_count; i >= 1; -- i) {
        int u = order[i];
        times[prev[u]] += times[u];
    }

    long long answer = 0;
    for (int u = 2; u <= node_count; ++ u) {
        answer += (long long)(step[u] - step[prev[u]]) * trans(times[u]);
    }
    std::cout << answer << std::endl;
    return 0;
}
