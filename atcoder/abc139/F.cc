#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 100 + 10;

struct Point {
  long long x, y;

  Point(long long x = 0, long long y = 0) : x(x), y(y) {}

  void input() {
    std::cin >> x >> y;
  }
} points[N];

int n;

bool cmp(const Point& a, const Point& b) {
  return atan2(a.y, a.x) < atan2(b.y, b.x);
}

void run(int case_id = 0) {
  std::cin >> n;
  for (int i = 0; i < n; ++ i) {
    points[i].input();
  }
  std::sort(points, points + n, cmp);

  long long answer = 0;
  for (int i = 0; i < n; ++ i) {
    Point p;
    for (int length = 0; length < n; ++ length) {
      int j = (i + length) % n;
      p.x += points[j].x;
      p.y += points[j].y;
      update_max(answer, p.x * p.x + p.y * p.y);
    }
  }

  std::cout << std::setprecision(12) << std::fixed;
  std::cout << sqrt(answer * 1.0) << "\n";
}

void multi_cases_main() {
  int num_tests;
  std::cin >> num_tests;
  for (int t = 1; t <= num_tests; ++ t) {
    run(t);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
