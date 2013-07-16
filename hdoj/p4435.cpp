#include <cstdio>
#include <cmath>
#include <cstring>

const double EPS = 1E-8;

struct Point {
    int x, y;
    void input() {
        scanf("%d%d", &x, &y);
    }
};

#define sqr(x) ((x) * (x))
int get_dist(const Point &a, const Point &b) {
    return ceil(sqrt((double)sqr(a.x - b.x) + sqr(a.y - b.y)));
}
int get_dist2(const Point &a, const Point &b) {
    int x = ceil(sqrt((double)sqr(a.x - b.x) + sqr(a.y - b.y)));
    return x * 2;
}

const int N = 130;

Point points[N];
bool built[N];
int n, d;

int queue[N];
bool visit[N];

bool check(int id) {
    memset(visit, 0, sizeof(visit));
    visit[1] = true;
    queue[0] = 1;
    for (int head = 0, tail = 0; head <= tail; ++ head) {
        int u = queue[head];
        for (int i = 1; i <= n; ++ i) {
            if ((i < id || built[i]) && get_dist(points[u], points[i]) <= d && !visit[i]) {
                visit[i] = true;
                queue[++ tail] = i;
            }
        }
    }
    for (int i = 1; i <= n; ++ i) {
        if ((built[i] || i < id) && !visit[i]) {
            return false;
        }
    }
    for (int i = id; i <= n; ++ i) {
        if (!built[i]) {
            bool flag = false;
            for (int j = 1; j <= n; ++ j) {
                if ((built[j] || j < id) && get_dist2(points[i], points[j]) <= d) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    while (scanf("%d%d", &n, &d) != EOF) {
        for (int i = 1; i <= n; ++ i) {
            points[i].input();
        }
        if (n == 1) {
            puts("1");
            continue;
        }
        memset(built, 0, sizeof(built));
        built[1] = true;
        if (!check(n + 1)) {
            puts("-1");
            continue;
        }
        for (int i = n; i >= 2; -- i) {
            built[i] = !check(i);
        }
        bool first = true;
        for (int i = n; i >= 1; -- i) {
            if (built[i] || !first) {
                putchar(built[i] ? '1' : '0');
                first = false;
            }
        }
        puts("");
    }
    return 0;
}
