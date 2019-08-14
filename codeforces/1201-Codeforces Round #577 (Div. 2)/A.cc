#include <bits/stdc++.h>

const int N = 1000 + 10;

char answers[N][N];
int scores[N];
int n, m;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++ i) {
    scanf("%s", answers[i] + 1);
  }
  for (int i = 1; i <= m; ++ i) {
    scanf("%d", scores + i);
  }

  int result = 0;
  for (int j = 1; j <= m; ++ j) {
    int counter[5] = {0};
    for (int i = 1; i <= n; ++ i) {
      counter[answers[i][j] - 'A'] ++;
    }
    int max_value = 0;
    for (int i = 0; i < 5; ++ i) {
      max_value = std::max(max_value, counter[i]);
    }
    result += scores[j] * max_value;
  }
  printf("%d\n", result);
  return 0;
}
