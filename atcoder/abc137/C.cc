#include <bits/stdc++.h>

const int N = 100000 + 10;

std::string strings[N];
int n;

bool cmp(char* a, char* b) {
  return strcmp(a, b) < 0;
}

int main() {
  char buffer[12];
  scanf("%d", &n);
  for (int i = 1; i <= n; ++ i) {
    scanf("%s", buffer);
    int length = strlen(buffer);
    std::sort(buffer, buffer + length);
    strings[i] = buffer;
  }
  std::sort(strings + 1, strings + n + 1);

  long long answer = 0;
  for (int i = 1; i <= n; ) {
    int j = i + 1;
    while (j <= n && strings[i] == strings[j]) {
      j ++;
    }
    long long x = j - i;
    answer += x * (x - 1) / 2;
    i = j;
  }
  printf("%lld\n", answer);
  return 0;
}
