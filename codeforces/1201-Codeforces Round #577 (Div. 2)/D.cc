#include <bits/stdc++.h>

const int N = 200000 + 10;

struct Data {
  int x, y;
  Data(int x = 0, int y = 0) : x(x), y(y) {}
};

std::unordered_map<long long, long long> min_steps;
std::queue<Data> queue;
int safe[N], leftmost[N], rightmost[N];
int n, m, k, q;
long long answer = 1LL << 60;

long long get_id(long long x, long long y) {
  return (x - 1) * m + y;
}

void update_min(int& a, int b) {
  if (a == -1 || b < a) a = b;
}

void update_max(int& a, int b) {
  if (a == -1 || b > a) a = b;
}

void insert(int x, int y, long long value) {
  long long id = get_id(x, y);
  if (min_steps.find(id) == min_steps.end()) {
    min_steps[id] = value;
    queue.push(Data(x, y));
  } else if (value < min_steps[id]) {
    min_steps[id] = value;
  }
}

int get_dist_left(int x, int y, int nx, int ny, int pos) {
  int result = std::abs(pos - y) + std::abs(nx - x);
  result += std::abs(pos - rightmost[nx]) + std::abs(rightmost[nx] - leftmost[nx]);
  return result;
}

int get_dist_right(int x, int y, int nx, int ny, int pos) {
  int result = std::abs(pos - y) + std::abs(nx - x);
  result += std::abs(pos - leftmost[nx]) + std::abs(rightmost[nx] - leftmost[nx]);
  return result;
}

int main() {
  memset(leftmost, -1, sizeof(leftmost));
  memset(rightmost, -1, sizeof(rightmost));

  scanf("%d%d%d%d", &n, &m, &k, &q);
  for (int i = 1; i <= k; ++ i) {
    int x, y;
    scanf("%d%d", &x, &y);
    update_min(leftmost[x], y);
    update_max(rightmost[x], y);
  }
  for (int i = 1; i <= q; ++ i) {
    scanf("%d", safe + i);
  }
  std::sort(safe + 1, safe + q + 1);

  if (rightmost[1] == -1) {
    insert(1, 1, 0);
  } else {
    insert(1, rightmost[1], rightmost[1] - 1);
  }

  while (!queue.empty()) {
    auto d = queue.front();
    int x = d.x, y = d.y;
    long long value = min_steps[get_id(x, y)];
    queue.pop();

    int nx = x + 1;
    while (nx <= n && leftmost[nx] == -1) {
      nx ++;
    }
    if (nx > n) {
      answer = std::min(answer, value);
      continue;
    }

    int pos = std::lower_bound(safe + 1, safe + q + 1, y) - safe;
    if (pos <= q) {
      insert(nx, leftmost[nx], value + get_dist_left(x, y, nx, leftmost[nx], safe[pos]));
    }
    if (pos >= 2) {
      insert(nx, leftmost[nx], value + get_dist_left(x, y, nx, leftmost[nx], safe[pos - 1]));
    }
    if (leftmost[nx] != rightmost[nx]) {
      if (pos <= q) {
        insert(nx, rightmost[nx], value + get_dist_right(x, y, nx, rightmost[nx], safe[pos]));
      }
      if (pos >= 2) {
        insert(nx, rightmost[nx], value + get_dist_right(x, y, nx, rightmost[nx], safe[pos - 1]));
      }
    }
  }
  // if (answer == 1LL << 60) {
  //   answer = 0;
  // }
  std::cout << answer << "\n";
  return 0;
}
