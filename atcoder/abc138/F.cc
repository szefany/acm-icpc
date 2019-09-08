#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 200;
const int MOD = 1000000000 + 7;

int a[N], b[N];
long long dp[N][2][2][2];

long long get(int pivot, bool first, bool less, bool greater) {
  if (pivot == 0) {
    return 1;
  }
  if (dp[pivot][first][less][greater] != -1) {
    return dp[pivot][first][less][greater];
  }
  int lower_x = greater ? 0 : a[pivot];
  int lower_y = greater ? 0 : a[pivot];
  int upper_x = less ? 1 : b[pivot];
  int upper_y = less ? 1 : b[pivot];
  long long result = 0, temp = 0;
  for (int i = lower_y; i <= upper_y; ++ i) {
    if (first && i == 0) continue;
    for (int j = lower_x; j <= upper_x; ++ j) {
      if (first && j == 0) continue;
      if (i < j) continue;
      temp = get(pivot - 1, false, less || i < upper_y, greater || j > lower_x);
      result += temp;
      if (result >= MOD) result -= MOD;
    }
  }
  dp[pivot][first][less][greater] = result;
  return result;
}

long long solve(long long x, long long y) {
  int len_a = 0;
  while (x) {
    a[++ len_a] = x % 2;
    x /= 2;
  }

  int len_b = 0;
  while (y) {
    b[++ len_b] = y % 2;
    y /= 2;
  }

  long long result = 0;
  for (int len = len_b; len >= len_a; -- len) {
    result += get(len, true, len < len_b, len > len_a);
    if (result >= MOD) result -= MOD;
  }
  // std::cerr << y << " " << result << std::endl;
  return result;
}

void run(int case_id = 0) {
  memset(dp, -1, sizeof(dp));
  long long l, r;
  std::cin >> l >> r;
  long long answer = solve(l, r);
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
