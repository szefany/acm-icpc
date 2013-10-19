#include <cstdio>
#include <iostream>

const int M = 1000000 + 10;

int last[M], n, m;

int main() {
	freopen("proximity.in", "r", stdin);
	freopen("proximity.out", "w", stdout);
	scanf("%d%d", &n, &m);
	int answer = -1;
	for (int i = 1; i <= n; ++ i) {
		int x;
		scanf("%d", &x);
		if (last[x] != 0 && i - last[x] <= m) {
			answer = std::max(answer, x);
		}
		last[x] = i;
	}
	printf("%d\n", answer);
	return 0;
}
