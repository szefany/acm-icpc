#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 600000;
const int M = 26;

int children[N][M], prev[N], step[N], times[N], rank[N];
int node_count, last;

void clear(int u) {
    memset(children[u], 0, sizeof(children[u]));
    prev[u] = step[u] = times[u] = 0;
}

void copy_data(int from, int to) {
    memcpy(children[to], children[from], sizeof(children[from]));
    prev[to] = prev[from];
    step[to] = step[from];
    times[to] = times[from];
}

void insert(int key) {
    clear(++ node_count);
    int u = node_count, node;
    step[u] = step[last] + 1;
    times[u] = 1;
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
            copy_data(v, nv);
            step[nv] = step[node] + 1;
            prev[u] = prev[v] = nv;
            for (; node && children[node][key] == v; node = prev[node]) {
                children[node][key] = nv;
            }
        }
    }
    last = u;
}

void build(char* string) {
    node_count = last = 1;
    clear(1);
    int length = strlen(string);
    for (int i = 0; i < length; ++ i) {
        insert(string[i] - 'a');
    }
}

bool cmp(int a, int b) {
    return step[a] < step[b];
}

char string[N];
int n, m, k;

int main() {
    while (scanf("%d%d%d", &n, &m, &k) != EOF) {
        scanf("%s", string);
        build(string);

        memset(times, 0, sizeof(times));
        for (int i = 0, u = 1; i < n; ++ i) {
            int key = string[i] - 'a';
            u = children[u][key];
            times[u] ++;
        }
        for (int i = 1; i <= node_count; ++ i) {
            rank[i] = i;
        }
        std::sort(rank + 1, rank + node_count + 1, cmp);
        int answer = 0;
        for (int i = node_count; i > 1; -- i) {
            int u = rank[i];
            times[prev[u]] += times[u];
            if (times[u] >= k) {
                answer += step[u] - step[prev[u]];
            }
        }

        while (m --) {
            int command;
            scanf("%d", &command);
            if (command == 2) {
                printf("%d\n", answer);
            } else {
                char buffer[2];
                scanf("%s", buffer);
                insert(*buffer - 'a');
                for (int u = last; u != 1; u = prev[u]) {
                    times[prev[u]] ++;
                    if (times[u] == k) {
                        answer += step[u] - step[prev[u]];
                    }
                }
            }
        }
    }
    return 0;
}
