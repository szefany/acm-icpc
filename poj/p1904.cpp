#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

#define foreach(i, v) for (std::vector<int>::iterator i = (v).begin(); i != (v).end(); ++ i)

const int N = 2000 + 10;

std::vector<int> neighbors[N], answer[N];

bool visit[N], is_matched[N];
int match[N], n;

struct SCC {
    static const int N = 4000 + 10;

    std::vector<int> edges[2][N];
    bool visit[N], arrived[2][N];
    int time_cut[N], color[N];
    int n;

    void initialise(int size) {
        n = size;
    }

    void add_edge(int u, int v) {
        edges[0][u].push_back(v);
        edges[1][v].push_back(u);
    }

    void dfs_1(int u, int &counter) {
        visit[u] = true;
        foreach(iter, edges[0][u]) {
            int v = *iter;
            if (!visit[v]) {
                dfs_1(v, counter);
            }
        }
        time_cut[++ counter] = u;
    }

    void dfs_2(int u, int counter) {
        visit[u] = true;
        color[u] = counter;
        foreach(iter, edges[1][u]) {
            int v = *iter;
            if (!visit[v]) {
                dfs_2(v, counter);
            }
        }
    }

    void get_scc() {
        memset(visit, 0, sizeof(visit));
        int counter = 0;
        for (int i = 1; i <= n; ++ i) {
            if (!visit[i]) {
                dfs_1(i, counter);
            }
        }
        memset(visit, 0, sizeof(visit));
        counter = 0;
        for (int i = n; i >= 1; -- i) {
            int u = time_cut[i];
            if (!visit[u]) {
                dfs_2(u, ++ counter);
            }
        }
    }

    int queue[N];

    void bfs(std::vector<int> &sources, int id) {
        int tail = 0;
        foreach(iter, sources) {
            int v = *iter;
            arrived[id][v] = true;
            queue[++ tail] = v;
        }
        for (int head = 1; head <= tail; ++ head) {
            int u = queue[head];
            foreach(iter, edges[id][u]) {
                int v = *iter;
                if (!arrived[id][v]) {
                    arrived[id][v] = true;
                    queue[++ tail] = v;
                }
            }
        }
    }

    bool judge(int u, int v) {
        return color[u] == color[v] || arrived[0][u] || arrived[1][v];
    }

} graph;

void read(int &result) {
    char c;
    while (c = getchar(), c < '0' || c > '9');
    result = (c & 15);
    while (c = getchar(), c >= '0' && c <= '9') {
        result = result * 10 + (c & 15);
    }
}

int main() {
    read(n);
    for (int i = 1; i <= n; ++ i) {
        int amount;
        read(amount);
        while (amount --) {
            int x;
            read(x);
            neighbors[i].push_back(x);
        }
    }

    memset(match, -1, sizeof(match));
    for (int i = 1; i <= n; ++ i) {
        int u;
        scanf("%d", &u);
        match[u] = i;
    }
    for (int i = 1; i <= n; ++ i) {
        int u = match[i];
        if (u != -1) {
            is_matched[u] = true;
        }
    }

    graph.initialise(n + n);
    for (int i = 1; i <= n; ++ i) {
        foreach(iter, neighbors[i]) {
            int v = *iter;
            if (match[v] == i) {
                graph.add_edge(v + n, i);
            } else {
                graph.add_edge(i, v + n);
            }
        }
    }
    graph.get_scc();

    std::vector<int> come, go;
    for (int i = 1; i <= n; ++ i) {
        if (!is_matched[i]) {
            go.push_back(i);
        }
        if (match[i] == -1) {
            come.push_back(i + n);
        }
    }

    graph.bfs(go, 0);
    graph.bfs(come, 1);

    for (int i = 1; i <= n; ++ i) {
        foreach(iter, neighbors[i]) {
            int v = *iter;
            if (match[v] == i || graph.judge(i, v + n)) {
                answer[i].push_back(v);
            }
        }
    }
    for (int i = 1; i <= n; ++ i) {
        std::sort(answer[i].begin(), answer[i].end());
        printf("%d ", (int)answer[i].size());
        foreach(iter, answer[i]) {
            printf("%d%c", *iter, iter + 1 == answer[i].end() ? '\n' : ' ');
        }
    }
    return 0;
}
