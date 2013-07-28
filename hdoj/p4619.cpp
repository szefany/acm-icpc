#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1000 + 10;

struct Point {
    int x[2], y[2];
    void input(int type) {
        scanf("%d%d", &x[0], &y[0]);
        if (type == 0) {
            x[1] = x[0] + 1;
            y[1] = y[0];
        } else {
            x[1] = x[0];
            y[1] = y[0] + 1;
        }
    }
};

Point points[2][N];
std::vector<int> neighbors[N];
bool visit[N];
int links[N];
int n, m;

bool find(int u) {
    if (visit[u]) {
        return false;
    }
    visit[u] = true;
    for (int i = 0; i < neighbors[u].size(); ++ i) {
        int v = neighbors[u][i];
        if (links[v] == 0 || find(links[v])) {
            links[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    while (scanf("%d%d", &n, &m) && n + m > 0) {
        for (int i = 1; i <= n; ++ i) {
            neighbors[i].clear();
        }
        for (int i = 1; i <= n; ++ i) {
            points[0][i].input(0);
        }
        for (int i = 1; i <= m; ++ i) {
            points[1][i].input(1);
        }
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= m; ++ j) {
                bool flag = false;
                for (int a = 0; a < 2; ++ a) {
                    for (int b = 0; b < 2; ++ b) {
                        if (points[0][i].x[a] == points[1][j].x[b] && points[0][i].y[a] == points[1][j].y[b]) {
                            flag = true;
                        }
                    }
                }
                if (flag) {
                    neighbors[i].push_back(j);
                }
            }
        }
        memset(links, 0, sizeof(links));
        int total = 0;
        for (int i = 1; i <= n; ++ i) {
            memset(visit, 0, sizeof(visit));
            total += find(i);
        }
        printf("%d\n", n + m - total);
    }
    return 0;
}
