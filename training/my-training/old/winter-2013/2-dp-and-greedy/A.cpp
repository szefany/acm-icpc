#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

const int N = 100;
const int M = 1000;
const int INF = 1 << 20;

struct Graph {
    Graph () {}
    Graph (int u, int v, int f, int c, int n): from(u), to(v), flow(f), capa(c), next(n) {}
    int from, to, capa, flow, next;
} g[M];
int first[N], arc[N], edge_count, vs, vt;

int n;
int scores[N];

typedef pair<int, int> Pair;
map<Pair, int> matches;
int counter;

bool cmp (int x, int y) {
    return x > y;
}

int get_index (int u, int v) {
    if (u > v) {
        swap (u, v);
    }
    return matches[make_pair (u, v)];
}

void addEdge (int u, int v, int c) {
    edge_count ++;
    g[edge_count] = Graph (u, v, 0, c, first[u]), first[u] = edge_count;
    g[M - edge_count] = Graph (v, u, 0, 0, first[v]), first[v] = M - edge_count;
}

int links[N], queue[N];
bool bfs () {
    memset (links, 0, sizeof (links));
    links[vs] = 1;
    queue[1] = vs;
    for (int head = 1, tail = 1; head <= tail; ++ head) {
        int u = queue[head];
        for (int iter = first[u]; iter != 0; iter = g[iter].next) {
            int v = g[iter].to;
            if (links[v] == 0 && g[iter].flow < g[iter].capa) {
                queue[++ tail] = v;
                links[v] = links[u] + 1;
            }
        }
    }
    return links[vt] != 0;
}

int dfs (int u, int d) {
    if (u == vt) return d;
    int delta = 0;
    for (int &iter = arc[u]; iter != 0; iter = g[iter].next) {
        int v = g[iter].to;
        if (links[v] == links[u] + 1 && g[iter].flow < g[iter].capa) {
            int r = dfs (v, min (d - delta, g[iter].capa - g[iter].flow));
            g[iter].flow += r;
            g[M - iter].flow -= r;
            delta += r;
            if (d == delta) return d;
        }
    }
    return delta;
}

bool check (int x) {
    memset (first, 0, sizeof (first));
    edge_count = 0;
    vs = counter + 1, vt = counter + 2;
    for (int i = n + 1; i <= counter; ++ i) {
        addEdge (i, vt, 1);
    }
    int total_flow = 0;
    for (int i = 1; i <= x; ++ i) {
        int win = scores[i];
        int j;
        for (j = 1; scores[j] > scores[i]; ++ j) {
            win --;
        }
        if (win < 0) {
            return false;
        }
        addEdge (vs, i, win);
        total_flow += win;
        for (int k = j; k <= n; ++ k) {
            if (k == i || (k <= x && scores[k] < scores[i])) continue;
            addEdge (i, get_index (i, k), 1);
        }
    }
    for (int i = x + 1; i <= n; ++ i) {
        addEdge (vs, i, scores[i]);
        total_flow += scores[i];
        for (int j = 1; j <= n; ++ j) {
            if (i == j) continue;
            addEdge (i, get_index (i, j), 1);
        }
    }
    int flow = 0;
    while (bfs ()) {
        memcpy (arc, first, sizeof (first));
        flow += dfs (vs, INF);
    }
    return flow == total_flow;
}

int main () {
    int testCount;
    scanf ("%d", &testCount);
    getchar ();
    while (testCount --) {
        string str;
        stringstream buffer;
        getline (cin, str);
        buffer << str;
        int iter = 1;
        while (buffer >> scores[iter]) {
            iter ++;
        }
        n = iter - 1;
        sort (scores + 1, scores + n + 1, cmp);
        // init map
        matches.clear();
        counter = n;
        for (int i = 1; i < n; ++ i) {
            for (int j = i + 1; j <= n; ++ j) {
                matches[make_pair (i, j)] = ++ counter;
            }
        }
        int ans = 1;
        for (int iter = 2; iter <= n; ++ iter) {
            if (check (iter)) {
                ans = iter;
            } else {
                break;
            }
        }
        printf ("%d\n", ans);
    }
    return 0;
}
