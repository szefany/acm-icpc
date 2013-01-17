#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1005;
const int M = 26;

struct Graph {
    Graph () {}
    Graph (int _to, int _value, int _next): to(_to), value(_value), next(_next) {}
    int to, value, next;
} g[N * 2];
int indegree[M], outdegree[M], first[M], edgeCount;

vector<int> path;
bool exist[M];
int rank[N], length[N];
char str[N][M];
int n;

void init () {
    edgeCount = 0;
    memset (indegree, 0, sizeof (indegree));
    memset (outdegree, 0, sizeof (outdegree));
    memset (first, 0, sizeof (first));
    memset (exist, 0, sizeof (exist));
    path.clear();
}

bool cmp (int x, int y) {
    return strcmp (str[x], str[y]) > 0;
}

void addEdge (int u, int v, int w) {
    edgeCount ++ ;
    g[edgeCount] = Graph (v, w, first[u]), first[u] = edgeCount;
    indegree[v] ++;
    outdegree[u] ++;
    // printf ("%c %c\n", (char)u + 'a', (char)v + 'a');
}

int father[M];
int find (int u) {
    int root = u;
    while (root != father[root]) {
        root = father[root];
    }
    while (u != root) {
        int temp = father[u];
        father[u] = root;
        u = temp;
    }
    return root;
}

void joint (int u, int v) {
    u = find (u);
    v = find (v);
    if (u != v) {
        father[u] = v;
    }
}

int is_euler () {
    // directed graph
    // check if it's a connected graph
    for (int i = 0; i < 26; ++ i) {
        if (!exist[i]) continue;
        father[i] = i;
    }
    for (int i = 0; i < 26; ++ i) {
        if (!exist[i]) continue;
        for (int iter = first[i]; iter != 0; iter = g[iter].next) {
            int j = g[iter].to;
            joint (i, j);
        }
    }
    int blocks = 0;
    for (int i = 0; i < 26; ++ i) {
        if (!exist[i]) continue;
        blocks += (find (i) == i);
    }
    if (blocks > 1) {
        return -1;
    }
    // check if the degrees are legal
    int outset = 0, position = -1;
    for (int i = 25; i >= 0 && outset < 3; -- i) {
        if (!exist[i]) continue;
        int x = abs (indegree[i] - outdegree[i]);
        if (x == 1) {
            outset ++;
            if (outdegree[i] > indegree[i]) position = i;
        }
        else if (x == 2) outset = 3;
    }
    if (outset > 2 || outset == 1) {
        return -1;
    }
    if (position == -1) {
        for (position = 0; position < 26 && !exist[position]; ++ position);
    }
    return position;
}

void dfs (int u, int last) {
    for (int &iter = first[u]; iter != 0; ) {
        int v = g[iter].to, w = g[iter].value;
        iter = g[iter].next;
        dfs (v, w);
    }
    if (last != -1) {
        path.push_back (last);
    }
}

int main () {
    freopen ("input.txt", "r", stdin);
    int testCount;
    scanf ("%d", &testCount);
    while (testCount --) {
        init ();
        scanf ("%d", &n);
        for (int i = 1; i <= n; ++ i) {
            rank[i] = i;
            scanf ("%s", str[i]);
            length[i] = strlen (str[i]);
            // words[str[i][0] - 'a'].push_back (i);
        }
        sort (rank + 1, rank + n + 1, cmp);
        /*
        for (int i = 0; i < 26; ++ i) {
            sort (words[i].begin(), words[i].end(), cmp);
            pivot[i] = 0;
        }
        */
        for (int i = 1; i <= n; ++ i) {
            int x = rank[i];
            int u = str[x][0] - 'a', v = str[x][length[x] - 1] - 'a';
            exist[u] = exist[v] = true;
            addEdge (u, v, x);
        }
        int start = is_euler ();
        if (start == -1) {
            puts ("***");
            continue;
        }
        dfs (start, -1);
        for (int i = path.size() - 1; i >= 0; -- i) {
            printf ("%s%c", str[path[i]], i == 0 ? '\n' : '.');
        }
    }
    return 0;
}

