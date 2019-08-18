#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int N = 100000 + 10;

int a[N], b[N], c[N], reflect[N], belong[N], answer[N], n;
Pair ids[N];

int random(int l, int r) {
  return std::uniform_int_distribution<int>(l, r)(rng);
}

void run(int case_id = 0) {
  int m = 0;
  std::cin >> m;
  for (int i = 1; i <= m; ++ i) {
    std::cin >> b[i];
    ids[i] = make_pair(b[i], i);
  }
  std::sort(ids + 1, ids + m + 1);

  int length = 0;
  for (int i = 1; i <= m; ) {
    int j = i;
    while (j <= m && ids[i].first == ids[j].first) j ++;
    a[++ length] = ids[i].first;
    for (int k = i; k < j; ++ k) {
      reflect[k] = length;
    }
    if (j - i > 1) {
      a[++ length] = ids[i].first;
      reflect[j - 1] = length;
    }
    i = j;
  }
  n = length;

  bool found = false;
  int limit = 5000000 / n;
  while (limit --) {
    int gcd[3] = {-1};
    for (int i = 1; i <= n; ++ i) {
      int id = random(1, 2);
      belong[i] = id;
      if (gcd[id] == -1) {
        gcd[id] = a[i];
      } else {
        gcd[id] = std::__gcd(gcd[id], a[i]);
      }
    }
    if (gcd[1] == 1 && gcd[2] == 1) {
      found = true;
      break;
    }
  }
  if (found) {
    std::cout << "YES" << "\n";
    for (int i = 1; i <= m; ++ i) {
      int id = ids[i].second;
      answer[id] = belong[reflect[i]];
    }
    for (int i = 1; i <= m; ++ i) {
      std::cout << answer[i] << " ";
    }
    std::cout << "\n";
  } else {
    std::cout << "NO" << "\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
