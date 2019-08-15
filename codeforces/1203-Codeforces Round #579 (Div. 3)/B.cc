#include <bits/stdc++.h>

const int N = 1000;

std::map<int, int> counter;
std::pair<int, int> a[N];
int n;

int main() {
  int tests;
  scanf("%d", &tests);
  while (tests --) {
    counter.clear();
    scanf("%d", &n);
    for (int i = 1; i <= 4 * n; ++ i) {
      int x;
      scanf("%d", &x);
      counter[x] ++;
    }

    n = 0;
    for (auto p : counter) {
      a[++ n] = p;
    }
    int area = a[1].first * a[n].first;

    bool valid = true;
    for (int i = 1; i * 2 <= n; ++ i) {
      int j = n - i + 1;
      if (a[i].second % 2 == 1 || a[j].second % 2 == 1 || a[i].second != a[j].second || a[i].first * a[j].first != area) {
        valid = false;
        break;
      }
    }
    if (n % 2 == 1) {
      int x = n / 2 + 1;
      if (a[x].first * a[x].first != area || a[x].second % 4 != 0) {
        valid = false;
      }
    }
    puts(valid ? "YES" : "NO");
  }
  return 0;
}
