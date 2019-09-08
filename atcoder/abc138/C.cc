#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 100;

int a[N], n;

void run(int case_id = 0) {
  std::priority_queue<double, std::vector<double>, std::greater<double> > heap;
  std::cin >> n;
  for (int i = 1; i <= n; ++ i) {
    std::cin >> a[i];
    heap.push(a[i]);
  }

  double answer = 0;
  while (!heap.empty()) {
    double x = heap.top();
    heap.pop();
    if (heap.empty()) {
      answer = x;
      break;
    }
    double y = heap.top();
    heap.pop();
    heap.push((x + y) / 2);
  }
  std::cout << std::setprecision(9) << std::fixed;
  std::cout << answer << std::endl;
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
