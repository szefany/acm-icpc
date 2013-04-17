#include <cstdio>
#include <cstring>
#include <vector>

const int N = 100 + 1;
const int S = (1 << 17) + 1;
const double INF = 1E30;

double dp[20][S];
int magic[N];
double graph[N][N], dist[20][N][N];
int n, m, n_target, n_box, n_speed, n_magic;
std::vector<int> elements;

void initialise() {
    elements.clear();
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            graph[i][j] = INF;
        }
    }
}

int read() {
    int number;
    scanf("%d", &number);
    for (int i = 0; i < number; ++ i) {
        int x;
        scanf("%d", &x);
        elements.push_back(x - 1);
    }
    return number;
}

bool all_box(int mask) {
    for (int i = n_target; i < n_target + n_box; ++ i) {
        if ((1 << i & mask) == 0) {
            return false;
        }
    }
    return true;
}

bool all_target(int mask) {
    for (int i = 0; i < n_target; ++ i) {
        if ((1 << i & mask) == 0) {
            return false;
        }
    }
    return true;
}

double get_speed(int mask) {
    double result = 30;
    for (int i = 0; i < elements.size(); ++ i) {
        if (1 << i & mask && i >= n_target + n_box) {
            result += 5;
        }
    }
    return result;
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        scanf("%d%d", &n, &m);
        initialise();
        for (int i = 0; i < m; ++ i) {
            int u, v;
            double w;
            scanf("%d%d%lf", &u, &v, &w);
            u --, v --;
            graph[u][v] = graph[v][u] = std::min(graph[u][v], w);
        }
        n_target = read();
        n_box = read();
        n_speed = read();
        n_magic = read();

        memset(magic, -1, sizeof(magic));
        for (int i = n_target + n_box + n_speed; i < elements.size(); ++ i) {
            magic[elements[i]] = i - n_target - n_box - n_speed;
        }

        for (int mask = 0; mask < 1 << n_magic; ++ mask) {
            for (int i = 0; i < n; ++ i) {
                for (int j = i + 1; j < n; ++ j) {
                    dist[mask][i][j] = dist[mask][j][i] = graph[i][j];
                }
            }
            for (int k = 0; k < n; ++ k) {
                if (magic[k] != -1 && (1 << magic[k] & mask) == 0) {
                    continue;
                }
                for (int i = 0; i < n; ++ i) {
                    if (i != k) {
                        for (int j = 0; j < n; ++ j) {
                            if (i != j && j != k) {
                                dist[mask][i][j] = dist[mask][j][i] = std::min(dist[mask][i][j], dist[mask][i][k] + dist[mask][k][j]);
                            }
                        }
                    }
                }
            }
        }
        int total = n_target + n_box + n_speed + n_magic;
        for (int i = 0; i < total; ++ i) {
            for (int mask = 0; mask < 1 << total; ++ mask) {
                dp[i][mask] = -1;
            }
        }

        int start;
        scanf("%d", &start);
        start --;
        for (int i = 0; i < total; ++ i) {
            dp[i][1 << i] = (double)dist[0][start][elements[i]] / 30;
            if (i >= n_target + n_box + n_speed) {
                dp[i][1 << i] += 3;
            }
        }

        double answer = -1;
        for (int mask = 0; mask < 1 << total; ++ mask) {
            for (int i = 0; i < total; ++ i) {
                if (dp[i][mask] == -1 || (1 << i & mask) == 0) {
                    continue;
                }
                if (all_target(mask)) {
                    if (all_box(mask)) {
#define update(a, b) if ((a) == -1 || (b) < (a)) (a) = (b)
                        update(answer, dp[i][mask]);
                    }
                    continue;
                }
                int magic_mask = 0;
                for (int j = n_target + n_box + n_speed; j < elements.size(); ++ j) {
                    int x = j - (n_target + n_box + n_speed);
                    if (1 << j & mask) {
                        magic_mask |= 1 << x;
                    }
                }
                double v = get_speed(mask);
                for (int next = 0; next < total; ++ next) {
                    if (1 << next & mask) {
                        continue;
                    }
                    double temp = dist[magic_mask][elements[i]][elements[next]] / v;
                    if (next >= n_target + n_box + n_speed) {
                        temp += 3;
                    }
                    update(dp[next][mask | 1 << next], dp[i][mask] + temp);
                }
            }
        }
        printf("Case #%d: %.5f\n", t, answer);
    }
    return 0;
}
