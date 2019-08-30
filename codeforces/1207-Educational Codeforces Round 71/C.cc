#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

const int N = 200000 + 10;
const long long INF = 1LL << 50;

char road[N];
long long dp[N][2];
int n, a, b;

int cost(int now, int next) {
  int result = (next + 1) * b + a;
  if (now != next) result += a;
  return result;
}

void update_min(long long& x, long long y) {
  if (x == -1 || y < x) x = y;
}

void run(int case_id = 0) {
  std::cin >> n >> a >> b;
  std::cin >> road;

  memset(dp, -1, sizeof(dp));
  dp[0][0] = b;
  for (int i = 0; i < n; ++ i) {
    for (int now = 0; now < 2; ++ now) {
      if (dp[i][now] == -1) continue;
      if (road[i] == '1' && now == 0) continue;
      for (int next = 0; next < 2; ++ next) {
        if (road[i] == '1' && next == 0) continue;
        update_min(dp[i + 1][next], dp[i][now] + cost(now, next));
      }
    }
  }
  std::cout << dp[n][0] << "\n";
}

void multi_cases_main() {
  int num_tests;
  std::cin >> num_tests;
  for (int t = 1; t <= num_tests; ++ t) {
    run(t);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  multi_cases_main();
  return 0;
}
