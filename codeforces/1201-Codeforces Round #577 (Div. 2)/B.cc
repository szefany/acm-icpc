#include <bits/stdc++.h>

const int N = 100000 + 10;

int a[N], n;

int main() {
  scanf("%d", &n);
  long long sum = 0;
  for (int i = 1; i <= n; ++ i) {
    scanf("%d", a + i);
    sum += a[i];
  }
  std::sort(a + 1, a + n + 1);

  bool valid = sum % 2 == 0 && a[n] * 2 <= sum;
  puts(valid ? "YES" : "NO");
  return 0;
}
