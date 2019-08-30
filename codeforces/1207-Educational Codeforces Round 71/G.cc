#include <bits/stdc++.h>

const int N = 400000 + 10;

namespace ac {
int children[N][26], fail[N], queue[N], num_nodes = 0;
int root = 0;
int current_node = 0;

int new_node() {
  num_nodes ++;
  fail[num_nodes] = 0;
  return num_nodes;
}

int insert(const char* word) {
  int node = 0;
  for (int i = 0; word[i]; ++i) {
    int token = word[i] - 'a';
    if (children[node][token] == 0) {
      children[node][token] = new_node();
    }
    node = children[node][token];
  }
  return node;
}

void build() {
  queue[0] = 0;
  for (int head = 0, tail = 0; head <= tail; ++ head) {
    int u = queue[head];
    for (int key = 0; key < 26; ++key) {
      if (children[u][key] == 0) {
        children[u][key] = children[fail[u]][key];
      } else {
        int v = children[u][key];
        fail[v] = u == 0 ? 0 : children[fail[u]][key];
        queue[++ tail] = v;
      }
    }
  }
}
}

struct Query {
  int type, from;
  char token;

  std::vector<int> next;
  std::vector<std::pair<int, int>> tasks;  // (node, task_id)

  void input() {
    std::cin >> type;
    char buffer[2];
    if (type == 1) {
      std::cin >> buffer;
    } else {
      std::cin >> from >> buffer;
    }
    token = *buffer;
  }
} queries[N];

char text[N];
int answer[N];
int n, m;

int sum[N], bit_size = 0;

int lowbit(int x) {
  return x & (-x);
}

void add(int x, int delta) {
  for (; x <= bit_size; x += lowbit(x)) {
    sum[x] += delta;
  }
}

int get_sum(int x) {
  int result = 0;
  for (; x > 0; x -= lowbit(x)) {
    result += sum[x];
  }
  return result;
}

std::vector<int> children[N];
int position[N], size[N], num_series = 0;

void dfs(int u, int p) {
  size[u] = 1;
  position[u] = ++ num_series;
  for (auto v : children[u]) {
    dfs(v, u);
    size[u] += size[v];
  }
}

void traverse_queries(int u, int node) {
  int key = queries[u].token - 'a';
  node = ac::children[node][key];
  add(position[node], 1);

  for (auto p : queries[u].tasks) {
    int v = p.first;
    int id = p.second;
    answer[id] = get_sum(position[v] + size[v] - 1) - get_sum(position[v] - 1);
  }
  for (auto v : queries[u].next) {
    traverse_queries(v, node);
  }
  add(position[node], -1);
}

void run() {
  std::cin >> n;
  for (int i = 1; i <= n; ++ i) {
    queries[i].input();
    if (queries[i].type == 2) {
      queries[queries[i].from].next.push_back(i);
    }
  }

  std::cin >> m;
  for (int i = 1; i <= m; ++ i) {
    int x = 0;
    std::cin >> x >> text;
    int node = ac::insert(text);
    queries[x].tasks.emplace_back(node, i);
  }
  ac::build();

  bit_size = ac::num_nodes + 1;
  for (int u = 1; u <= ac::num_nodes; ++ u) {
    children[ac::fail[u]].push_back(u);
  }
  dfs(0, -1);

  for (int i = 1; i <= n; ++ i) {
    if (queries[i].type == 1) {
      traverse_queries(i, 0);
    }
  }
  for (int i = 1; i <= m; ++ i) {
    std::cout << answer[i] << "\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
