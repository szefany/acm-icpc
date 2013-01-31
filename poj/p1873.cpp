// POJ 1873, The Fortified Forest
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 20;
const int M = 1 << N;
const double EPS = 1E-8;

struct Point {
    int x, y;
    Point () {}
    Point (int x0, int y0): x (x0), y (y0) {}
    Point operator - (const Point &other) {
        return Point (x - other.x, y - other.y);
    }
};

int sgn (double key) {
    if (key < -EPS) {
        return -1;
    }
    return key < EPS ? 0 : 1;
}

double det (Point p, Point q) {
    return p.x * q.y - p.y * q.x;
}

double dist (Point a, Point b) {
#define sqr(x) ((x) * (x))
    return sqrt (sqr ((double)a.x - b.x) + sqr ((double)a.y - b.y));
}

Point p0;
bool cmp (Point p, Point q) {
    int flag = det (p - p0, q - p0);
    if (flag != 0) {
        return flag > 0;
    }
    return dist (p, p0) > dist (q, p0);
}

struct Polygon {
    static const int N = 50;
    Point points[N];
    int size;
    Polygon () {size = 0;}
    void push (Point p) {
        points[size ++] = p;
    }
    double convex_perimeter () {
        if (size < 2) {
            return 0;
        }
        if (size == 2) {
            return 2 * dist (points[0], points[1]);
        }
        int id = 0;
        for (int i = 1; i < size; ++ i) {
            int flag = points[i].x - points[id].x;
            if (flag < 0 || flag == 0 && points[i].y < points[id].y) {
                id = i;
            }
        }
        swap (points[0], points[id]);
        p0 = points[0];
        sort (points + 1, points + size, cmp);
        Polygon convex;
        int &top = convex.size;
        for (int i = 0; i < 3; ++ i) {
            convex.push (points[i]);
        }
        for (int i = 3; i <= size; ++ i) {
            int now = i % size;
            while (top > 2 && sgn (det (convex.points[top - 1] - points[now], \
                convex.points[top - 2] - points[now])) > 0) {
                top --;
            }
            convex.push (points[now]);
        }
        double result = 0;
        for (int i = 0; i + 1 < top; ++ i) {
            result += dist (convex.points[i], convex.points[i + 1]);
        }
        return result;
    }
};

int x[N], y[N], values[N], length[N];
int mask_values[M];
double extra[M];
int n;

double solve (int mask) {
    Polygon poly;
    double materials = 0;
    for (int i = 0; i < n; ++ i) {
        if (1 << i & mask) {
            poly.push (Point (x[i], y[i]));
        }
        else {
            materials += length[i];
        }
    }
    double need = poly.convex_perimeter ();
    if (sgn (materials - need) < 0) {
        return -1;
    }
    return materials - need;
}

int main () {
    int test_count = 0;
    while (scanf ("%d", &n) != EOF && n > 0) {
        int total_values = 0;
        for (int i = 0; i < n; ++ i) {
            scanf ("%d%d%d%d", &x[i], &y[i], &values[i], &length[i]);
            total_values += values[i];
        }
        int id = -1;
        for (int mask = 0; mask < 1 << n; ++ mask) {
            extra[mask] = solve (mask);
            if (sgn (extra[mask]) < 0) {
                continue;
            }
            mask_values[mask] = 0;
            for (int i = 0; i < n; ++ i) {
                if (1 << i & mask) {
                    mask_values[mask] += values[i];
                }
            }
            mask_values[mask] = total_values - mask_values[mask];
            if (id == -1 || mask_values[mask] < mask_values[id] || mask_values[mask] == mask_values[id] \
                && __builtin_popcount (mask) > __builtin_popcount (id)) {
                id = mask;
            }
        }
        vector <int> output;
        double remain;
        if (id > 0) {
            remain = extra[id];
        }
        if (n == 2) {
            int k = values[0] <= values[1] ? 0 : 1;
            output.push_back (k + 1);
            remain = length[k];
        }
        else {
            for (int i = 0; i < n; ++ i) {
                if ((1 << i & id) == 0) {
                    output.push_back (i + 1);
                }
            }
        }
        if (test_count > 0) {
            puts ("");
        }
        printf ("Forest %d\n", ++ test_count);
        printf ("Cut these trees: ");
        for (int i = 0; i < output.size(); ++ i) {
            printf ("%d%c", output[i], i == output.size() - 1 ? '\n' : ' ');
        }
        printf ("Extra wood: %.2f\n", remain);
    }
    return 0;
}
