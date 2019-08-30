#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 60;

std::vector<Pair> answer;
int a[N][N], b[N][N], n, m;

void run(int case_id = 0) {
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= m; ++ j) {
      std::cin >> a[i][j];
    }
  }
  for (int i = 1; i < n; ++ i) {
    for (int j = 1; j < m; ++ j) {
      if (a[i][j] + a[i + 1][j] + a[i][j + 1] + a[i + 1][j + 1] == 4) {
        answer.push_back(make_pair(i, j));
        b[i][j] = 1;
        b[i + 1][j] = 1;
        b[i][j + 1] = 1;
        b[i + 1][j + 1] = 1;
      }
    }
  }
  bool valid = true;
  for (int i = 1; i <= n && valid; ++ i) {
    for (int j = 1; j <= m && valid; ++ j) {
      if (b[i][j] != a[i][j]) {
        valid = false;
        break;
      }
    }
  }
  if (!valid) {
    std::cout << "-1" << std::endl;
  } else {
    std::cout << answer.size() << std::endl;
    for (auto p : answer) {
      std::cout << p.first << " " << p.second << "\n";
    }
  }
}


int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
