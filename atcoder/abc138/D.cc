#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 200000 + 10;
const int M = N << 2;

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

std::vector<int> neighbors[N];
int enter[N], leave[N], nodes[N], size;
int n, q;

int values[M], cover[M];

void push_down(int u) {
  cover[L(u)] += cover[u];
  cover[R(u)] += cover[u];
  values[L(u)] += cover[u];
  values[R(u)] += cover[u];
  cover[u] = 0;
}

void insert(int u, int l, int r, int a, int b, int x) {
  if (b < l || a > r) return;
  if (a <= l && b >= r) {
    cover[u] += x;
    values[u] += x;
  } else {
    push_down(u);
    int m = (l + r) >> 1;
    insert(L(u), l, m, a, b, x);
    insert(R(u), m + 1, r, a, b, x);
  }
}

int query(int u, int l, int r, int x) {
  if (l == r) {
    return values[u];
  }
  push_down(u);
  int m = (l + r) >> 1;
  if (x <= m) {
    return query(L(u), l, m, x);
  }
  return query(R(u), m + 1, r, x);
}


void dfs(int u, int f) {
  size ++;
  enter[u] = size;
  nodes[size] = u;
  for (auto v : neighbors[u]) {
    if (v == f) continue;
    dfs(v, u);
  }
  leave[u] = size;
}

void run(int case_id = 0) {
  std::cin >> n >> q;
  for (int i = 1; i < n; ++ i) {
    int u, v;
    std::cin >> u >> v;
    neighbors[u].push_back(v);
    neighbors[v].push_back(u);
  }
  size = 0;
  dfs(1, -1);

  while (q --) {
    int p, x;
    std::cin >> p >> x;
    insert(1, 1, n, enter[p], leave[p], x);
  }

  for (int i = 1; i <= n; ++ i) {
    std::cout << query(1, 1, n, enter[i]);
    std::cout << (i == n ? "\n" : " ");
  }
}

void multi_cases_main() {
  int num_tests;
  std::cin >> num_tests;
  for (int t = 1; t <= num_tests; ++ t) {
    run(t);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
