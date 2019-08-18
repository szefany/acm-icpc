#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 400000 + 10;

int a[N], n, I;
std::vector<int> elements;

void run(int case_id = 0) {
  std::cin >> n >> I;
  for (int i = 1; i <= n; ++ i) {
    std::cin >> a[i];
  }
  int k = std::min(I * 8 / n, 20);
  k = 1 << k;

  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; ) {
    int j = i;
    while (j <= n && a[i] == a[j]) j ++;
    elements.push_back(j - i);
    i = j;
  }

  int answer = 0;
  int number = 0;
  for (int i = 0; i < std::min(k - 1, (int)elements.size()); ++ i) {
    number += elements[i];
  }
  update_max(answer, number);
  for (int i = k - 1; i < elements.size(); ++ i) {
    number += elements[i];
    update_max(answer, number);
    number -= elements[i - k + 1];
  }
  std::cout << n - answer << std::endl;
}

void multi_cases_main() {
  int num_tests;
  std::cin >> num_tests;
  for (int t = 1; t <= num_tests; ++ t) {
    run(t);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
