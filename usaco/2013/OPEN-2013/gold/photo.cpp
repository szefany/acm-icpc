#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 200000 + 10;
const int INF = 1 << 30;

int left[N], right[N], label[N], a[N], b[N], dp[N];
int n, m;

void update_min(int &a, int b) {
	a = a < b ? a : b;
}

void update_max(int &a, int b) {
	a = a > b ? a : b;
}

const int S = N << 2;

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

int value[S];

void build(int u, int l, int r) {
	if (l == r) {
		value[u] = l == 0 ? 0 : -INF;
	} else {
		int m = l + r >> 1;
		build(L(u), l, m);
		build(R(u), m + 1, r);
		value[u] = std::max(value[L(u)], value[R(u)]);
	}
}

void insert(int u, int l, int r, int x, int v) {
	if (l == r) {
		value[u] = v;
	} else {
		int m = l + r >> 1;
		if (x <= m) {
			insert(L(u), l, m, x, v);
		} else {
			insert(R(u), m + 1, r, x, v);
		}
		value[u] = std::max(value[L(u)], value[R(u)]);
	}
}

int query(int u, int l, int r, int a, int b) {
	if (a > r || b < l) {
		return -INF;
	}
	if (a <= l && b >= r) {
		return value[u];
	}
	int m = l + r >> 1;
	return std::max(query(L(u), l, m, a, b), query(R(u), m + 1, r, a, b));
}

int main() {
	freopen("photo.in", "r", stdin);
	freopen("photo.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++ i) {
		scanf("%d%d", a + i, b + i);
	}
	int limit = n + 1;

	for (int i = 0; i <= limit; ++ i) {
		label[i] = limit;
	}
	for (int i = 1; i <= m; ++ i) {
		update_min(label[b[i]], a[i]);
	}
	for (int i = limit, now = limit; i > 0; -- i) {
		update_min(now, label[i]);
		right[i] = now - 1;
	}

	for (int i = 0; i <= limit; ++ i) {
		label[i] = 0;
	}
	for (int i = 1; i <= m; ++ i) {
		update_max(label[b[i]], a[i]);
	}
	for (int i = 1, now = 0; i <= limit; ++ i) {
		left[i] = now;
		update_max(now, label[i]);
	}

	build(1, 0, limit);
	for (int i = 1; i <= limit; ++ i) {
		if (left[i] <= right[i]) {
			dp[i] = query(1, 0, limit, left[i], right[i]) + 1;
			insert(1, 0, limit, i, dp[i]);
		}
	}
	if (dp[limit] <= 0) {
		puts("-1");
	} else {
		printf("%d\n", dp[limit] - 1);
	}
	return 0;
}
