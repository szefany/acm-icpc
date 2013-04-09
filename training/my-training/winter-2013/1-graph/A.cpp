// URAL 1129, Door Painting
#include <cstdio>
#include <vector>

#define foreach(i, v) for (__typeof ((v).begin()) i = (v).begin(); i != (v).end(); i ++)

const int N = 100 + 5;

std::vector <int> neighbors[N];
int edges[N][N], color[N][N], current[N], degree[N];
int n;

void dfs (int u, int c) {
    for (int i = 0; i < n; ++ i) {
        if (edges[u][i]) {
            color[u][i] = c;
            color[i][u] = c ^ 1;
            degree[u] --;
            degree[i] --;
            edges[u][i] --;
            edges[i][u] --;
            dfs (i, c);
            return;
        }
    }
}

int main () {
    scanf ("%d", &n);
    for (int i = 0; i < n; ++ i) {
        int number;
        scanf ("%d", &number);
        while (number --) {
            int x;
            scanf ("%d", &x);
            x --;
            edges[i][x] ++;
            degree[i] ++;
            neighbors[i].push_back (x);
        }
    }
    for (int i = 0; i < n; ++ i) {
        while (degree[i]) {
            dfs (i, current[i]);
            current[i] ^= 1;
        }
    }
    for (int i = 0; i < n; ++ i) {
        foreach (iter, neighbors[i]) {
            printf ("%c%c", color[i][*iter] ? 'G' : 'Y', iter + 1 == neighbors[i].end() ? '\n' : ' ');
        }
    }
    return 0;
}
