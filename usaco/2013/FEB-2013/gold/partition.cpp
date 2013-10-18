#include <cstdio>
#include <cstring>

const int N = 16;

int a[N][N], belongs[N], sum[N];
int n, m;

bool judge(int mask, int largest) {
	int group = 0;
	for (int i = 0; i < n; ++ i) {
		belongs[i] = group;
		if (1 << i & mask) {
			group ++;
		}
	}
	int limit = m - __builtin_popcount(mask);
	memset(sum, 0, sizeof(sum));
	for (int i = 0; i < n; ++ i) {
		bool flag = false;
		for (int j = 0; j < n; ++ j) {
			sum[belongs[j]] += a[j][i];
			if (sum[belongs[j]] > largest) {
				flag = true;
				break;
			}
		}
		if (flag) {
			limit --;
			if (limit < 0) {
				return false;
			}
			memset(sum, 0, sizeof(sum));
			for (int j = 0; j < n; ++ j) {
				sum[belongs[j]] += a[j][i];
				if (sum[belongs[j]] > largest) {
					return false;
				}
			}
		}
	}
	return true;
}

bool check(int largest) {
	for (int mask = 0; mask < (1 << n - 1); ++ mask) {
		if (__builtin_popcount(mask) <= m && judge(mask, largest)) {
			return true;
		}
	}
	return false;
}

int main() {
	freopen("partition.in", "r", stdin);
	freopen("partition.out", "w", stdout);
	scanf("%d%d", &n, &m);
	int total = 0;
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < n; ++ j) {
			scanf("%d", &a[i][j]);
			total += a[i][j];
		}
	}
	int lower = 0, upper = total;
	while (lower < upper) {
		int middle = lower + upper >> 1;
		if (check(middle)) {
			upper = middle;
		} else {
			lower = middle + 1;
		}
	}
	printf("%d\n", lower);
	return 0;
}
