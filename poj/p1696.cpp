// POJ 1696, Space Ant
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 100;
const double EPS = 1e-6;

struct Point {
    double x, y;
} points[N];

bool visit[N];
int stack[N], length;
int n;

int sgn (double x) {
    if (x < -EPS) return -1;
    return x < EPS ? 0 : 1;
}

double dist (Point a, Point b) {
#define sqr(x) (x) * (x)
    return sqrt (sqr (a.x - b.x) + sqr (a.y - b.y));
}

double det (Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int main () {
    freopen ("input.txt", "r", stdin);
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        scanf ("%d", &n);
        int start = 0;
        for (int i = 1; i <= n; ++ i) {
            scanf ("%*d%lf%lf", &points[i].x, &points[i].y);
            if (start == 0 || points[i].y < points[start].y || sgn (points[i].y - points[start].y) == 0 && points[i].x < points[start].x) {
                start = i;
            }
        }
        memset (visit, 0, sizeof (visit));
        stack[1] = start, length = 1;
        visit[start] = true;
        for (int counter = 1; counter <= n; ++ counter) {
            int next = 0;
            for (int i = 1; i <= n; ++ i) {
                if (visit[i]) continue;
                double temp = det (points[stack[counter]], points[i], points[next]);
                if (next == 0 || sgn (temp) > 0 || sgn (temp) == 0 && dist (points[stack[counter]], points[i]) < dist (points[stack[counter]], points[next])) {
                    next = i;
                }
            }
            visit[next] = true;
            stack[counter + 1] = next;
        }
        printf ("%d ", n);
        for (int i = 1; i <= n; ++ i) {
            printf ("%d%c", stack[i], i == n ? '\n' : ' ');
        }
    }
    return 0;
}
