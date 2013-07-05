#include <cstdio>
#include <vector>

const int N = 200 + 10;
const double EPS = 1E-8;

int sgn(double x) {
    return x < -EPS ? -1 : x > EPS;
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    Point operator - (const Point &other) {
        return Point(x - other.x, y - other.y);
    }
    void input() {
        scanf("%lf%lf", &x, &y);
    }
};

double det(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

struct Segment {
    Point a, b;
    Segment() {}
    Segment(Point a, Point b): a(a), b(b) {}
};

bool cross (Segment u, Segment v) {
    int d1 = sgn (det (u.b - u.a, v.a - u.a));
    int d2 = sgn (det (u.b - u.a, v.b - u.a));
    int d3 = sgn (det (v.b - v.a, u.a - v.a));
    int d4 = sgn (det (v.b - v.a, u.b - v.a));
    if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return true;
    return (d1 == 0 && sgn (dot (v.a - u.a, v.a - u.b)) <= 0
        || d2 == 0 && sgn (dot (v.b - u.a, v.b - u.b)) <= 0
        || d3 == 0 && sgn (dot (u.a - v.a, u.a - v.b)) <= 0
        || d4 == 0 && sgn (dot (u.b - v.a, u.b - v.b)) <= 0);
}

bool on_segment (Point p, Point a, Point b) {
    return sgn(det(p - a, p - b)) == 0 && sgn(dot(p - a, p - b)) <= 0;
}

int ancestor[N];

int find(int u) {
    int root = u;
    while (root != ancestor[root]) {
        root = ancestor[root];
    }
    while (u != root) {
        int temp = ancestor[u];
        ancestor[u] = root;
        u = temp;
    }
    return root;
}

void joint(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) {
        ancestor[u] = v;
    }
}

struct Edge {
    int u, v;
    Edge(int u = 0, int v = 0): u(u), v(v) {}
    void input() {
        scanf("%d%d", &u, &v);
    }
};

Point points[N];
Edge edges[N];
int n, m;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        points[i].input();
        ancestor[i] = i;
    }
    for (int i = 1; i <= m; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        edges[i] = Edge(u, v);
        joint(u, v);
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            int u = edges[j].u;
            int v = edges[j].v;
            if (on_segment(points[i], points[u], points[v])) {
                joint(i, u);
            }
        }
    }
    for (int i = 1; i <= m; ++ i) {
        int a = edges[i].u;
        int b = edges[i].v;
        for (int j = i + 1; j <= m; ++ j) {
            int c = edges[j].u;
            int d = edges[j].v;
            if (cross(Segment(points[a], points[b]), Segment(points[c], points[d]))) {
                joint(a, c);
            }
        }
    }
    int answer = 0;
    for (int i = 1; i <= n; ++ i) {
        answer += i == find(i);
    }
    puts(answer == 1 ? "YES" : "NO");
    return 0;
}
