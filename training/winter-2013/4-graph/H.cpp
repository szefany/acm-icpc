// POJ 3352, Road Construction
#include <cstdio>
#include <vector>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

using std::min;

const int N = 1000;

std::vector <int> neighbors[N];
int n, m, number;
int depth[N], lowest[N], color[N], degree[N];

void tarjan (int u, int f) {
    lowest[u] = depth[u] = f == -1 ? 1 : depth[f] + 1;
    foreach (iter, neighbors[u]) {
        int v = *iter;
        if (v == f) {
            continue;
        }
        if (depth[v]) {
            lowest[u] = std::min (lowest[u], depth[v]);
        } else {
            tarjan (v, u);
            lowest[u] = std::min (lowest[u], lowest[v]);
            if (lowest[v] > depth[u]) {
                number ++;
            }
        }
    }
}

bool visit[N];
int counter;
void paint (int u, int c) {
    visit[u] = true;
    color[u] = c;
    foreach (iter, neighbors[u]) {
        int v = *iter;
        if (!visit[v]) {
            paint (v, lowest[v] > depth[u] ? ++ counter : c);
        }
    }
}

int main () {
    scanf ("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        int u, v;
        scanf ("%d%d", &u, &v);
        u --, v --;
        neighbors[u].push_back (v);
        neighbors[v].push_back (u);
    }
    tarjan (0, -1);
    paint (0, 0);
    for (int u = 0; u < n; ++ u) {
        foreach (iter, neighbors[u]) {
            int v = *iter;
            if (color[u] != color[v]) {
                degree[color[u]] ++;
            }
        }
    }
    int answer = 0;
    for (int i = 0; i <= n; ++ i) {
        answer += degree[i] == 1;
    }
    printf ("%d\n", answer == 1 ? 0 : (answer + 1) / 2);
    return 0;
}
