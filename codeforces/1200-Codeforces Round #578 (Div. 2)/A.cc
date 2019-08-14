#include <bits/stdc++.h>

const int N = 100000 + 10;

bool filled[10];
char string[N];

int main() {
  int n;
  scanf("%d", &n);
  scanf("%s", string);
  for (int i = 0; i < n; ++ i) {
    if (string[i] == 'L') {
      for (int j = 0; j <= 9; ++ j) {
        if (!filled[j]) {
          filled[j] = true;
          break;
        }
      }
    } else if (string[i] == 'R') {
      for (int j = 9; j >= 0; -- j) {
        if (!filled[j]) {
          filled[j] = true;
          break;
        }
      }
    } else {
      int x = string[i] - '0';
      filled[x] = false;
    }
  }
  for (int i = 0; i <= 9; ++ i) {
    putchar(filled[i] ? '1' : '0');
  }
  puts("");
  return 0;
}
