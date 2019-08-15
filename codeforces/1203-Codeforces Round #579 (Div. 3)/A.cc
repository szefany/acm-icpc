#include <bits/stdc++.h>

const int N = 500;

int a[N], n;

int main() {
  int tests;
  scanf("%d", &tests);
  while (tests --) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
      scanf("%d", a + i);
      a[i + n] = a[i];
    }

    bool valid = false;
    for (int i = 1; i <= n; ++ i) {
      bool f1 = true;
      bool f2 = true;
      for (int j = i; j <= i + n - 1; ++ j) {
        f1 &= a[j] == j - i + 1;
        f2 &= a[j] == n - (j - i + 1) + 1;
      }
      if (f1 || f2) {
        valid = true;
        break;
      }
    }
    puts(valid ? "YES" : "NO");
  }
  return 0;
}
