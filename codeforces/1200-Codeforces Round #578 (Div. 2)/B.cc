#include <bits/stdc++.h>

const int N = 100 + 10;

int height[N];
int n, m, k;

int main() {
  int tests;
  scanf("%d", &tests);
  while (tests --) {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++ i) {
      scanf("%d", height + i);
    }

    bool valid = true;
    int current = m;
    for (int i = 1; i < n; ++ i) {
      if (height[i] < height[i + 1] - k) {
        current -= height[i + 1] - k - height[i];
        if (current < 0) {
          valid = false;
          break;
        }
      } else {
        int value = std::min(height[i], height[i] - (height[i + 1] - k));
        current += value;
      }
    }
    puts(valid ? "YES" : "NO");
  }
  return 0;
}
