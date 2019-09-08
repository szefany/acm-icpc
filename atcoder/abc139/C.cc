#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 100000 + 10;

int a[N], n;

void run(int case_id = 0) {
  std::cin >> n;
  for (int i = 1; i <= n; ++ i) std::cin >> a[i];
  int result = 0;
  for (int i = 1; i <= n; ) {
    int j = i + 1;
    while (j <= n && a[j] <= a[j - 1]) j ++;
    update_max(result, j - i);
    i = j;
  }
  std::cout << result - 1 << "\n";
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
