#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

void run(int case_id = 0) {
  int a, b;
  std::cin >> a >> b;
  int result = 0;
  if (b == 1) {
    result = 0;
  } else {
    int x = 1;
    while (x < b) {
      x = x - 1 + a;
      result ++;
    }
  }
  std::cout << result << "\n";
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
