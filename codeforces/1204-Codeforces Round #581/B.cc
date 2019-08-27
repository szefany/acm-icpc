#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 1000 + 10;

int a[N];
int n, l, r;

long long min_sum() {
  int num_diff = 0;
  for (int i = 1; i <= n; ++ i) {
    if (num_diff < l) {
      a[i] = 1 << num_diff;
      num_diff ++;
    } else {
      a[i] = 1;
    }
  }
  long long result = 0;
  for (int i = 1; i <= n; ++ i) {
    result += a[i];
  }
  return result;
}

long long max_sum() {
  int num_diff = 0;
  for (int i = 1; i <= n; ++ i) {
    if (num_diff < r) {
      a[i] = 1 << num_diff;
      num_diff ++;
    } else {
      a[i] = 1 << (num_diff - 1);
    }
  }
  long long result = 0;
  for (int i = 1; i <= n; ++ i) {
    result += a[i];
  }
  return result;
}

void run(int case_id = 0) {
  std::cin >> n >> l >> r;
  std::cout << min_sum() << " " << max_sum() << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
