// UVALive 6151, Beehives
#include <iostream>
#include <cstdio>
#include <vector>
#include <deque>

const int N = 500;
const int INF = 1 << 30;

typedef std::pair<int, int> Pair;

std::vector <int> neighbors[N];
int depth[N];
int n, m, answer;

void initialise () {
    for (int i = 0; i < n; ++ i) {
        depth[i] = -1;
        neighbors[i].clear();
    }
}

std::deque <Pair> queue;
void bfs (int vs) {
    for (int i = 0; i < n; ++ i) {
        depth[i] = -1;
    }
    queue.push_back (std::make_pair (vs, -1));
    depth[vs] = 0;
    while (!queue.empty()) {
        int u = queue.front().first, f = queue.front().second;
        queue.pop_front();
        for (int i = 0; i < neighbors[u].size(); ++ i) {
            int v = neighbors[u][i];
            if (v != f) {
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    queue.push_back (std::make_pair (v, u));
                } else {
                    answer = std::min (answer, depth[u] + depth[v] + 1);
                }
            }
        }
    }
}

int main () {
    int test_count;
    scanf ("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        scanf ("%d%d", &n, &m);
        initialise ();
        for (int i = 0; i < m; ++ i) {
            int u, v;
            scanf ("%d%d", &u, &v);
            neighbors[u].push_back (v);
            neighbors[v].push_back (u);
        }
        answer = INF;
        for (int i = 0; i < n; ++ i) {
            bfs (i);
        }
        printf ("Case %d: ", t);
        if (answer == INF) {
            puts ("impossible");
        } else {
            printf ("%d\n", answer);
        }
    }
    return 0;
}
