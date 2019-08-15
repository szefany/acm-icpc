#include <bits/stdc++.h>

const int N = 200000;

int a[N], n;
int counter[N], visited[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++ i) {
    scanf("%d", a + i);
    counter[a[i]] ++;
  }

  int answer = 0;
  for (int i = 1; i < N; ++ i) {
    if (counter[i] == 1) {
      if (i > 1 && !visited[i - 1]) {
        visited[i - 1] = true;
        answer ++;
      } else if (!visited[i]) {
        visited[i] = true;
        counter[i] --;
      } else {
        visited[i + 1] = true;
        counter[i] --;
      }
    } else if (counter[i] > 1) {
      if (i > 1 && !visited[i - 1]) {
        visited[i - 1] = true;
        counter[i] --;
        answer ++;
      }
      if (!visited[i]) {
        visited[i] = true;
        counter[i] --;
      }
      if (counter[i] > 0) {
        visited[i + 1] = true;
        counter[i] --;
      }
    }
    if (visited[i]) answer ++;
  }
  printf("%d\n", answer);
  return 0;
}
