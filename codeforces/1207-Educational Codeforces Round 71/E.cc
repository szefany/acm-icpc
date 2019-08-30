#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 100;

long long a[N];

long long query() {
  std::cout << "?";
  for (int i = 0; i < 100; ++ i) {
    std::cout << " " << a[i];
  }
  std::cout << std::endl;
  std::cout.flush();
  long long x;
  std::cin >> x;
  return x;
}

void run(int case_id = 0) {
  for (int i = 0; i < 100; ++ i) {
    a[i] = i + 1;
  }
  long long x = query();
  long long m = (1LL << 14) - 1;
  long long answer = x & (m ^ 127);

  for (int i = 0; i < 100; ++ i) {
    a[i] <<= 7;
  }
  long long y = query();
  answer |= y & 127;
  std::cout << "! " << answer << std::endl;
  std::cout.flush();
}

int main() {
  run();
  return 0;
}
