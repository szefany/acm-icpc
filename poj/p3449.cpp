// POJ 3449, Geometric Shapes
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 30;
const double EPS = 1e-6;

struct Point {
    double x, y;
    char name[2];
    Point () {}
    Point (double x1, double y1): x(x1), y(y1) {}
    Point operator - (const Point &other) {
        return Point (x - other.x, y - other.y);
    }
    void input () {
        scanf (" (%lf,%lf)", &x, &y);
    }
};

struct Segment {
    Point a, b;
    char name[2];
    Segment () {}
    Segment (Point a1, Point b1): a(a1), b(b1) {}
};

struct Polygon {
    vector <Point> points;
    char name[2];
};

int n;
bool visit[N];
vector<Segment> segments;
vector<Polygon> polygons;
vector<char> ans[N];

void init () {
    memset (visit, 0, sizeof (visit));
    for (int i = 0; i < 26; ++ i) {
        ans[i].clear ();
    }
    segments.clear ();
    polygons.clear ();
}

double det (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double dot (Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

int sgn (double x) {
    if (x < -EPS) {
        return -1;
    }
    return x < EPS ? 0 : 1;
}

bool on_segment (Point p, Segment u) {
    return sgn (det (p - u.a, p - u.b)) == 0 && sgn (dot (p - u.a, p - u.b)) <= 0;
}

bool intersect (Segment u, Segment v) {
    if (on_segment (u.a, v) && on_segment (u.b, v) || on_segment (v.a, u) && on_segment (v.b, u)) {
        return false;
    }
    int d1 = sgn (det (u.b - u.a, v.a - u.a));
    int d2 = sgn (det (u.b - u.a, v.b - u.a));
    int d3 = sgn (det (v.b - v.a, u.a - v.a));
    int d4 = sgn (det (v.b - v.a, u.b - v.a));
    if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return true;
    return d1 == 0 && sgn (dot (v.a - u.a, v.a - u.b)) <= 0 \
        || d2 == 0 && sgn (dot (v.b - u.a, v.b - u.b)) <= 0 \
        || d3 == 0 && sgn (dot (u.a - v.a, u.a - v.b)) <= 0 \
        || d4 == 0 && sgn (dot (u.b - v.a, u.b - v.b)) <= 0;
}

bool in_polygon (Point p, Polygon u) {
    // Judge whether the point is on the edges
    for (int i = 0; i + 1 < u.points.size(); ++ i) {
        if (on_segment (p, Segment (u.points[i], u.points[i + 1]))) {
            return true;            
        }
    }
    // Judge whether it is inside the polygon
    int counter[2] = {0};
    for (int i = 1; i < u.points.size(); ++ i) {
        Point last = u.points[i - 1];
        Point now = u.points[i];
        if (sgn (last.y - p.y) < 0 && sgn (now.y - p.y) >= 0 ||
            sgn (now.y - p.y) < 0 && sgn (last.y - p.y) >= 0) {
            double x = (p.y - last.y) * (now.x - last.x) / (now.y - last.y) + last.x;
            if (sgn (x - p.x) < 0) {
                counter[0] ++;
            }
            else {
                counter[1] ++;
            }
        }
    }
    return (counter[0] & 1) && (counter[1] & 1);
}

bool intersect (Polygon p, Polygon q) {
    for (int i = 0; i + 1 < p.points.size(); ++ i) {
        for (int j = 0; j + 1 < q.points.size(); ++ j) {
            if (intersect (Segment (p.points[i], p.points[i + 1]), Segment (q.points[j], q.points[j + 1]))) {
                return true;
            }
        }
    }
    return false;
}

bool intersect (Segment s, Polygon p) {
    for (int i = 0; i + 1 < p.points.size(); ++ i) {
        if (intersect (s, Segment (p.points[i], p.points[i + 1]))) {
            return true;
        }
    }
    return false;
}

void get_square_point (Point &a, Point &b, Point &c, Point &d) {
    /*
        Given the opposite corner points a and b of the square, return the other two points
    */
    c.x = (a.x + b.x + a.y - b.y) / 2;
    c.y = (-a.x + b.x + a.y + b.y) / 2;
    d.x = (a.x + b.x - a.y + b.y) / 2;
    d.y = (a.x - b.x + a.y + b.y) / 2;
}

Point symmetry_point (Point a, Point b) {
    return Point (2 * b.x - a.x, 2 * b.y - a.y);
}

void get_rectangle_point (Point &a, Point &b, Point &c, Point &d) {
    /*
        Given three points of a rectangle(forming angle ABC as a right angle), return the other point D
    */
    Point centre ((a.x + c.x) / 2, (a.y + c.y) / 2);
    d = symmetry_point (b, centre);
}

void insert (vector<Point> &v, Point a, Point b, Point c, Point d) {
    v.push_back (a);
    v.push_back (b);
    v.push_back (c);
    v.push_back (d);
}

int main () {
    char name[2];
    while (scanf ("%s", name) != EOF) {
        if (*name == '.') {
            break;
        }
        init ();
        char buffer[10];
        n = 0;
        while (*name != '-') {
            n ++;
            scanf ("%s", buffer);
            if (*buffer == 'l') {
                Segment s;
                s.a.input ();
                s.b.input ();
                strcpy (s.name, name);
                segments.push_back (s);
            }
            else {
                int counter = 0;
                Polygon p;
                strcpy (p.name, name);
                if (*buffer == 's') {
                    Point a, b, c, d;
                    a.input ();
                    b.input ();
                    get_square_point (a, b, c, d);
                    insert (p.points, a, c, b, d);
                }
                else if (*buffer == 'r') {
                    Point a, b, c, d;
                    a.input ();
                    b.input ();
                    c.input ();
                    get_rectangle_point (a, b, c, d);
                    insert (p.points, a, b, c, d);    
                }
                else {
                    if (*buffer == 't') {
                        counter = 3;
                    }
                    else {
                        scanf ("%d", &counter);
                    }
                    while (counter --) {
                        Point a;
                        a.input ();
                        p.points.push_back (a);
                    }
                }
                p.points.push_back (p.points[0]);
                polygons.push_back (p);
            }
            scanf ("%s", name);
        }
        for (int i = 0; i < segments.size(); ++ i) {
            int index = *segments[i].name - 'A';
            visit[index] = true;
            for (int j = 0; j < segments.size(); ++ j) {
                if (i == j) {
                    continue;
                }
                if (intersect (segments[i], segments[j])) {
                    ans[index].push_back (*segments[j].name - 'A');
                }
            }
            for (int j = 0; j < polygons.size(); ++ j) {
                if (intersect (segments[i], polygons[j])) {
                    ans[index].push_back (*polygons[j].name - 'A');
                }
            }
        }
        for (int i = 0; i < polygons.size(); ++ i) {
            int index = *polygons[i].name - 'A';
            visit[index] = true;
            for (int j = 0; j < polygons.size(); ++ j) {
                if (i == j) {
                    continue;
                }
                if (intersect (polygons[i], polygons[j])) {
                    ans[index].push_back (*polygons[j].name - 'A');
                }
            }
            for (int j = 0 ; j < segments.size(); ++ j) {
                if (intersect (segments[j], polygons[i])) {
                    ans[index].push_back (*segments[j].name - 'A');
                }
            }
        }
        for (int i = 0; i < 26; ++ i) {
            if (!visit[i]) {
                continue;
            }
            sort (ans[i].begin(), ans[i].end());
            if (ans[i].size() == 0) {
                printf ("%c has no intersections\n", i + 'A');
            }
            else {
                printf ("%c intersects with", i + 'A');
                if (ans[i].size() == 1) {
                    printf (" %c\n", ans[i][0] + 'A');
                }
                else if (ans[i].size() == 2) {
                    printf (" %c and %c\n", ans[i][0] + 'A', ans[i][1] + 'A');
                }
                else {
                    for (int j = 0; j < ans[i].size() - 1; ++ j) {
                        printf (" %c,", ans[i][j] + 'A');
                    }
                    printf (" and %c\n", ans[i][ans[i].size() - 1] + 'A');
                }
            }
        }
        puts ("");
    }
    return 0;
}
