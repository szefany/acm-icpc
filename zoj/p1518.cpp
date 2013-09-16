#include <cstdio>
#include <cstring>
#include <vector>

const int N = 2000 + 10;

std::vector<int> neighbors[N];
int ancestor[N], value[N];
int n;

int find(int u) {
    return ancestor[u] == u ? u : ancestor[u] = find(ancestor[u]);
}

void joint(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) {
        ancestor[u] = v;
        value[v] += value[u];
    }
}

bool visit[N];

int main() {
    while (scanf("%d", &n) != EOF && n > 0) {
        memset(ancestor, 0, sizeof(ancestor));
        memset(value, 0, sizeof(value));
        for (int i = 1; i <= n + n; ++ i) {
            ancestor[i] = i;
            value[i] = i <= n;
        }
        for (int i = 1; i <= n; ++ i) {
            char buffer[10];
            int x;
            scanf("%*s %d %*s %s", &x, buffer);
            int delta = *buffer == 't' ? 0 : n;
            joint(i, x + delta);
            joint(i + n, x + n - delta);
        }
        bool flag = true;
        for (int i = 1; i <= n; ++ i) {
            flag &= find(i) != find(i + n);
        }
        if (!flag) {
            puts("Inconsistent");
        } else {
            memset(visit, 0, sizeof(visit));
            int answer = 0;
            for (int i = 1; i <= n; ++ i) {
                int x = find(i);
                int y = find(i + n);
                if (!visit[x] && !visit[y]) {
                    answer += std::max(value[x], value[y]);
                    visit[x] = visit[y] = true;
                }
            }
            printf("%d\n", answer);
        }
    }
    return 0;
}
