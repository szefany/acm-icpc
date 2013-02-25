// HDU 4003, Find Metal Mineral
#include <iostream>
#include <cstdio>
#include <vector>
#include <climits>

using std::make_pair;
using std::min;

#define foreach(i, v) for (__typeof ((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

typedef std::pair <int, int> Pair;

const int N = 10000 + 5;
const int INF = N * N * 10 + N * 10;

std::vector <Pair> neighbors[N];
bool is_leaf[N];
int cost[N][15][2], temp[N][15][2];
int n, m, vs;

void initialise () {
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j <= m; ++ j) {
            for (int k = 0; k < 2; ++ k) {
                cost[i][j][k] = temp[i][j][k] = INF;
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        is_leaf[i] = true;
        neighbors[i].clear();
    }
}

inline void update (int& target, int value) {
    if (value < target) {
        target = value;
    }
}

void solve (int u, int f) {
    foreach (iter, neighbors[u]) {
        int v = (*iter).first;
        if (v != f) {
            solve (v, u);
            is_leaf[u] = false;
        }
    }
    if (is_leaf[u]) {
        cost[u][0][0] = cost[u][0][1] = INF;
        for (int i = 1; i <= m; ++ i) {
            for (int j = 0; j < 2; ++ j) {
                cost[u][i][j] = 0;
            }
        }
        return;
    }
    cost[u][0][0] = 0;
    foreach (iter, neighbors[u]) {
        int v = (*iter).first, w = (*iter).second;
        if (v == f) {
            continue;
        }
        for (int i = 0; i <= m; ++ i) {
            temp[u][i][0] = temp[u][i][1] = INF;
            for (int j = 1; j <= i; ++ j) {
                update (temp[u][i][0], j * w + cost[v][j][0] + min (cost[u][i - j][0], cost[u][i - j + 1][1]));
                update (temp[u][i][0], j * w + w + cost[v][j][1] + cost[u][i - j + 1][0]);
                update (temp[u][i][1], j * w + cost[v][j][0] + cost[u][i - j][1]);
                update (temp[u][i][1], j * w + w + cost[v][j][1] + min (cost[u][i - j][0], cost[u][i - j + 1][1]));
            }
        }
        for (int i = 0; i <= m; ++ i) {
            for (int j = 0; j < 2; ++ j) {
                cost[u][i][j] = temp[u][i][j];
            }
        }
    }
    cost[u][0][0] = cost[u][0][1] = INF;
}

int main () {
    while (scanf ("%d%d%d", &n, &vs, &m) != EOF) {
        initialise ();
        for (int i = 1; i < n; ++ i) {
            int u, v, w;
            scanf ("%d%d%d", &u, &v, &w);
            u --, v --;
            neighbors[u].push_back (make_pair (v, w));
            neighbors[v].push_back (make_pair (u, w));
        }
        vs --;
        solve (vs, -1);
        int answer = INF;
        for (int i = 1; i <= m; ++ i) {
            if (cost[vs][i][0] < answer) {
                answer = cost[vs][i][0];
            }
        }
        std::cout << answer << '\n';
    }
    return 0;
}
