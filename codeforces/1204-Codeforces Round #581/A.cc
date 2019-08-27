#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

void run(int case_id = 0) {
  std::string s;
  std::cin >> s;
  int answer = 0;
  int pivot = s.length() - 1;
  bool valid = false;
  while (pivot >= 1) {
    if (s[pivot] != '0' || s[pivot - 1] != '0') {
      valid = true;
    }
    answer ++;
    pivot -= 2;
  }
  if (pivot == 0 && valid) answer ++;
  std::cout << answer << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
