#include <bits/stdc++.h>

int main() {
  int n;
  std::cin >> n;
  long long g = -1;
  for (int i = 1; i <= n; ++ i) {
    long long x;
    std::cin >> x;
    if (g == -1) {
      g = x;
    } else {
      g = std::__gcd(g, x);
    }
  }

  int answer = 0;
  for (long long x = 1; x * x <= g; ++ x) {
    if (g % x == 0) {
      answer ++;
      if (x * x != g) answer ++;
    }
  }
  std::cout << answer << '\n';
  return 0;
}
