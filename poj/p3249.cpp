// POJ 3249, Test for Job
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 100005;

vector<int> neighbors[N];
int values[N], in_degree[N], out_degree[N], queue[N + N];
long long dist[N];
int n, m;

void init () {
    memset (in_degree, 0, sizeof (in_degree));
    memset (out_degree, 0, sizeof (out_degree));
    memset (values, 0, sizeof (values));
    for (int i = 1; i < N; ++ i) {
        neighbors[i].clear();
    }
}

int main () {
    while (scanf ("%d%d", &n, &m) != EOF) {
        init ();
        for (int i = 1; i <= n; ++ i) {
            scanf ("%d", &values[i]);
        }
        while (m --) {
            int u, v;
            scanf ("%d%d", &u, &v);
            neighbors[u].push_back (v);
            in_degree[v] ++;
            out_degree[u] ++;
        }
        int vs = n + 1, vt = n + 2;
        for (int i = 1; i <= n; ++ i) {
            if (in_degree[i] == 0) {
                neighbors[vs].push_back (i);
                in_degree[i] ++;
            }
            if (out_degree[i] == 0) {
                neighbors[i].push_back (vt);
                in_degree[vt] ++;
            }
        }
        memset (dist, 200, sizeof (dist));
        queue[1] = vs, dist[vs] = 0;
        int head = 0, tail = 1;
        while (head != tail) {
            head = head % N + 1;
            int u = queue[head];
            for (int iter = 0; iter < neighbors[u].size(); ++ iter) {
                int v = neighbors[u][iter];
                if (dist[u] + values[v] > dist[v]) {
                    dist[v] = dist[u] + values[v];
                }
                in_degree[v] --;
                if (in_degree[v] == 0) {
                    tail = tail % N + 1;
                    queue[tail] = v;
                }
            }
        }
        if (dist[vt] == dist[0]) {
            dist[vt] = 0;
        }
        cout << dist[vt] << endl;
    }
    return 0;
}
