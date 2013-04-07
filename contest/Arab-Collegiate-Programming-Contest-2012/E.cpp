#include <cstdio>
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

const int N = 200;
const int M = 100000;
const int INF = 1 << 20;

struct Edge {
    Edge () {}
    Edge (int v, int f, int c, int n): to (v), flow (f), capa (c), next (n) {}
    int to, flow, capa, next;
} g[M];
int first[N], edge_count;
int vs, vt, n;

void add_edge (int u, int v, int c) {
    edge_count ++;
    g[edge_count] = Edge (v, 0, c, first[u]), first[u] = edge_count;
    g[M - edge_count] = Edge (u, 0, 0, first[v]), first[v] = M - edge_count;
}

char string[N], buffer[N], id[N];
bool map[N][N];
int counter[N], number[N], match[N];

std::map<char, int> links;
int size;

void initialise () {
    links.clear ();
    size = 0;
#define clr(x) memset ((x), 0, sizeof (x))
    clr (g), clr (string), clr (buffer), clr (id), clr (counter), clr (number), clr (map), clr (first), clr (match), edge_count = 0;
}

int trans (char key) {
    if (links.find (key) == links.end()) {
        links[key] = ++ size;
        id[size] = key;
    }
    return links[key];
}

int queue[N], label[N];
bool bfs () {
    memset (label, 0, sizeof (label));
    label[vs] = 1;
    queue[0] = vs;
    for (int head = 0, tail = 0; head <= tail; ++ head) {
        int u = queue[head];
        for (int iter = first[u]; iter; iter = g[iter].next) {
            int v = g[iter].to;
            if (g[iter].flow < g[iter].capa && label[v] == 0) {
                label[v] = label[u] + 1;
                queue[++ tail] = v;
            }
        }
    }
    return label[vt];
}

int dfs (int u, int d) {
    if (u == vt) {
        return d;
    }
    int delta = 0;
    for (int iter = first[u]; iter; iter = g[iter].next) {
        int v = g[iter].to;
        if (g[iter].flow < g[iter].capa && label[u] + 1 == label[v]) {
            int r = dfs (v, std::min (d - delta, g[iter].capa - g[iter].flow));
            g[iter].flow += r;
            g[M - iter].flow -= r;
            delta += r;
            if (d == delta) {
                return d;
            }
        }
    }
    return delta;
}

bool check (int from, int letter) {
    memset (first, 0, sizeof (first));
    edge_count = 0;
    match[from] = letter;

    for (int i = 1; i <= n; ++ i) {
        add_edge (vs, i, 1);
        if (i <= from) {
            add_edge (i, n + match[i], 1);
        } else {
            for (int j = 1; j <= 26; ++ j) {
                if (map[i][j]) {
                    add_edge (i, n + j, 1);
                }
            }
        }
    }
    for (int i = 1; i <= 26; ++ i) {
        add_edge (n + i, vt, number[i]);
    }

    int flow = 0;
    while (bfs ()) {
        flow += dfs (vs, INF);
    }
    return flow == n;
}

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        initialise ();
        scanf ("%s", string);
        n = strlen (string);

        for (int i = 0; i < n; ++ i) {
            number[string[i] - 'a' + 1] ++;
        }

        vs = n + 26 + 1;
        vt = n + 26 + 2;
        for (int i = 1; i <= n; ++ i) {
            add_edge (vs, i, 1);
            scanf ("%s", buffer);
            int length = strlen (buffer);
            for (int j = 0; j < length; ++ j) {
                int x = buffer[j] - 'a' + 1; 
                map[i][x] = true;
                add_edge (i, n + x, 1);
            }
        }
        for (int i = 1; i <= 26; ++ i) {
            add_edge (n + i, vt, number[i]);
        }

        int flow = 0;
        while (bfs ()) {
            flow += dfs (vs, INF);
        }
        if (flow < n) {
            puts ("NO SOLUTION");
            continue;
        }

        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= 26; ++ j) {
                if (map[i][j] && number[j] && check (i, j)) {
                    match[i] = j;
                    putchar (j + 'a' - 1);
                    break;
                }               
            }
        }
        puts ("");
    }
    return 0;
}
