#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

void run(int case_id = 0) {
  int b, p, f, h, c;
  std::cin >> b >> p >> f >> h >> c;
  if (h < c) {
    std::swap(h, c);
    std::swap(p, f);
  }
  int number = std::min(b / 2, p);
  int profit = number * h;
  b -= number * 2;
  number = std::min(b / 2, f);
  profit += number * c;
  std::cout << profit << std::endl;
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
  multi_cases_main();
  return 0;
}
