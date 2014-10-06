#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

const int N = 20000 + 10;

std::vector<Pair> edges;
std::vector<int> neighbors[N];
int covers[N], depth[N], father[N], n, m;

void dfs(int u, int f, std::queue<int>& queue) {
    depth[u] = depth[f] + 1;
    father[u] = f;
    for (int i = 0; i < neighbors[u].size(); ++ i) {
        int v = neighbors[u][i];
        if (v != f) {
            dfs(v, u, queue);
        }
    }
    queue.push(u);
}

int main() {
    scanf("%d%d", &n, &m);
    while (m --) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (w == 1) {
            neighbors[u].push_back(v);
            neighbors[v].push_back(u);
        } else {
            edges.push_back(make_pair(u, v));
        }
    }
    std::queue<int> queue;
    dfs(1, 0, queue);

    for (int i = 0; i < edges.size(); ++ i) {
        int u = edges[i].first;
        int v = edges[i].second;
        if (depth[u] < depth[v]) {
            std::swap(u, v);
        }
        covers[u] ++;
        covers[v] --;
    }

    int answer = 0;
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        answer += covers[u] == 1;
        covers[father[u]] += covers[u];
    }
    printf("%d\n", answer);
    return 0;
}
