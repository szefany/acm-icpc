#include <bits/stdc++.h>

const int N = 100000 + 10;

int a[N], n, x, y;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin >> n >> x >> y;
  for (int i = 1; i <= n; ++ i) {
    std::cin >> a[i];
  }
  int found = 0;
  for (int i = 1; i <= n; ++ i) {
    bool valid = true;
    for (int j = std::max(1, i - x); j < i; ++ j) {
      valid &= a[i] < a[j];
    }
    for (int j = i + 1; j <= std::min(n, i + y); ++ j) {
      valid &= a[i] < a[j];
    }
    if (valid) {
      found = i;
      break;
    }
  }
  std::cout << found << std::endl;
  return 0;
}
