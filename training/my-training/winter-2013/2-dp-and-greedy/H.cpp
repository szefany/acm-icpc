// ZOJ 3524, Crazy Shopping
#include <cstdio>
#include <cstring>

const int N = 600;
const int W = 2000 + 5;
const int M = 100000;

struct Edge {
    int to, weight, next;
    Edge () {}
    Edge (int v, int w, int n): to (v), weight (w), next (n) {}
} g[M];
int first[N], edge_count;

int weight[N], values[N], queue[N], degree[N], max_value[N][W], energy[N][W];
int n, m, vs, capacity;

void initialise () {
    for (int i = 0; i < n; ++ i) {
        first[i] = degree[i] = 0;
    }
    edge_count = 0;
}

void add_edge (int u, int v, int w) {
    edge_count ++;
    g[edge_count] = Edge (v, w, first[u]), first[u] = edge_count;
}

void topo_sort (int* queue, int& length, int vs) {
    queue[0] = vs;
    for (int head = 0, tail = 1; head < tail; ++ head) {
        int u = queue[head];
        for (int iter = first[u]; iter; iter = g[iter].next) {
            int v = g[iter].to;
            degree[v] ++;
            if (degree[v] == 1) {
                queue[tail ++] = v;
            }
        }
    }
    length = 1;
    for (int head = 0; head < length; ++ head) {
        int u = queue[head];
        for (int iter = first[u]; iter; iter = g[iter].next) {
            int v = g[iter].to;
            degree[v] --;
            if (degree[v] == 0) {
                queue[length ++] = v;
            }
        }
    }
}

void update (int& target_value, int& target_energy, int value, int energy) {
    if (value > target_value || value == target_value && energy < target_energy) {
        target_value = value;
        target_energy = energy;
    }
}

int main () {
    while (scanf ("%d%d%d%d", &n, &m, &capacity, &vs) != EOF) {
        initialise ();
        for (int i = 0; i < n; ++ i) {
            scanf ("%d%d", &weight[i], &values[i]);
        }
        for (int i = 0; i < m; ++ i) {
            int u, v, w;
            scanf ("%d%d%d", &u, &v, &w);
            u --, v --;
            add_edge (u, v, w);
        }
        int total;
        topo_sort (queue, total, vs - 1);
        for (int i = 0; i < n; ++ i) {
            max_value[i][0] = 0;
            for (int j = 1; j <= capacity; ++ j) {
                max_value[i][j] = 0;
                energy[i][j] = 0;
            }
        }
        int final_value = -1, final_energy = 0;
        for (int i = 0; i < total; ++ i) {
            int u = queue[i];
            for (int j = weight[u]; j <= capacity; ++ j) {
                update (max_value[u][j], energy[u][j], max_value[u][j - weight[u]] + values[u], energy[u][j - weight[u]]);
                update (final_value, final_energy, max_value[u][j], energy[u][j]);
            }
            for (int iter = first[u]; iter; iter = g[iter].next) {
                int v = g[iter].to, w = g[iter].weight;
                for (int j = 0; j < capacity; ++ j) {
                    update (max_value[v][j], energy[v][j], max_value[u][j], energy[u][j] + w * j);
                }
            }
        }
        printf ("%d\n", final_energy);
    }
    return 0;
}
