#include <cstdio>
#include <cstring>
#include <vector>
#include <set>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 500;
const int M = 50000;
const int INF = 1 << 30;

struct Query {
    char buffer[2];
    int u, v;
    void input() {
        scanf("%s%d%d", buffer, &u, &v);
        u --, v --;
    }
} queries[M];

std::pair<int, int> edges[M];
std::set<int> neighbors[N];
bool map[N][N];
int id[N][N], visit[N];
int n, m;

void initialise() {
    for (int i = 0; i < n; ++ i) {
        neighbors[i].clear();
        visit[i] = 0;
        for (int j = 0; j < n; ++ j) {
            map[i][j] = false;
            id[i][j] = INF;
        }
    }
}

bool reach(int u, int dest, int times) {
    if (u == dest) {
        return true;
    }
    visit[u] = times;
    foreach(iter, neighbors[u]) {
        int v = *iter;
        if (visit[v] != times && reach(v, dest, times)) {
            return true;
        }
    }
    return false;
}

std::vector<int> path;
int find(int u, int dest, int times) {
    path.push_back(u);
    if (u == dest) {
        int result = INF;
        foreach(iter, path) {
            if (iter + 1 != path.end()) {
                int u = *iter;
                int v = *(iter + 1);
                result = std::min(result, id[u][v]);
            }
        }
        path.pop_back();
        return result;
    }
    visit[u] = times;
    foreach(iter, neighbors[u]) {
        int v = *iter;
        if (visit[v] != times) {
            int temp = find(v, dest, times);
            if (temp != -1) {
                return temp;
            }
        }
    }
    path.pop_back();
    return -1;
}

void insert_edge(int u, int v) {
    map[u][v] = map[v][u] = true;
    neighbors[u].insert(v);
    neighbors[v].insert(u);
}

void delete_edge(int u, int v) {
    map[u][v] = map[v][u] = false;
    neighbors[u].erase(v);
    neighbors[v].erase(u);
}

int main() {
    int test_count = 0;
    while (scanf("%d%d", &n, &m) != EOF) {
        initialise();
        if (test_count) {
            puts("");
        }
        for (int i = 0; i < m; ++ i) {
            queries[i].input();
            int u = queries[i].u, v = queries[i].v;
            if (queries[i].buffer[0] == 'D') {
                id[u][v] = id[v][u] = i;
                edges[i] = std::make_pair(u, v);
            }
        }
        printf("Case %d:\n", ++ test_count);
        for (int i = 0; i < m; ++ i) {
            char type = queries[i].buffer[0];
            int u = queries[i].u;
            int v = queries[i].v;
            if (type == 'I') {
                path.clear();
                int x = find(u, v, i);
                if (x == -1 || x < id[u][v]) {
                    insert_edge(u, v);
                }
                if (x < id[u][v] && x != -1) {
                    int a = edges[x].first;
                    int b = edges[x].second;
                    delete_edge(a, b);
                }
            } else if (type == 'D') {
                delete_edge(u, v);
            } else {
                puts(u == v || reach(u, v, i) ? "YES" : "NO");
            }
        }
    }
    return 0;
}
