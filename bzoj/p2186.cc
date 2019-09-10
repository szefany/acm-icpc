#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 10000000 + 10;

bool visited[N];
int primes[N], num_primes = 0;
int phi_fact[N], fact[N], inv[N];

int read() {
  char c;
  int flag = 1;
  while (c = getchar(), c < '0' || c > '9') {
    if (c == '-') flag = -1;
  }
  int result = c & 15;
  while (c = getchar(), c >= '0' && c <= '9') {
    result = result * 10 + (c & 15);
  }
  return flag > 0 ? result : -result;
  return result * flag;
}

void run(int case_id = 0) {
  int num_tests = read();
  int mod = read();

  phi_fact[1] = 1 % mod;
  fact[1] = 1 % mod;
  inv[1] = 1 % mod;

  for (int i = 2; i < N; ++ i) {
    fact[i] = (long long)fact[i - 1] * i % mod;
    if (i < mod) inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;
    if (!visited[i]) {
      primes[num_primes ++] = i;
      phi_fact[i] = (long long)phi_fact[i - 1] * (i - 1) % mod * inv[i % mod] % mod;
    } else {
      phi_fact[i] = phi_fact[i - 1];
    }
    for (int j = 0; j < num_primes && i * primes[j] < N; ++ j) {
      visited[i * primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  while (num_tests --) {
    int n = read();
    int m = read();
    printf("%lld\n", (long long)phi_fact[m] * fact[n] % mod);
  }
}

int main() {
  run();
  return 0;
}
