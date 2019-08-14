#include <bits/stdc++.h>

const int N = 1000 + 10;
const int M = 2520;

std::vector<int> neighbors[N];
int weight[N];
int dp[N][M];
int n, q;

std::stack<std::pair<int, int>> stack, stack_copy;
std::set<int> nodes;

void solve(int u, int c) {
  int result = 0;
  int d = 0;
  while (1) {
    dp[u][c] = -2;
    stack.push(std::make_pair(u, c));
    int next_c = ((c + weight[u]) % M + M) % M;
    int e = next_c % neighbors[u].size();;
    int v = neighbors[u][e];
    if (dp[v][next_c] >= 0) {
      result = dp[v][next_c];
      break;
    }
    if (dp[v][next_c] == -2) {
      stack_copy = stack;
      nodes.clear();
      while (!stack_copy.empty()) {
        int u = stack_copy.top().first;
        int c = stack_copy.top().second;
        stack_copy.pop();
        nodes.insert(u);
        if (u == v && c == next_c) break;
      }
      result = nodes.size();
      break;
    }
    stack.push(std::make_pair(v, next_c));
    u = v;
    c = next_c;
  }

  while (!stack.empty()) {
    int u = stack.top().first;
    int c = stack.top().second;
    stack.pop();
    dp[u][c] = result;
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++ i) {
    scanf("%d", weight + i);
  }
  for (int i = 1; i <= n; ++ i) {
    int num;
    scanf("%d", &num);
    while (num --) {
      int x;
      scanf("%d", &x);
      neighbors[i].push_back(x);
    }
  }

  memset(dp, -1, sizeof(dp));
  for (int i = 1; i <= n; ++ i) {
    for (int j = 0; j < M; ++ j) {
      if (dp[i][j] == -1) {
        solve(i, j);
      }
    }
  }

  scanf("%d", &q);
  while (q --) {
    int u, c;
    scanf("%d%d", &u, &c);
    c = (c % M + M) % M;
    printf("%d\n", dp[u][c]);
  }
  return 0;
}
