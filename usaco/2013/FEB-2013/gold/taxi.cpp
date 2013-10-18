#include <cstdio>
#include <algorithm>
#include <iostream>

const int N = 100000 + 10;

int a[N], b[N], n, m;

int main() {
	freopen("taxi.in", "r", stdin);
	freopen("taxi.out", "w", stdout);
	scanf("%d%d", &n, &m);
	a[0] = m;
	b[0] = 0;
	long long answer = 0;
	for (int i = 1; i <= n; ++ i) {
		scanf("%d%d", a + i, b + i);
		answer += abs(b[i] - a[i]);
	}

	std::sort(a, a + n + 1);
	std::sort(b, b + n + 1);
	for (int i = 0; i <= n; ++ i) {
		answer += abs(a[i] - b[i]);
	}
	std::cout << answer << std::endl;
	return 0;
}
