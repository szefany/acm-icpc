#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

void run(int case_id = 0) {
  int n;
  std::cin >> n;
  double answer = 0;
  for (int i = 1; i <= n; ++ i) {
    double x;
    std::cin >> x;
    answer += 1.0 / x;
  }
  std::cout << std::setprecision(9) << std::fixed;
  std::cout << 1.0 / answer << std::endl;
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
