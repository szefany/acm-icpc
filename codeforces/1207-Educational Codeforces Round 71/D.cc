#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 300000 + 10;
const int MOD = 998244353;

Pair a[N], b[N];
long long factorial[N];
int n;

void run(int case_id = 0) {
  std::cin >> n;
  factorial[0] = 1;
  for (int i = 1; i <= n; ++ i) {
    factorial[i] = factorial[i - 1] * i % MOD;
  }

  for (int i = 1; i <= n; ++ i) {
    int x, y;
    std::cin >> x >> y;
    a[i] = make_pair(x, y);
    b[i] = make_pair(y, x);
  }

  long long answer = factorial[n];
  long long temp = 1;
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; ) {
    int j = i;
    while (j <= n && a[i].first == a[j].first) j ++;
    temp = temp * factorial[j - i] % MOD;
    i = j;
  }
  // std::cerr << temp << std::endl;
  answer = (answer - temp) % MOD;

  temp = 1;
  std::sort(b + 1, b + n + 1);
  for (int i = 1; i <= n; ) {
    int j = i;
    while (j <= n && b[i].first == b[j].first) j ++;
    temp = temp * factorial[j - i] % MOD;
    i = j;
  }
  // std::cerr << temp << std::endl;
  answer = (answer - temp) % MOD;

  temp = 1;
  int max_value = 0;
  for (int i = 1; i <= n; ) {
    int j = i;
    while (j <= n && a[i].first == a[j].first) j ++;
    for (int x = i; x < j; ) {
      int y = x;
      while (y < j && a[x].second == a[y].second) {
        if (a[y].second < max_value) {
          temp = 0;
        }
        y ++;
      }
      temp = temp * factorial[y - x] % MOD;
      x = y;
    }
    for (int k = i; k < j; ++ k) {
      update_max(max_value, a[k].second);
    }
    i = j;
  }
  // std::cerr << temp << std::endl;
  answer = (answer + temp) % MOD;
  answer = (answer + MOD) % MOD;
  std::cout << answer << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
