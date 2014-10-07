#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

const int N = 100000 + 10;
const int S = N << 2;
const int INF = 1 << 29;

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

int elements[N], n;

int gcd[S];

void Build(int u, int l, int r) {
  if (l == r) {
    gcd[u] = elements[l];
  } else {
    int m = l + r >> 1;
    Build(L(u), l, m);
    Build(R(u), m + 1, r);
    gcd[u] = std::__gcd(gcd[L(u)], gcd[R(u)]);
  }
}

int QueryGcd(int u, int l, int r, int a, int b) {
  if (a <= l && b >= r) {
    return gcd[u];
  }
  int m = l + r >> 1;
  if (b <= m) {
    return QueryGcd(L(u), l, m, a, b);
  }
  if (a > m) {
    return QueryGcd(R(u), m + 1, r, a, b);
  }
  return std::__gcd(QueryGcd(L(u), l, m, a, b), QueryGcd(R(u), m + 1, r, a, b));
}

int main() {
  scanf("%d", &n);
  std::vector<Pair> all;
  for (int i = 1; i <= n; ++ i) {
    scanf("%d", elements + i);
    all.push_back(make_pair(elements[i], i));
  }
  std::sort(all.begin(), all.end());
  Build(1, 1, n);

  int q;
  scanf("%d", &q);
  while (q --) {
    int l, r;
    scanf("%d%d", &l, &r);
    int gcd = QueryGcd(1, 1, n, l, r);
    int chosen = std::upper_bound(all.begin(), all.end(), make_pair(gcd, r))
                 - std::lower_bound(all.begin(), all.end(), make_pair(gcd, l));
    printf("%d\n", r - l + 1 - chosen);
  }
  return 0;
}
