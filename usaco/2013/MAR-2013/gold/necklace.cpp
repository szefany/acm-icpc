#include <cstdio>
#include <cstring>

const int N = 10000 + 10;
const int L = 1000 + 10;
const int INF = 1 << 29;

char a[N], b[L];
int next[L];
int dp[N][L];

#define update_min(a, b) if ((a) > (b)) (a) = (b)

int main() {
	freopen("necklace.in", "r", stdin);
	freopen("necklace.out", "w", stdout);
	scanf("%s%s", a + 1, b + 1);
	int length_a = strlen(a + 1);
	int length_b = strlen(b + 1);

	next[1] = 0;
	for (int i = 2, j = 0; i <= length_b; ++ i) {
		while (j && b[j + 1] != b[i]) {
			j = next[j];
		}
		j += b[i] == b[j + 1];
		next[i] = j;
	}

	memset(dp, 1, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 0; i < length_a; ++ i) {
		for (int j = 0; j < length_b; ++ j) {
			int key = a[i + 1];
			update_min(dp[i + 1][j], dp[i][j] + 1);
			int k = j;
			while (k && b[k + 1] != key) {
				k = next[k];
			}
			k += b[k + 1] == key;
			update_min(dp[i + 1][k], dp[i][j]);
		}
	}
	int answer = INF;
	for (int i = 0; i < length_b; ++ i) {
		update_min(answer, dp[length_a][i]);
	}
	printf("%d\n", answer);
	return 0;
}
