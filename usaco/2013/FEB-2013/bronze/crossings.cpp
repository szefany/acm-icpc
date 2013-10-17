#include <cstdio>
#include <algorithm>

const int N = 100000 + 10;
const int INF = 1 << 30;

struct Data {
	int a, b;
	void input() {
		scanf("%d%d", &a, &b);
	}
	bool operator < (const Data &o) const {
		return a < o.a;
	}
} data[N];

int max_value[N], min_value[N], n;

int main() {
	freopen("crossings.in", "r", stdin);
	freopen("crossings.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		data[i].input();
	}
	std::sort(data + 1, data + n + 1);

	max_value[0] = -INF;
	for (int i = 1; i <= n; ++ i) {
		max_value[i] = std::max(data[i].b, max_value[i - 1]);
	}
	min_value[n + 1] = INF;
	for (int i = n; i >= 1; -- i) {
		min_value[i] = std::min(data[i].b, min_value[i + 1]);
	}
	int answer = 0;
	for (int i = 1; i <= n; ++ i) {
		answer += max_value[i - 1] < data[i].b && min_value[i + 1] > data[i].b;
	}
	printf("%d\n", answer);
	return 0;
}
