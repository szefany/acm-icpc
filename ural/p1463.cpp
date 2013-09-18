#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using std::max;

const int N = 50000 + 10;
const int M = N * 4;

struct Edge {
    int to, weight, next;
    Edge(int v = 0, int w = 0, int n = 0): to(v), weight(w), next(n) {}
} g[M];
int first[N], edge_count;

void add_edge(int u, int v, int w) {
    edge_count ++;
    g[edge_count] = Edge(v, w, first[u]), first[u] = edge_count;
}

bool visit[N];
int a[N];
int n, m;

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;
Pair upper[N], lower[N], answer;

void dfs(int u, int p) {
    visit[u] = true;
    for (int iter = first[u]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        if (v != p) {
            dfs(v, u);
        }
    }
    upper[u] = make_pair(a[u], 0);
    lower[u] = make_pair(a[u], 0);
    for (int iter = first[u]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        if (v != p) {
            Pair temp = make_pair(upper[v].first + g[iter].weight + a[u], v);
            if (temp > upper[u]) {
                lower[u] = upper[u];
                upper[u] = temp;
            } else if (temp > lower[u]) {
                lower[u] = temp;
            }
        }
    }
}

int queue[N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
    }
    while (m --) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    answer = make_pair(0, 0);
    for (int i = 1; i <= n; ++ i) {
        if (!visit[i]) {
            dfs(i, 0);
        }
    }
    
    int id = 0;
    int result = -1;
    for (int i = 1; i <= n; ++ i) {
        int temp = lower[i].first + upper[i].first - a[i];
        if (temp > result) {
            result = temp;
            id = i;
        }
    }

    int length = 0;
    for (int u = id; u; u = upper[u].second) {
        queue[++ length] = u;
    }
    std::reverse(queue + 1, queue + length + 1);
    for (int u = lower[id].second; u; u = upper[u].second) {
        queue[++ length] = u;
    }
    printf("%d\n", result);
    printf("%d\n", length);
    for (int i = 1; i <= length; ++ i) {
        printf("%d%c", queue[i], i == length ? '\n' : ' ');
    }
    return 0;
}
