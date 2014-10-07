#include <cstdio>

const int N = 100000 + 10;
const int MOD = 1000000007;

int dp[N], sum[N];

int main() {
  int test, k;
  scanf("%d%d", &test, &k);
  dp[0] = 1;
  sum[0] = 1;
  for (int i = 1; i < N; ++ i) {
    dp[i] = dp[i - 1];
    if (i >= k) {
      (dp[i] += dp[i - k]) %= MOD;
    }
    sum[i] = sum[i - 1];
    (sum[i] += dp[i]) %= MOD;
  }
  while (test --) {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", ((sum[b] - sum[a - 1]) % MOD + MOD) % MOD); 
  }
  return 0;
}
