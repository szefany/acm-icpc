#include <bits/stdc++.h>

const int N = 10 + 10;
const int M = N << 2;

int a[N], b[N], id[N];
int n, m;

#define L(u) ((u) << 1)
#define R(u) (((u) << 1) | 1)

int empty[M], right[M];

void build(int u, int l, int r) {
  if (l == r) {
    empty[u] = 1;
    right[u] = l;
  } else {
    int m = (l + r) / 2;
    build(L(u), l, m);
    build(R(u), m + 1, r);
    empty[u] = r - l + 1;
    right[u] = r;
  }
}

void update(int u) {
  empty[u] = empty[L(u)] + empty[R(u)];
  if (right[R(u)] != -1) {
    right[u] = right[R(u)];
  } else {
    right[u] = right[L(u)];
  }
}

void insert(int u, int l, int r, int x) {
  if (l == r) {
    empty[u] = 0;
    right[u] = -1;
  } else {
    int m = (l + r) / 2;
    if (x <= m) {
      insert(L(u), l, m, x);
    } else {
      insert(R(u), m + 1, r, x);
    }
    update(u);
  }
}

int query(int u, int l, int r, int a, int b) {
  if (b < l || a > r) {
    return -1;
  }
  if (a <= l && b >= r) {
    return right[u];
  }
  int m = (l + r) / 2;
  int x = query(R(u), m + 1, r, a, b);
  if (x == -1) {
    x = query(L(u), l, m, a, b);
  }
  return x;
}

bool cmp(int x, int y) {
  if (b[x] == b[y]) {
    return a[x] < a[y];
  }
  return b[x] > b[y];
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++ i) {
    scanf("%d%d", a + i, b + i);
    a[i] = m - a[i] + 1;
    id[i] = i;
  }
  std::sort(id + 1, id + n + 1, cmp);

  build(1, 1, n);
  int answer = 0;
  for (int i = 1; i <= n; ++ i) {
    int u = id[i];
    int pos = query(1, 1, n, 1, a[u]);
    if (pos != -1) {
      answer += b[u];
      insert(1, 1, n, pos);
    }
  }
  printf("%d\n", answer);
  return 0;
}
