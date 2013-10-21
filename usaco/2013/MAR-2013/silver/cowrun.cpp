#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1000 + 10;
const long long INF = 1LL << 60;

long long dp[N][N][2];
int a[N], n;

#define update_min(a, b) if ((a) > (b)) (a) = (b)

int main() {
	freopen("cowrun.in", "r", stdin);
	freopen("cowrun.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", a + i);
	}
	a[++ n] = 0;
	std::sort(a + 1, a + n + 1);

	int middle = 0;
	for (int i = 1; i <= n; ++ i) {
		if (a[i] == 0) {
			middle = i;
			break;
		}
	}
	memset(dp, 60, sizeof(dp));
	dp[middle][middle][0] = dp[middle][middle][1] = 0;

	for (int length = 1; length <= n; ++ length) {
		for (int i = 1; i + length - 1 <= n; ++ i) {
			int j = i + length - 1;
			int remain = n - length;
			if (i > 1) {
				update_min(dp[i - 1][j][0], dp[i][j][0] + abs(a[i] - a[i - 1]) * remain);
				update_min(dp[i - 1][j][0], dp[i][j][1] + abs(a[j] - a[i - 1]) * remain);
			}
			if (j < n) {
				update_min(dp[i][j + 1][1], dp[i][j][0] + abs(a[i] - a[j + 1]) * remain);
				update_min(dp[i][j + 1][1], dp[i][j][1] + abs(a[j] - a[j + 1]) * remain);
			}
		}
	}
	printf("%lld\n", std::min(dp[1][n][0], dp[1][n][1]));
	return 0;
}
