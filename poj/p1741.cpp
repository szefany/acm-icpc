#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int N = 10000;
const int INF = 1 << 30;

struct Edge {
    int to, weight, next;
    Edge() {}
    Edge(int v, int w, int n): to(v), weight(w), next(n) {}
} g[N << 1];
int first[N], edge_count;

int dist[N], size[N], father[N];
bool visit[N];
int n, m;

void initialise() {
    for (int i = 0; i < n; ++ i) {
        first[i] = 0;
        visit[i] = false;
    }
    edge_count = 0;
}

void add_edge(int u, int v, int w) {
    edge_count ++;
    g[edge_count] = Edge(v, w, first[u]), first[u] = edge_count;
}

int queue[N], counter;
void dfs(int u, int p, int d) {
    father[u] = p;
    dist[u] = d;
    size[u] = 1;
    queue[counter ++] = u;
    for (int iter = first[u]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        int w = g[iter].weight;
        if (v != p && !visit[v]) {
            dfs(v, u, d + w);
            size[u] += size[v];
        }
    }
}

int get_root(int u) {
    counter = 0;
    dfs(u, -1, 0);
    int id = -1, record = INF;
    for (int i = 0; i < counter; ++ i) {
        int u = queue[i];
        int temp = counter - size[u];
        for (int iter = first[u]; iter; iter = g[iter].next) {
            int v = g[iter].to;
            if (v != father[u] && !visit[v]) {
                temp = std::max(temp, size[v]);
            }
        }
        if (temp < record) {
            record = temp;
            id = u;
        }
    }
    return id;
}

int buffer[N];
int count_1(int root, int d) {
    counter = 0;
    dfs(root, -1, d);
    for (int i = 0; i < counter; ++ i) {
        buffer[i] = dist[queue[i]];
    }
    std::sort(buffer, buffer + counter);
    int result = 0;
    for (int i = 0, j = counter - 1; i < j; ++ i) {
        while (j > i && buffer[i] + buffer[j] > m) {
            j --;
        }
        result += j - i;
    }
    return result;
}

int count_2(int root) {
    int result = 0;
    for (int iter = first[root]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        int w = g[iter].weight;
        if (!visit[v]) {
            result += count_1(v, w);
        }
    }
    return result;
}

int solve(int u) {
    int result = 0;
    int root = get_root(u);
    visit[root] = true;
    result += count_1(root, 0);
    result -= count_2(root);
    for (int iter = first[root]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        if (!visit[v]) {
            result += solve(v);
        }
    }
    return result;
}

int main() {
    while (scanf("%d%d", &n, &m) && n + m > 0) {
        initialise();
        for (int i = 0; i < n - 1; ++ i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            u --, v --;
            add_edge(u, v, w);
            add_edge(v, u, w);
        }
        int answer = solve(0);
        printf("%d\n", answer);
    }
    return 0;
}
