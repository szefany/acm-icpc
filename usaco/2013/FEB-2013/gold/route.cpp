#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

const int N = 40000 + 10;
const int M = 100000 + 10;

struct Edge {
	int from, to;
	Edge(int u = 0, int v = 0): from(u), to(v) {}
	bool operator < (const Edge &e) const {
		return from < e.from || from == e.from && to < e.to;
	}
} edges[M];

long long dp_left[N], dp_right[N];
int left[N], right[N];
int a, b, m;

#define update_max(a, b) if ((a) < (b)) (a) = (b)

int main() {
	freopen("route.in", "r", stdin);
	freopen("route.out", "w", stdout);
	scanf("%d%d%d", &a, &b, &m);
	for (int i = 1; i <= a; ++ i) {
		scanf("%d", left + i);
		dp_left[i] = left[i];
	}
	for (int i = 1; i <= b; ++ i) {
		scanf("%d", right + i);
		dp_right[i] = right[i];
	}
	for (int i = 1; i <= m; ++ i) {
		int u, v;
		scanf("%d%d", &u, &v);
		edges[i] = Edge(u, v);
	}
	std::sort(edges + 1, edges + m + 1);

	for (int i = m; i >= 1; -- i) {
		int u = edges[i].from;
		int v = edges[i].to;
		long long next_left = dp_right[v] + left[u];
		long long next_right = dp_left[u] + right[v];
		update_max(dp_left[u], next_left);
		update_max(dp_right[v], next_right);
	}
	long long answer = 0;
	for (int i = 1; i <= a; ++ i) {
		update_max(answer, dp_left[i]);
	}
	for (int i = 1; i <= b; ++ i) {
		update_max(answer, dp_right[i]);
	}
	std::cout << answer << std::endl;
	return 0;
}
