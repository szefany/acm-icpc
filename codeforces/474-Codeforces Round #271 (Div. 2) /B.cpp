#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);

  std::vector<int> sum;
  int s = 0;
  for (int i = 0; i < n; ++ i) {
    int x;
    scanf("%d", &x);
    s += x;
    sum.push_back(s);
  }
  int q;
  scanf("%d", &q);
  while (q --) {
    int x;
    scanf("%d", &x);
    int id = std::lower_bound(sum.begin(), sum.end(), x) - sum.begin() + 1;
    printf("%d\n", id);
  }
  return 0;
}
