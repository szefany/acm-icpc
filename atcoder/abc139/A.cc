#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

void run(int case_id = 0) {
  std::string a, b;
  std::cin >> a;
  std::cin >> b;
  int answer = 0;
  for (int i = 0; i < a.length(); ++ i) {
    answer += a[i] == b[i];
  }
  std::cout << answer << "\n";
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
