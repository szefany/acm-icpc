#include <bits/stdc++.h>

typedef std::pair<int, unsigned long long> Hash;

const int BASE = 131;
const int MOD = 1000000007;
const int N = 1000000 + 10;

Hash power[N];

Hash hash_1[N], hash_2[N];
char string[N], buffer[N];
int n;

bool str_equal(int l1, int r1, int l2, int r2) {
  auto a1 = ((hash_1[r1].first - hash_1[l1 - 1].first) % MOD + MOD) % MOD;
  auto a2 = hash_1[r1].second - hash_1[l1 - 1].second;
  auto b1 = ((hash_2[r2].first - hash_2[l2 - 1].first) % MOD + MOD) % MOD;
  auto b2 = hash_2[r2].second - hash_2[l2 - 1].second;

  if (r1 > r2) {
    b1 = (long long)b1 * power[r1 - r2].first % MOD;
    b2 = b2 * power[r1 - r2].second;
  } else {
    a1 = (long long)a1 * power[r2 - r1].first % MOD;
    a2 = a2 * power[r2 - r1].second;
  }
  return a1 == b1 && a2 == b2;
}

int main() {
  power[0].first = power[0].second = 1;
  for (int i = 1; i < N; ++ i) {
    power[i].first = (long long)power[i - 1].first * BASE % MOD;
    power[i].second = power[i - 1].second * BASE;
  }

  int len_1 = 0;
  scanf("%d", &n);
  while (n --) {
    scanf("%s", buffer + 1);
    int len_2 = strlen(buffer + 1);
    for (int i = 1; i <= len_2; ++ i) {
      hash_2[i].first = (hash_2[i - 1].first + (long long)buffer[i] * power[i].first) % MOD;
      hash_2[i].second = hash_2[i - 1].second + buffer[i] * power[i].second;
    }

    int found = 0;
    for (int i = std::min(len_1, len_2); i >= 1; -- i) {
      if (str_equal(len_1 - i + 1, len_1, 1, i)) {
        found = i;
        break;
      }
    }

    // std::cerr << found << std::endl;
    for (int i = found + 1; i <= len_2; ++ i) {
      string[++ len_1] = buffer[i];
      hash_1[len_1].first = (hash_1[len_1 - 1].first + (long long)buffer[i] * power[len_1].first) % MOD;
      hash_1[len_1].second = hash_1[len_1 - 1].second + buffer[i] * power[len_1].second;
    }
  }
  string[++ len_1] = 0;
  puts(string + 1);
  return 0;
}
