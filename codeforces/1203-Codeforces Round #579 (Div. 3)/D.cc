#include <bits/stdc++.h>

const int N = 200000 + 10;

char a[N], b[N];
int prefix[N], suffix[N];
int len_a, len_b;

int main() {
  scanf("%s", a + 1);
  scanf("%s", b + 1);
  len_a = strlen(a + 1);
  len_b = strlen(b + 1);

  for (int j = 1, i = 0; j <= len_b; ++ j) {
    while (i + 1 <= len_a && a[i + 1] != b[j]) i ++;
    if (a[i + 1] == b[j]) i ++;
    prefix[j] = i;
  }
  for (int j = len_b, i = len_a + 1; j >= 1; -- j) {
    while (i - 1 >= 1 && a[i - 1] != b[j]) i --;
    if (a[i - 1] == b[j]) i --;
    suffix[j] = i;
  }

  int answer = std::max(len_a - prefix[len_b], suffix[1] - 1);
  for (int i = 1; i < len_b; ++ i) {
    int x = prefix[i];
    int y = suffix[i + 1];
    if (x < y) {
      answer = std::max(answer, y - x - 1);
    }
  }
  printf("%d\n", answer);
  return 0;
}
