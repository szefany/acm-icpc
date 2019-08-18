#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 52;

char board[N][N];
int sum[N][N];
int dp[N][N][N][N], n;

void run(int case_id = 0) {
  std::cin >> n;
  for (int i = 1; i <= n; ++ i) {
    std::cin >> board[i] + 1;
  }
  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= n; ++ j) {
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (board[i][j] == '#');
    }
  }
  memset(dp, 60, sizeof(dp));

  for (int w = 1; w <= n; ++ w) {
    for (int h = 1; h <= n; ++ h) {
      for (int x1 = 1; x1 + h - 1 <= n; ++ x1) {
        for (int y1 = 1; y1 + w - 1 <= n; ++ y1) {
          int x2 = x1 + h - 1;
          int y2 = y1 + w - 1;
          int blacks = sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
          if (blacks == 0) {
            dp[x1][y1][x2][y2] = 0;
            continue;
          }
          if (w == 1 && h == 1) {
            dp[x1][y1][x2][y2] = 1;
            continue;
          }
          dp[x1][y1][x2][y2] = std::max(w, h);
          if (w >= h) {
            for (int i = y1; i <= y2; ++ i) {
              update_min(dp[x1][y1][x2][y2], dp[x1][y1][x2][i] + dp[x1][i + 1][x2][y2]);
            }
          } else {
            for (int i = x1; i <= x2; ++ i) {
              update_min(dp[x1][y1][x2][y2], dp[x1][y1][i][y2] + dp[i + 1][y1][x2][y2]);
            }
          }
        }
      }
    }
  }
  std::cout << dp[1][1][n][n] << std::endl;
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
  run();
  return 0;
}
