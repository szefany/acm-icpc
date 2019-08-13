#include <bits/stdc++.h>

int main() {
  int a, b;
  std::cin >> a >> b;
  int answer = std::max(std::max(a + b, a - b), a * b);
  std::cout << answer << std::endl;
  return 0;
}
