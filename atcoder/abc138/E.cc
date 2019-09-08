#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 100000 + 10;

int next[N][26];
int pos[26];
std::string s, t;

void run(int case_id = 0) {
  std::cin >> s >> t;
  int n = s.length();
  s += s;
  memset(pos, -1, sizeof(pos));
  for (int i = n + n - 1; i >= n; -- i) {
    char token = s[i] - 'a';
    pos[token] = i - n;
  }
  for (int i = n - 1; i >= 0; -- i) {
    for (int c = 0; c <= 25; ++ c) {
      next[i][c] = pos[c];
    }
    char token = s[i] - 'a';
    pos[token] = i;
  }

  long long answer = 0;
  int pivot = -1;
  for (int i = 0; i < t.length(); ++ i) {
    char token = t[i] - 'a';
    int x = -1;
    if (pivot == -1) {
      x = pos[token];
    } else {
      x = next[pivot][token];
    }
    if (x == -1) {
      answer = -1;
      break;
    }
    int delta = x - pivot;
    if (delta <= 0) delta += n;
    answer += delta;
    pivot = x;
  }
  std::cout << answer << std::endl;
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
