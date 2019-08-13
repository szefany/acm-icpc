#include <bits/stdc++.h>

int main() {
  int k, x;
  std::cin >> k >> x;
  std::vector<int> answer;
  for (int i = std::max(-1000000, x - k + 1); i <= std::min(1000000, x + k - 1); ++ i) {
    answer.push_back(i);
  }
  for (int i = 0; i < answer.size(); ++ i) {
    printf("%d%c", answer[i], i + 1 == answer.size() ? '\n' : ' ');
  }
  return 0;
}
