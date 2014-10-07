#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>

long long sqr(long long x) {
  return x * x;
}

struct Point {
  long long x, y;
  Point(long long x = 0, long long y = 0) : x(x), y(y) {};

  long long Dist(const Point& o) const {
    return sqr(x - o.x) + sqr(y - o.y);
  }

  Point Rotate(const Point &o, int times) const {
    Point origin = *this;
    while (times --) {
      long long dx = origin.x - o.x;
      long long dy = origin.y - o.y;
      origin = Point(o.x - dy, o.y + dx);
    }
    return origin;
  }

  Point operator - (const Point& o) const {
    return Point(x - o.x, y - o.y);
  }
  bool operator < (const Point& o) const {
    return x < o.x || x == o.x && y < o.y;
  }
};

long long dot(const Point& a, const Point& b) {
  return a.x * b.x + a.y * b.y;
}
long long det(const Point& a, const Point& b) {
  return a.x * b.y - a.y * b.x;
}

Point p0;
bool cmp(const Point& a, const Point& b) {
  return det(a - p0, b - p0) > 0;
}

bool Check(std::vector<Point> points, std::vector<Point> center, int a, int b, int c, int d) {
  points[0] = points[0].Rotate(center[0], a);
  points[1] = points[1].Rotate(center[1], b);
  points[2] = points[2].Rotate(center[2], c);
  points[3] = points[3].Rotate(center[3], d);

  for (int i = 1; i < 4; ++ i) {
    if (points[i] < points[0]) {
      std::swap(points[0], points[i]);
    }
  }
  p0 = points[0];
  std::sort(points.begin() + 1, points.end(), cmp);

  long long dist = points[0].Dist(points[1]);
  if (dist == 0) {
    return false;
  }
  for (int i = 0; i < 4; ++ i) {
    int j = (i + 1) % 4;
    if (dist - points[i].Dist(points[j])) {
      return false;
    }
  }

  for (int i = 0; i < 4; ++ i) {
    int prev = (i + 3) % 4;
    int next = (i + 1) % 4;
    if (dot(points[i] - points[prev], points[next] - points[i])) {
      return false;
    }
  }
  return true;
}

int main() {
  freopen("C.in", "r", stdin);
  int test;
  scanf("%d", &test);
  while (test --) {
    std::vector<Point> points, center;
    for (int i = 0; i < 4; ++ i) {
      long long x, y, a, b;
      std::cin >> x >> y >> a >> b;
      points.push_back(Point(x, y));
      center.push_back(Point(a, b));
    }

    const int INF = 1 << 29;

    int answer = INF;
    for (int a = 0; a < 4; ++ a) {
      for (int b = 0; b < 4; ++ b) {
        for (int c = 0; c < 4; ++ c) {
          for (int d = 0; d < 4; ++ d) {
            if (a + b + c + d < answer && Check(points, center, a, b, c, d)) {
              answer = a + b + c + d;
            }
          }
        }
      }
    }
    printf("%d\n", answer == INF ? -1 : answer);
  }
  return 0;
}
