#include <bits/stdc++.h>

const int N = 2000 + 10;

char grids[N][N];
int left[N][N], up[N][N], down[N][N], right[N][N], sum_left[N][N], sum_up[N][N], sum_down[N][N], sum_right[N][N];
int sum_vertical[N][N], sum_horizonal[N][N];
int n, k;

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++ i) {
    scanf("%s", grids[i] + 1);
  }

  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= n; ++ j) {
      if (grids[i][j] == 'W') {
        left[i][j] = j == 1 || left[i][j - 1];
        up[i][j] = i == 1 || up[i - 1][j];
      } else {
        left[i][j] = false;
        up[i][j] = false;
      }
    }
  }
  for (int i = n; i >= 1; -- i) {
    for (int j = n; j >= 1; -- j) {
      if (grids[i][j] == 'W') {
        right[i][j] = j == n || right[i][j + 1];
        down[i][j] = i == n || down[i + 1][j];
      } else {
        right[i][j] = down[i][j] = false;
      }
    }
  }
  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= n; ++ j) {
      sum_left[i][j] = sum_left[i - 1][j] + left[i][j];
      sum_up[i][j] = sum_up[i][j - 1] + up[i][j];
      sum_right[i][j] = sum_right[i - 1][j] + right[i][j];
      sum_down[i][j] = sum_down[i][j - 1] + down[i][j];
    }
  }

  for (int i = 0; i <= n + 1; ++ i) {
    for (int j = 0; j <= n + 1; ++ j) {
      bool hori = (j == 0 || left[i][j]) && (j + k + 1 > n || right[i][j + k + 1]);
      sum_horizonal[i][j] = sum_horizonal[i - 1][j] + hori;

      bool vert = (i == 0 || up[i][j]) && (i + k + 1 > n || down[i + k + 1][j]);
      sum_vertical[i][j] = sum_vertical[i][j - 1] + vert;
    }
  }

  int answer = 0;
  for (int i = 1; i + k - 1 <= n; ++ i) {
    for (int j = 1; j + k - 1 <= n; ++ j) {
      int x = i + k - 1;
      int y = j + k - 1;
      int temp = 0;
      temp += sum_left[i - 1][n];
      temp += sum_left[n][n] - sum_left[x][n];
      temp += sum_up[n][j - 1];
      temp += sum_up[n][n] - sum_up[n][y];
      temp += sum_horizonal[x][j - 1] - sum_horizonal[i - 1][j - 1];
      temp += sum_vertical[i - 1][y] - sum_vertical[i - 1][j - 1];
      answer = std::max(answer, temp);
    }
  }
  printf("%d\n", answer);
  return 0;
}
