#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 150;
const double INF = 1E20;
const double EPS = 1E-6;

double dist[N][N], slack[N], lx[N], ly[N], x[2][N], y[2][N];
bool visit[2][N];
int match[N];
int n;

int sgn (double x) {
    if (x < -EPS) {
        return -1;
    }
    return x < EPS ? 0 : 1;
}

bool find (int u) {
    visit[0][u] = true;
    for (int i = 0; i < n; ++ i) {
        if (visit[1][i]) continue;
        if (sgn (lx[u] + ly[i] - dist[u][i]) == 0) {
            visit[1][i] = true;
            if (match[i] == -1 || find (match[i])) {
                match[i] = u;
                return true;
            }
        }
        else {
            slack[i] = min (slack[i], lx[u] + ly[i] - dist[u][i]);
        }
    } 
    return false;
}

void KM() {
    for (int i = 0; i < n; ++ i) {
        lx[i] = -INF;
        ly[i] = 0;
        match[i] = -1;
    } 
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            lx[i] = max (lx[i], dist[i][j]);
        }
    }
    for (int u = 0; u < n; ++ u) {
        for (int i = 0; i < n; ++ i) {
            slack[i] = INF;
        }
        while (1) {
            memset (visit, 0, sizeof (visit));
            if (find (u)) {
                break;
            }
            double delta = INF;
            for (int i = 0; i < n; ++ i) {
                if (!visit[1][i]) {
                    delta = min (delta, slack[i]);
                }
            }
            for (int i = 0; i < n; ++ i) {
                if (visit[0][i]) {
                    lx[i] -= delta;
                }
                if (visit[1][i]) {
                    ly[i] += delta;
                } else {
                    slack[i] -= delta;
                }
            }
        }
    }
}

int main() {
    scanf ("%d", &n);
    for (int i = 0; i < 2; ++ i) {
        for (int j = 0; j < n; ++ j) {
            scanf ("%lf%lf", &x[i][j], &y[i][j]);
        }
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
#define sqr(x) ((x) * (x))
            dist[j][i] = (-1) * sqrt (sqr (x[0][i] - x[1][j]) + sqr (y[0][i] - y[1][j]));
        }
    }
    KM();
    for (int i = 0; i < n; ++ i) {
        printf("%d\n", match[i] + 1);
    }
    return 0;
}
