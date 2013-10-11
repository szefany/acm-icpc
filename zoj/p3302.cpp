#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 100 + 10;
const int M = 10000 + 10;

int pow[M], has[M];

void initialise() {
	has[0] = 0;
	for (int i = 1; i < M; ++ i) {
		if (i & 1) {
			has[i] = 0;
		} else {
			has[i] = has[i >> 1] + 1;
		}
	}
	pow[0] = 0;
	for (int i = 1; i < M; ++ i) {
		pow[i] = pow[i - 1] + has[i];
	}
}

int A(int a, int b) {
	return pow[a] - pow[a - b];
}

int a[N], n;

int main() {
	initialise();
	while (scanf("%d", &n) != EOF) {
		int sum = 0;
		int mul = pow[n];
		for (int i = 1; i <= n; ++ i) {
			scanf("%d", a + i);
			sum += a[i];
			mul += has[a[i]];
		}
		if (sum == n) {
			puts("-1");
			puts("0");
		} else {
			mul += has[sum - n];
			printf("%d\n", n + 1);
			printf("%d\n", mul - A(sum, n + 1));
		}
		
		int min_value = a[1];
		for (int i = 1; i <= n; ++ i) {
			min_value = std::min(min_value, a[i]);
		}
		int m = 0;
		for (int i = 1; i <= n; ++ i) {
			if (a[i] == min_value) {
				m ++;
			}
		}
		mul = pow[sum - min_value] + has[min_value] + has[m];
		int ans = A(sum, sum - min_value + 1);
		printf("%d\n", sum - min_value + 1);
		printf("%d\n", mul - ans);
	}
}
