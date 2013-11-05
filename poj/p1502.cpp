#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100 + 10;
const int M = 100000;
const int INF = 1 << 29;

struct Edge {
    int to, cost, next;
    Edge(int v = 0, int c = 0, int n = 0): to(v), cost(c), next(n) {}
} g[M];
int first[N], edge_count;

void add_edge(int u, int v, int c) {
    edge_count ++;
    g[edge_count] = Edge(v, c, first[u]), first[u] = edge_count;
}

const int S = N << 2;

int value[S], id[S], node_count;
int position[N];
bool visit[N];

void swap_data(int u, int v) {
    std::swap(position[id[u]], position[id[v]]);
    std::swap(id[u], id[v]);
    std::swap(value[u], value[v]);
}

void up(int u) {
    while (u > 1) {
        if (value[u] < value[u >> 1]) {
            swap_data(u, u >> 1);
            u >>= 1;
        } else {
            break;
        }
    }
}

void down(int u) {
    while (u << 1 <= node_count) {
        if (u << 1 == node_count) {
            if (value[u << 1] < value[u]) {
                swap_data(u, u << 1);
            }
            break;
        }
        int v = value[u << 1] < value[(u << 1) | 1] ? u << 1 : (u << 1) + 1;
        if (value[v] < value[u]) {
            swap_data(u, v);
            u = v;
        } else {
            break;
        }
    }
}

void insert(int u, int v) {
    node_count ++;
    value[node_count] = v;
    id[node_count] = u;
    up(node_count);
}

void erase() {
    position[id[1]] = -1;
    swap_data(1, node_count);
    node_count --;
    down(1);
}

void modify(int u, int v) {
    int node = position[u];
    if (node == -1) {
        node = ++ node_count;
        position[u] = node;
        id[node] = u;
    }
    value[node] = v;
    up(node);
}

int dist[N], n;

void get_mindist() {
    memset(dist, 60, sizeof(dist));
    memset(visit, 0, sizeof(visit));
    memset(position, -1, sizeof(position));
    dist[1] = 0;
    insert(1, 0);
    for (int counter = 1; counter <= n; ++ counter) {
        int u = id[1];
        visit[u] = true;
        erase();
        for (int iter = first[u]; iter; iter = g[iter].next) {
            int v = g[iter].to;
            if (dist[u] + g[iter].cost < dist[v]) {
                dist[v] = dist[u] + g[iter].cost;
                modify(v, dist[v]);
            }
        }
    }
}

int main() {
    freopen("input", "r", stdin);
    scanf("%d", &n);
    for (int i = 2; i <= n; ++ i) {
        for (int j = 1; j < i; ++ j) {
            char buffer[20];
            scanf("%s", buffer);
            if (*buffer != 'x') {
                int cost;
                sscanf(buffer, "%d", &cost);
                add_edge(i, j, cost);
                add_edge(j, i, cost);
            }
        }
    }
    get_mindist();
    int answer = 0;
    for (int i = 2; i <= n; ++ i) {
        answer = std::max(answer, dist[i]);
    }
    printf("%d\n", answer);
    return 0;
}
