// Coceforces Bayan 2012-2013 Elimination Round 
// Problem E, Flights
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 1005;
const int M = 10005;

struct Graph {
    Graph () {}
    Graph (int u, int v): from(u), to(v) {}
    Graph (int u, int v, int w, int n): from(u), to(v), weight(w), next(n) {}
    int from, to, weight, next;
} g[M], edges[M];
int first[N], edgeCount;

int n, m;
bool visit[2][N];

void addEdge (int u, int v, int w) {
    edgeCount ++;
    g[edgeCount] = Graph (u, v, w, first[u]), first[u] = edgeCount;
}

void dfs (int u, int p) {
    visit[p][u] = true;
    for (int iter = first[u]; iter != 0; iter = g[iter].next) {
        int v = g[iter].to;
        if ((p == 0 && g[iter].weight < 0) || (p == 1 && g[iter].weight > 0)) continue;
        if (!visit[p][v]) {
            dfs (v, p);
        }
    }
}

int q[N * 2], dist[N], counter[N];
bool inQueue[N];
static const int Q = N;

int main () {
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= m; ++ i) {
        int u, v;
        scanf ("%d%d", &u, &v);
        addEdge (u, v, 2);
        addEdge (v, u, -1);
        edges[i] = Graph (u, v);
    }
    dfs (1, 0);
    dfs (n, 1);
    memset (dist, 1, sizeof (dist));
    dist[1] = 0, q[1] = 1, counter[1] = 1;
    for (int head = 0, tail = 1; head != tail; ) {
        head = head % Q + 1;
        int u = q[head];
        inQueue[u] = false;
        for (int iter = first[u]; iter != 0; iter = g[iter].next) {
            int v = g[iter].to;
            if (!visit[0][v] || !visit[1][v]) continue;
            if (dist[u] + g[iter].weight < dist[v]) {
                dist[v] = dist[u] + g[iter].weight;
                if (!inQueue[v]) {
                    tail = tail % Q + 1;
                    q[tail] = v;
                    inQueue[v] = true;
                    counter[v] ++;
                    if (counter[v] > n + n) {
                        puts ("No");
                        return 0;
                    }
                }
            }
        }
    }
    puts ("Yes");
    for (int i = 1; i <= m; ++ i) {
        int u = edges[i].from;
        int v = edges[i].to;
        if (!visit[0][u] || !visit[1][u] || !visit[0][v] || !visit[1][v]) {
            puts ("1");
        }
        else {
            printf ("%d\n", dist[v] - dist[u]);
        }
    }
    return 0;
}
