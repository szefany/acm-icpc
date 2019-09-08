#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 1000 + 10;

bool visited[N], busy[N][N];
int a[N][N], pivot[N];
int n;

std::queue<Pair> candidates[2];

void add(std::queue<Pair>& queue, int x, int y) {
  if (x > y) std::swap(x, y);
  queue.push(make_pair(x, y));
}

void run(int case_id = 0) {
  std::cin >> n;
  for (int i = 1; i <= n; ++ i) {
    pivot[i] = 1;
    for (int j = 1; j < n; ++ j) {
      std::cin >> a[i][j];
    }
  }

  for (int i = 1; i <= n; ++ i) {
    int x = a[i][1];
    if (x > i && a[x][1] == i) {
      add(candidates[1], i, x);
    }
  }

  int day = 0;
  int done = 0;
  while (done < n * (n - 1) / 2) {
    day ++;
    int now = day & 1;
    if (candidates[now].empty()) {
      day = -1;
      break;
    }
    while (!candidates[now].empty()) {
      int x = candidates[now].front().first;
      int y = candidates[now].front().second;
      candidates[now].pop();
      pivot[x] ++;
      pivot[y] ++;
      done ++;
      if (pivot[x] <= n - 1) {
        int x2 = a[x][pivot[x]];
        if (a[x2][pivot[x2]] == x) {
          add(candidates[now ^ 1], x, x2);
        }
      }
      if (pivot[y] <= n - 1) {
        int y2 = a[y][pivot[y]];
        if (a[y2][pivot[y2]] == y) {
          add(candidates[now ^ 1], y, y2);
        }
      }
    }
  }
  std::cout << day << std::endl;
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
