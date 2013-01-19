// POJ 1066, Treasure Hunt
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100;
const double EPS = 1E-6;

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

int n;
double vx, vy;
vector<double> board[4];
// 0: W, 1: S, 2: E, 3: N

int sgn (double x) {
    if (x < -EPS) return -1;
    return x < EPS ? 0 : 1;
}

double det (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

bool intersect (Segment u, Segment v) {
    int d1 = sgn (det (u.b - u.a, v.a - u.a));
    int d2 = sgn (det (u.b - u.a, v.b - u.a));
    int d3 = sgn (det (v.b - v.a, u.a - v.a));
    int d4 = sgn (det (v.b - v.a, u.b - v.a));
    return (d1 ^ d2) == -2 && (d3 ^ d4) == -2;
}

void insert (double x, double y) {
    if (sgn (x) == 0) {
        board[0].push_back (y);
    }
    else if (sgn (x - 100) == 0) {
        board[2].push_back (y);
    }
    else if (sgn (y) == 0) {
        board[1].push_back (x);
    }
    else {
        board[3].push_back (x);
    }
}

int solve (double x, double y) {
    Segment s (Point (x, y), Point (vx, vy));
    int result = 0;
    for (int i = 1; i <= n; ++ i) {
        result += intersect (s, segments[i]);
    }
    return result;
}

int main () {
    freopen ("input.txt", "r", stdin);
    scanf ("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        double x1, y1, x2, y2;
        scanf ("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        segments[i] = Segment (Point (x1, y1), Point (x2, y2));
        insert (x1, y1);
        insert (x2, y2);
    }
    for (int i = 0; i < 4; ++ i) {
        board[i].push_back (0);
        board[i].push_back (100);
        sort (board[i].begin(), board[i].end());
    }
    scanf ("%lf%lf", &vx, &vy);
    int ans = 1 << 20;
    for (int i = 1; i < board[0].size(); ++ i) {
        if (sgn (board[0][i] - board[0][i - 1]) == 0) continue;
        int temp = solve (0, (board[0][i] + board[0][i - 1]) / 2);
        if (temp < ans) ans = temp;
    }
    for (int i = 1; i < board[1].size(); ++ i) {
        if (sgn (board[1][i] - board[1][i - 1]) == 0) continue;
        int temp = solve ((board[1][i] + board[1][i]) / 2, 0);
        if (temp < ans) ans = temp;
    }
    for (int i = 1; i < board[2].size(); ++ i) {
        if (sgn (board[2][i] - board[2][i - 1]) == 0) continue;
        int temp = solve (100, (board[2][i] + board[2][i - 1]) / 2);
        if (temp < ans) ans = temp;
    }
    for (int i = 1; i < board[3].size(); ++ i) {
        if (sgn (board[3][i] - board[3][i - 1]) == 0) continue;
        int temp = solve ((board[3][i] + board[3][i - 1]) / 2, 100);
        if (temp < ans) ans = temp;
    }
    printf ("Number of doors = %d\n", ans + 1);
    return 0;
}

