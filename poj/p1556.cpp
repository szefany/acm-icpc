// POJ 1556, The Doors
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <deque>
using namespace std;

const int N = 100;
const double EPS = 1e-6;

struct Point {
    Point () {}
    Point (double _x, double _y): x(_x), y(_y) {}
    double x, y;
    Point operator - (const Point &other) {
        return Point (x - other.x, y - other.y);
    }
};

struct Segment {
    Segment () {}
    Segment (Point _a, Point _b): a(_a), b(_b) {}
    Point a, b;
} segments[N];

Point nodes[N];
double g[N][N], dist[N];
bool inqueue[N];
int n, nodeCount, counter;

double Distance (Point a, Point b) {
#define sqr(x) (x) * (x)
    return sqrt (sqr (a.x - b.x) + sqr (a.y - b.y));
}

int sgn (double x) {
    if (x < -EPS) return -1;
    return x < EPS ? 0 : 1;
}

double det (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

bool intersect (Point a, Point b, Point c, Point d) {
    int d1 = sgn (det (b - a, c - a));
    int d2 = sgn (det (b - a, d - a));
    int d3 = sgn (det (d - c, a - c));
    int d4 = sgn (det (d - c, b - c));
    return (d1 ^ d2) == -2 && (d3 ^ d4) == -2;
}

void insert (Point a, int u) {
    for (int i = 1; i <= counter; ++ i) {
        bool flag = true;
        for (int j = 1; j <= nodeCount; ++ j) {
            if (intersect (a, nodes[i], segments[j].a, segments[j].b)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            g[u][i] = g[i][u] = Distance (a, nodes[i]);
        }
    }
}

void init () {
    for (int i = 1; i < N; ++ i) {
        for (int j = 1; j < N; ++ j) {
            g[i][j] = 1e10;
        }
    }
}

int main () {
    freopen ("input.txt", "r", stdin);
    while (scanf ("%d", &n) != EOF && n != -1) {
        init();
        nodeCount = counter = 0;
        for (int i = 1; i <= n; ++ i) {
            double x, y1, y2, y3, y4;
            scanf ("%lf%lf%lf%lf%lf", &x, &y1, &y2, &y3, &y4);
            if (sgn (y1) > 0) {
                nodeCount ++;
                segments[nodeCount] = Segment (Point (x, 0), Point (x, y1));
            }
            nodeCount ++;
            segments[nodeCount] = Segment (Point (x, y2), Point (x, y3));
            if (sgn (y4 - 10)) {
                nodeCount ++;
                segments[nodeCount] = Segment (Point (x, y4), Point (x, 10));
            }
            nodes[++ counter] = Point (x, y1);
            nodes[++ counter] = Point (x, y2);
            nodes[++ counter] = Point (x, y3);
            nodes[++ counter] = Point (x, y4);
        }
        int vs = counter + 1;
        int vt = counter + 2;
        nodes[++ counter] = Point (0, 5);
        nodes[++ counter] = Point (10, 5);
        for (int i = 1; i <= counter; ++ i) {
            insert (nodes[i], i);
        }
        n = counter;
        for (int i = 1; i <= n; ++ i) {
            dist[i] = 1e10;
        }
        memset (inqueue, 0, sizeof (inqueue));
        dist[vs] = 0, inqueue[vs] = true;
        deque<int> queue;
        queue.push_back (vs);
        while (!queue.empty()) {
            int u = queue.front();
            queue.pop_front();
            inqueue[u] = false;
            for (int i = 1; i <= n; ++ i) {
                if (dist[u] + g[u][i] < dist[i]) {
                    dist[i] = dist[u] + g[u][i];
                    if (!inqueue[i]) {
                        inqueue[i] = true;
                        queue.push_back (i);
                    }
                }
            }
        }
        printf ("%.2f\n", dist[vt]);
    } 
    return 0;
}
