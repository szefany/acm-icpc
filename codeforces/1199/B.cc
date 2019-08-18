#include <bits/stdc++.h>

int main() {
  double h, l;
  std::cin >> h >> l;
  std::cout << std::setprecision(9) << std::fixed;
  std::cout << (l * l - h * h) / 2 / h << std::endl;
  return 0;
}
