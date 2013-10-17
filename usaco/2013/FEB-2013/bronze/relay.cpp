#include <cstdio>
#include <cstring>

const int N = 1000 + 10;

bool visit[N];
int loop[N], next[N];
int n;

bool in_loop(int u) {
	if (loop[u] != -1) {
		return loop[u];
	}
	if (u == 0) {
		return false;
	}
	if (visit[u]) {
		return true;
	}
	visit[u] = true;
	loop[u] = in_loop(next[u]);
	visit[u] = false;
	return loop[u];
}

int main() {
	freopen("relay.in", "r", stdin);
	freopen("relay.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", next + i);
	}
	memset(loop, -1, sizeof(loop));
	int count = 0;
	for (int i = 1; i <= n; ++ i) {
		count += in_loop(i);
	}
	printf("%d\n", n - count);
	return 0;
}
