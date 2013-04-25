#include <cstdio>
#include <cstring>
#include <vector>
#include <climits>
#include <cstdlib>
#include <ctime>

const int N = 300000 + 1;
const int M = N << 1;
const int INF = 1 << 30;

struct treap_data {
    static const int SIZE = 300000 + 1;
    int weight[SIZE], value[SIZE], key[SIZE], max_value[SIZE], child[SIZE][2], size[SIZE];
    int node_count, root;
    
    void initialise() {
        node_count = root = 0;
        weight[0] = INT_MAX;
    }
    
    void update(int u) {
        size[u] = 1;
        max_value[u] = value[u];
        for (int i = 0; i < 2; ++ i) {
            int v = child[u][i];
            size[u] += size[v];
            max_value[u] = std::max(max_value[u], max_value[v]);
        }
    }
    
    void rotate(int &u, int d) {
        int v = child[u][d];
        child[u][d] = child[v][d ^ 1];
        child[v][d ^ 1] = u;
        update(u);
        update(v);
        u = v;
    }
    
    void insert(int &u, int k, int v) {
        if (u == 0) {
            u = ++ node_count;
            weight[u] = rand();
            key[u] = k;
            value[u] = max_value[u] = v;
            child[u][0] = child[u][1] = 0;
        } else if (k == key[u]) {
            value[u] = std::max(value[u], v);
        } else {
            int d = k > key[u];
            insert(child[u][d], k, v);
            if (weight[child[u][d]] < weight[u]) {
                rotate(u, d);
            }
        }
        update(u);
    }
    
    int find(int bound) {
        int result = 0, u = root;
        while (u) {
            if (bound >= key[u]) {
                result = std::max(result, max_value[child[u][0]]);
                result = std::max(result, value[u]);
                u = child[u][1];
            } else {
                u = child[u][0];
            }
        }
        return result;
    }
    
    void push(int k, int v) {
        insert(root, k, v);
    }
} treap;

struct Edge {
    int to, weight, next;
    Edge() {}
    Edge(int v, int w, int n): to(v), weight(w), next(n) {}
} g[M];
int first[N], edge_count;

bool black[N], mark[N];
int depth[N], size[N];
int n, limit, m;

void add_edge(int u, int v, int w) {
    edge_count ++;
    g[edge_count] = Edge(v, w, first[u]), first[u] = edge_count;
}

std::vector<int> nodes, dp[N];

void dfs(int u, int p) {
    nodes.push_back(u);
    depth[u] = black[u];
    size[u] = 1;
    for (int iter = first[u]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        if (v != p && !mark[v]) {
            dfs(v, u);
            depth[u] = std::max(depth[u], depth[v] + black[u]);
            size[u] += size[v];
        }
    }
}

int get_root(int u) {
    nodes.clear();
    dfs(u, -1);
    int id = -1, record = INF, m = nodes.size();
    for (int i = 0; i < m; ++ i) {
        int v = nodes[i];
        int temp = std::max(size[v], m - size[v]);
        if (temp < record) {
            record = temp;
            id = v;
        }
    }
    return id;
}

int longest[N];
void solve(int u, int p, int count, int dist) {
    longest[count] = std::max(longest[count], dist);
    for (int iter = first[u]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        int w = g[iter].weight;
        if (!mark[v] && v != p) {
            solve(v, u, count + black[v], dist + w);
        }
    }
}

int divide(int u) {
    int root = get_root(u);
    mark[root] = true;
    
    nodes.clear();
    dfs(root, -1);
    
    int result = 0;
    treap.initialise();
    treap.push(black[root], 0);
    for (int iter = first[root]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        int w = g[iter].weight;
        if (!mark[v]) {
            for (int i = 0; i <= depth[v]; ++ i) {
                longest[i] = -INF;
            }
            solve(v, root, black[v], 0);
            for (int i = std::min(depth[v], limit - black[root]); i >= 0; -- i) {
                if (longest[i] != -INF) {
                    int temp = treap.find(limit - i);
                    result = std::max(result, temp + w + longest[i]);
                }
            }
            for (int i = 0; i <= depth[v]; ++ i) {
                if (longest[i] != -INF) {
                    treap.push(i + black[root], longest[i] + w);
                }
            }
        }
    }
    for (int iter = first[root]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        if (!mark[v]) {
            result = std::max(result, divide(v));
        }
    }
    return result;
}

int main() {
    srand(time(0));
    scanf("%d%d%d", &n, &limit, &m);
    for (int i = 0; i < m; ++ i) {
        int x;
        scanf("%d", &x);
        black[x - 1] = true;
    }
    for (int i = 0; i < n - 1; ++ i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u --, v --;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    int answer = divide(0);
    printf("%d\n", answer);
    return 0;
}
