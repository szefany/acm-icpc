#include <bits/stdc++.h>

const int N = 110;
const int R = 30000 + 10;

std::vector<std::pair<int, int>> positive, negative;
int dp[N][R];
int n, r;

bool cmp(const std::pair<int, int>& a, const std::pair<int, int>& b) {
  return a.first - a.second > b.first - b.second;
}

void update_max(int& a, int b) {
  if (b > a) a = b;
}

int main() {
  scanf("%d%d", &n, &r);
  for (int i = 1; i <= n; ++ i) {
    int a, b;
    scanf("%d%d", &a, &b);
    if (b >= 0) {
      positive.push_back(std::make_pair(a, b));
    } else {
      negative.push_back(std::make_pair(a, -b));
    }
  }
  std::sort(positive.begin(), positive.end());

  int counter = 0;
  for (auto p : positive) {
    if (r < p.first) {
      break;
    }
    r += p.second;
    counter ++;
  }

  for (auto& p : negative) {
    p.first = std::max(p.first, p.second);
  }
  std::sort(negative.begin(), negative.end(), cmp);

  for (int i = 0; i < R; ++ i) {
    dp[0][i] = -1 << 20;
  }
  dp[0][r] = counter;
  for (int i = 0; i < negative.size(); ++ i) {
    int a = negative[i].first;
    int b = negative[i].second;

    for (int c = 0; c <= r; ++ c) {
      update_max(dp[i + 1][c], dp[i][c]);
      if (c >= a && c >= b) {
        update_max(dp[i + 1][c - b], dp[i][c] + 1);
      }
    }
  }
  // for (int i = 0; i < negative.size(); ++ i) {
  //   for (int c = 0; c <= r; ++ c) {
  //     std::cerr << i << " " << c << " " << dp[i][c] << std::endl;
  //   }
  // }
  int answer = 0;
  for (int c = 0; c <= r; ++ c) {
    update_max(answer, dp[negative.size()][c]);
  }
  printf("%d\n", answer);
  return 0;
}
