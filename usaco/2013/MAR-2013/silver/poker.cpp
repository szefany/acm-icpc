#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 100000 + 10;
const int S = N << 2;
const int INF = 1 << 30;

int a[N], n;
long long answer;

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

Pair value[S];
int delta[S];

void build(int u, int l, int r) {
	if (l == r) {
		value[u] = make_pair(a[l], l);
		return;
	}
	int m = l + r >> 1;
	build(L(u), l, m);
	build(R(u), m + 1, r);
	value[u] = std::min(value[L(u)], value[R(u)]);
}

void push_down(int u) {
	if (delta[u]) {
		delta[L(u)] += delta[u];
		delta[R(u)] += delta[u];
		value[L(u)].first -= delta[u];
		value[R(u)].first -= delta[u];
		delta[u] = 0;
	}
}

void subtract(int u, int l, int r, int a, int b, int v) {
	if (b < l || a > r) {
		return;
	}
	if (a <= l && b >= r) {
		delta[u] += v;
		value[u].first -= v;
		return;
	}
	push_down(u);
	int m = l + r >> 1;
	subtract(L(u), l, m, a, b, v);
	subtract(R(u), m + 1, r, a, b, v);
	value[u] = std::min(value[L(u)], value[R(u)]);
}

Pair query(int u, int l, int r, int a, int b) {
	if (b < l || a > r) {
		return make_pair(INF, INF);
	}
	if (a <= l && b >= r) {
		return value[u];
	}
	push_down(u);
	int m = l + r >> 1;
	return std::min(query(L(u), l, m, a, b), query(R(u), m + 1, r, a, b));
}

void solve(int l, int r) {
	if (l <= r) {
		Pair now = query(1, 1, n, l, r);
		int v = now.first;
		int x = now.second;
		answer += v;
		subtract(1, 1, n, l, r, v);
		solve(l, x - 1);
		solve(x + 1, r);
	}
}

int main() {
	freopen("poker.in", "r", stdin);
	freopen("poker.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", a + i);
	}
	build(1, 1, n);
	solve(1, n);
	printf("%lld\n", answer);
	return 0;
}
