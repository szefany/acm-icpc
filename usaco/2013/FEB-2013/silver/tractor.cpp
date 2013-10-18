#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 500 + 10;
const int M = N * N * 2;

int ancestor[M], size[M];

int get_ancestor(int u) {
	return u == ancestor[u] ? u : ancestor[u] = get_ancestor(ancestor[u]);
}

void joint(int u, int v) {
	u = get_ancestor(u);
	v = get_ancestor(v);
	if (u != v) {
		if (size[u] > size[v]) {
			std::swap(u, v);
		}
		ancestor[u] = v;
		size[v] += size[u];
	}
}

struct Edge {
	int u, v, w;
	Edge(int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
	bool operator < (const Edge &o) const {
		return w < o.w;
	}
} edges[M];

int matrix[N][N], n, counter;

int get_id(int x, int y) {
	return (x - 1) * n + y;
}

int abs(int x) {
	return x > 0 ? x : -x;
}

int main() {
	freopen("tractor.in", "r", stdin);
	freopen("tractor.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= n; ++ j) {
			scanf("%d", &matrix[i][j]);
			if (i > 1) {
				edges[++ counter] = Edge(get_id(i - 1, j), get_id(i, j), abs(matrix[i][j] - matrix[i - 1][j]));
			}
			if (j > 1) {
				edges[++ counter] = Edge(get_id(i, j - 1), get_id(i, j), abs(matrix[i][j] - matrix[i][j - 1]));
			}
		}
	}

	std::sort(edges + 1, edges + counter + 1);
	for (int i = 1; i <= n * n; ++ i) {
		ancestor[i] = i;
		size[i] = 1;
	}
	int limit = (n * n + 1) / 2;
	int answer = 0;
	for (int i = 1; i <= counter; ++ i) {
		int u = edges[i].u;
		int v = edges[i].v;
		joint(u, v);
		if (size[get_ancestor(u)] >= limit) {
			answer = edges[i].w;
			break;
		}
	}
	printf("%d\n", answer);
	return 0;
}
