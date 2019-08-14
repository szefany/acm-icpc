#include <bits/stdc++.h>

int main() {
  long long n, m, q;
  std::cin >> n >> m >> q;
  long long g = std::__gcd(n, m);
  while (q --) {
    long long x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    x1 --, y1 --, x2 --, y2 --;
    if (x1 == 0) {
      y1 /= n / g;
    } else {
      y1 /= m / g;
    }
    if (x2 == 0) {
      y2 /= n / g;
    } else {
      y2 /= m / g;
    }
    puts(y1 == y2 ? "YES" : "NO");
  }
  return 0;
}
