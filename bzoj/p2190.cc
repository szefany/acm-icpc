#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 40000 + 10;

int phi[N], n;

void run(int case_id = 0) {
  std::cin >> n;
  for (int i = 1; i <= n; ++ i) phi[i] = i;
  for (int i = 2; i <= n; ++ i) {
    if (phi[i] == i) {
      for (int j = i; j <= n; j += i) {
        phi[j] = phi[j] / i * (i - 1);
      }
    }
  }

  long long answer = 0;
  for (int i = 1; i <= n - 1; ++ i) {
    answer += phi[i];
  }
  std::cout << answer * 2 + 1 << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
