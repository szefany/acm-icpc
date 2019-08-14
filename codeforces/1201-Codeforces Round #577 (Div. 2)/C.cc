#include <bits/stdc++.h>

const int N = 200000 + 10;

int a[N], n, k;

bool is_valid(int x) {
  int pos = std::lower_bound(a + 1, a + n + 1, x) - a;
  pos --;
  int remain = k;
  while (pos > 0) {
    if (x - a[pos] <= remain) {
      remain -= x - a[pos];
      pos --;
    } else {
      break;
    }
  }
  int m = (n + 1) / 2;
  return pos < m;
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++ i) {
    scanf("%d", a + i);
  }
  std::sort(a + 1, a + n + 1);

  int lower = 1, upper = 2000000000 + 10;
  int found = -1;
  while (lower < upper) {
    int medium = ((long long)lower + upper) / 2;
    if (is_valid(medium)) {
      found = medium;
      lower = medium + 1;
    } else {
      upper = medium;
    }
  }
  printf("%d\n", found);
  return 0;
}
