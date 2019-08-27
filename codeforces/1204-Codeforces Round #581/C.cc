#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 100 + 10;
const int M = 1000000 + 10;
const int INF = 1 << 29;

bool connected[N][N];
int dist[N][N];
int path[M], dp[M], from[M];
int n, m;

void run(int case_id = 0) {
  std::cin >> n;
  char buffer[N];
  for (int i = 1; i <= n; ++ i) {
    std::cin >> buffer + 1;
    for (int j = 1; j <= n; ++ j) {
      connected[i][j] = buffer[j] == '1';
      dist[i][j] = connected[i][j] ? 1 : INF;
    }
  }

  for (int k = 1; k <= n; ++ k) {
    for (int i = 1; i <= n; ++ i) {
      if (i == k) continue;
      for (int j = 1; j <= n; ++ j) {
        if (i == j || j == k) continue;
        update_min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  std::cin >> m;
  for (int i = 1; i <= m; ++ i) {
    std::cin >> path[i];
  }

  for (int i = 1; i <= m; ++ i) {
    dp[i] = INF;
  }
  dp[1] = 1;
  for (int i = 1; i <= m; ++ i) {
    int u = path[i];
    for (int v = 1; v <= n; ++ v) {
      int d = dist[u][v];
      if (i + d <= m && path[i + d] == v && dp[i + d] > dp[i] + 1) {
        dp[i + d] = dp[i] + 1;
        from[i + d] = i;
      }
    }
  }
  int x = m;
  std::cout << dp[x] << "\n";
  std::vector<int> routes;
  while (1) {
    routes.push_back(path[x]);
    if (x == 1) break;
    x = from[x];
  }
  for (int i = routes.size() - 1; i >= 0; -- i) {
    std::cout << routes[i] << " ";
  }
  std::cout << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
