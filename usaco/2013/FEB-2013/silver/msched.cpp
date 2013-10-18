#include <cstdio>
#include <cstring>
#include <vector>

const int N = 10000 + 10;

std::vector<int> neighbors[N];
int dp[N], degree[N], cost[N], queue[N];
int n, m;

int ancestor[N], final[N], counter;

int get_ancestor(int u) {
	return u == ancestor[u] ? u : ancestor[u] = get_ancestor(ancestor[u]);
}

void joint(int u, int v) {
	u = get_ancestor(u);
	v = get_ancestor(v);
	if (u != v) {
		ancestor[u] = v;
	}
}

int main() {
	freopen("msched.in", "r", stdin);
	freopen("msched.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", cost + i);
		ancestor[i] = i;
	}
	while (m --) {
		int u, v;
		scanf("%d%d", &u, &v);
		neighbors[u].push_back(v);
		degree[v] ++;
		joint(u, v);
	}
	int tail = 0;
	for (int i = 1; i <= n; ++ i) {
		if (degree[i] == 0) {
			dp[i] = cost[i];
			queue[++ tail] = i;
		}
	}
	for (int head = 1; head <= tail; ++ head) {
		int u = queue[head];
		int du = get_ancestor(u);
		final[du] = std::max(final[du], dp[u]);
		for (int i = 0; i < neighbors[u].size(); ++ i) {
			int v = neighbors[u][i];
			dp[v] = std::max(dp[v], dp[u] + cost[v]);
			degree[v] --;
			if (degree[v] == 0) {
				queue[++ tail] = v;
			}
		}
	}
	int answer = 0;
	for (int i = 1; i <= n; ++ i) {
		if (i == get_ancestor(i)) {
			answer = std::max(answer, final[i]);
		}
	}
	printf("%d\n", answer);
	return 0;
}
