// POJ 3683, Priest John's Busiest Day
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 2005;
const int M = 2000000;

struct Graph {
    int to, next;
    Graph () {}
    Graph (int v, int n): to (v), next (n) {}
} g[2][M];

int first[2][N], color[N], queue[N], start[N][2], end[N][2], last[N], ans[N], degree[N];
int edge_count, counter, n, color_count;
bool connected[N][N], visit[N];
vector<int> neighbors[N], conflict[N];

void paint (int u) {
    ans[u] = 2;
    for (int iter = 0; iter < neighbors[u].size(); ++ iter) {
        int v = neighbors[u][iter];
        if (ans[v] == 0) {
            paint (v);
        }
    }
}

void put (int x) {
    if (x < 10) {
        putchar ('0');
    }
    printf ("%d", x);
}

void print (int x, int y) {
    put (x / 60), putchar (':'), put (x % 60), putchar (' ');
    put (y / 60), putchar (':'), put (y % 60), putchar ('\n');
}

void read (int &key) {
    int a, b;
    scanf (" %d:%d", &a, &b);
    key = a * 60 + b;
}

int trans (int x, int type) {
    return x + type * n;
}

bool intersect (int a, int i, int b, int j) {
    int x1 = start[a][i], y1 = end[a][i];
    int x2 = start[b][j], y2 = end[b][j];
    return x1 > x2 && x1 < y2 || x1 <= x2 && y1 > x2;
}

void add_edge (int u, int v) {
    edge_count ++;
    g[0][edge_count] = Graph (v, first[0][u]), first[0][u] = edge_count;
    g[1][edge_count] = Graph (u, first[1][v]), first[1][v] = edge_count;
}

void dfs_1 (int u) {
    visit[u] = true;
    for (int iter = first[0][u]; iter != 0; iter = g[0][iter].next) {
        int v = g[0][iter].to;
        if (!visit[v]) {
            dfs_1 (v);
        }
    }
    queue[++ counter] = u;
}

void dfs_2 (int u) {
    color[u] = color_count;
    visit[u] = true;
    for (int iter = first[1][u]; iter != 0; iter = g[1][iter].next) {
        int v = g[1][iter].to;
        if (!visit[v]) {
            dfs_2 (v);
        }
    }
}

int main () {
    scanf ("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        int s, t, d;
        read (s), read (t);
        scanf ("%d", &d);
        start[i][0] = s, end[i][0] = s + d;
        start[i][1] = t - d, end[i][1] = t;
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = i + 1; j <= n; ++ j) {
            for (int k = 0; k < 2; ++ k) {
                for (int l = 0; l < 2; ++ l) {
                    if (intersect (i, k, j, l)) {
                        add_edge (trans (i, k), trans (j, l ^ 1));
                        add_edge (trans (j, l), trans (i, k ^ 1));
                    }
                }
            }
        }
    }
    int node_count = n << 1;
    memset (visit, 0, sizeof (visit));
    counter = 0;
    for (int i = 1; i <= node_count; ++ i) {
        if (!visit[i]) {
            dfs_1 (i);
        }
    }
    memset (visit, 0, sizeof (visit));
    color_count = 0;
    for (int i = node_count; i >= 1; -- i) {
        int u = queue[i];
        if (!visit[u]) {
            color_count ++;
            dfs_2 (u);
        }
    }
    bool flag = true;
    for (int i = 1; i <= n; ++ i) {
        if (color[i] == color[i + n]) {
            flag = false;
            break;
        }
    }
    if (!flag) {
        puts ("NO");
        return 0;
    }
    puts ("YES");
    // New graph and obtain the conflict relationship
    for (int i = 1; i <= node_count; ++ i) {
        int u = color[i];
        for (int iter = first[0][i]; iter != 0; iter = g[0][iter].next) {
            int v = color[g[0][iter].to];
            if (u != v && !connected[v][u]) {
                connected[v][u] = true;
                neighbors[v].push_back (u); // Note that it is a REVERSED graph
                degree[u] ++;
            }
        }
    }
    for (int i = 1; i <= n; ++ i) {
        conflict[color[i]].push_back (color[i + n]);
        conflict[color[i + n]].push_back (color[i]);
    }
    // Topo sort
    int head = 0, tail = 0;
    for (int i = 1; i <= color_count; ++ i) {
        if (degree[i] == 0) {
            queue[++ tail] = i;
        }
    }
    while (head < tail) {
        int u = queue[++ head];
        for (int iter = 0; iter < neighbors[u].size(); ++ iter) {
            int v = neighbors[u][iter];
            degree[v] --;
            if (degree[v] == 0) {
                queue[++ tail] = v;
            }
        }
    }
    // Distribute
    memset (ans, 0, sizeof (ans));
    for (int i = 1; i <= color_count; ++ i) {
        int u = queue[i];
        if (ans[u] != 0) {
            continue;
        }
        ans[u] = 1;
        for (int iter = 0; iter < conflict[u].size(); ++ iter) {
            int v = conflict[u][iter];
            if (ans[v] == 0) {
                paint (v);
            }
        }
    }
    // Print
    for (int i = 1; i <= n; ++ i) {
        if (ans[color[i]] == 1) {
            print (start[i][0], end[i][0]);
        }
        else {
            print (start[i][1], end[i][1]);
        }
    }
    return 0;
}
