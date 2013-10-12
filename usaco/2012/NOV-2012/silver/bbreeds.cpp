#include <cstdio>
#include <cstring>

const int N = 1000 + 10;
const int MOD = 2012;

char string[N];
int dp[N][N];

int main() {
	freopen("bbreeds.in", "r", stdin);
	freopen("bbreeds.out", "w", stdout);
	scanf("%s", string + 1);
	int n = strlen(string + 1);
	
	dp[0][0] = 1;
	for (int i = 1, depth = 0; i <= n; ++ i) {
		depth += string[i] == '(' ? 1 : -1;
		for (int a = 0; a <= depth; ++ a) {
			int b = depth - a;
			if (string[i] == '(') {
				if (a) {
					(dp[i][a] += dp[i - 1][a - 1]) %= MOD;
				}
				if (b) {
					(dp[i][a] += dp[i - 1][a]) %= MOD;
				}
			} else {
				(dp[i][a] += dp[i - 1][a + 1] + dp[i - 1][a]) %= MOD;
			}
		}
	}
	printf("%d\n", dp[n][0]);
	return 0;
}
