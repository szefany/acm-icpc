#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

const int N = 200000 + 10;

std::vector<long long> all;
std::vector<int> path;
long long height[N];
int n, d;

const int S = N << 2;

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

Pair values[S];
void Insert(int u, int l, int r, int x, Pair v) {
  if (l == r) {
    values[u] = v;
    return;
  }
  int m = l + r >> 1;
  if (x <= m) {
    Insert(L(u), l, m, x, v);
  } else {
    Insert(R(u), m + 1, r, x, v);
  }
  values[u] = std::max(values[L(u)], values[R(u)]);
}

Pair Query(int u, int l, int r, int a, int b) {
  if (b < l || a > r || a > b) {
    return make_pair(-1, 0);
  }
  if (a <= l && b >= r) {
    return values[u];
  }
  int m = l + r >> 1;
  return std::max(Query(L(u), l, m, a, b), Query(R(u), m + 1, r, a, b));
}

int from[N];

int main() {
  scanf("%d%d", &n, &d);
  for (int i = 1; i <= n; ++ i) {
    scanf("%I64d", &height[i]);
    all.push_back(height[i]);
  }
  std::sort(all.begin(), all.end());
  all.resize(unique(all.begin(), all.end()) - all.begin());

  int answer = 0;
  int id = 0;
  int size = all.size();
  for (int i = 1; i <= n; ++ i) {
    long long x = height[i];
    Pair now = make_pair(1, 0);
    Pair temp = Query(1, 0, size - 1, 0, std::upper_bound(all.begin(), all.end(), x - d) - all.begin() - 1);
    temp.first ++;
    now = std::max(now, temp);
    temp = Query(1, 0, size - 1, std::lower_bound(all.begin(), all.end(), x + d) - all.begin(), size - 1);
    temp.first ++;
    now = std::max(now, temp);

    from[i] = now.second;
    if (from[i] > i) {
      int a = 1;
    }
    Insert(1, 0, size - 1, std::lower_bound(all.begin(), all.end(), x) - all.begin(), make_pair(now.first, i));

    if (now.first > answer) {
      answer = now.first;
      id = i;
    }
  }
  printf("%d\n", answer);

  while (id) {
    path.push_back(id);
    id = from[id];
  }
  for (int i = path.size() - 1; i >= 0; -- i) {
    printf("%d%c", path[i], i == 0 ? '\n' : ' ');
  }
  return 0;
}
