#include <bits/stdc++.h>

const int N = 3000;

int fact[N], inv_fact[N];
int a[N], b[N], buffer[N], p;

int inverse(int a) {
  return a == 1 ? 1 : (p - p / a) * inverse(p % a) % p;
}

int C(int a, int b) {
  return fact[a] * inv_fact[b] % p * inv_fact[a - b] % p;
}

void get_coeff(int k) {
  int m = p - 1;
  int km = 1;
  for (int i = m; i >= 0; -- i) {
    buffer[i] = -(km * C(m, i)) % p;
    (km *= -k) %= p;
  }
  buffer[0] = (buffer[0] + 1) % p;

  // std::cerr << k << std::endl;
  // for (int i = 0; i <= m; ++ i) {
  //   std::cerr << buffer[i] << " ";
  // }
  // std::cerr << std::endl;
}

int main() {
  scanf("%d", &p);

  fact[0] = 1;
  inv_fact[0] = 1;
  for (int i = 1; i < p; ++ i) {
    fact[i] = fact[i - 1] * i % p;
    inv_fact[i] = inv_fact[i - 1] * inverse(i) % p;
  }

  for (int i = 0; i < p; ++ i) {
    int x;
    scanf("%d", &x);
    if (x == 1) {
      get_coeff(i);
      for (int j = 0; j < p; ++ j) {
        (b[j] += buffer[j]) %= p;
      }
    }
  }
  for (int i = 0; i < p; ++ i) {
    if (b[i] < 0) {
      b[i] += p;
    }
    printf("%d%c", b[i], i == p - 1 ? '\n' : ' ');
  }
  return 0;
}
