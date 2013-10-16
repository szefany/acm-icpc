#include <cstdio>
#include <vector>

const int N = 200000 + 10;
const int D = 19;

int go[N][D], enter[N], leave[N], target[N], answer[N], n;
long long depth[N], m;

int main() {
	freopen("runaway.in", "r", stdin);
	freopen("runaway.out", "w", stdout);
	scanf("%d%lld", &n, &m);
	for (int u = 2; u <= n; ++ u) {
		int p;
		long long d;
		scanf("%d%lld", &p, &d);
		depth[u] = depth[p] + d;
		go[u][0] = p;
		for (int i = 0; go[u][i]; ++ i) {
			go[u][i + 1] = go[go[u][i]][i];
		}
	}
	for (int u = 1; u <= n; ++ u) {
		int v = u;
		for (int i = D - 1; i >= 0; -- i) {
			if (go[v][i] && depth[u] - depth[go[v][i]] <= m) {
				v = go[v][i];
			}
		}
		target[u] = v;
		enter[u] ++;
		leave[v] ++;
	}
	for (int i = n; i >= 1; -- i) {
		answer[i] += enter[i];
		if (target[i] < i) {
			answer[go[i][0]] += answer[i] - leave[i];
		}
	}
	for (int i = 1; i <= n; ++ i) {
		printf("%d\n", answer[i]);
	}
	return 0;
}
