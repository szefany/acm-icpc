#include <bits/stdc++.h>

const int N = 400000 + 10;

std::pair<int, int> a[N];
int max_value[N];
int n, q;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin >> n;
  for (int i = 1; i <= n; ++ i) {
    int x;
    std::cin >> x;
    a[i] = std::make_pair(x, 0);
  }
  std::cin >> q;
  for (int i = 1; i <= q; ++ i) {
    int oper;
    std::cin >> oper;
    if (oper == 1) {
      int p, x;
      std::cin >> p >> x;
      a[p] = std::make_pair(x, i);
    } else {
      int x;
      std::cin >> x;
      max_value[i] = x;
    }
  }
  for (int i = q; i >= 0; -- i) {
    max_value[i] = std::max(max_value[i + 1], max_value[i]);
  }
  for (int i = 1; i <= n; ++ i) {
    int result = std::max(a[i].first, max_value[a[i].second]);
    std::cout << result << " ";
  }
  std::cout << "\n";
  return 0;
}
