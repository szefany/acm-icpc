#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 300 + 10;
const int M = 1000000;
const int INF = 1e9 + 10;

struct Rect {
  int x1, y1, x2, y2;
  void input() {
    std::cin >> x1 >> y1 >> x2 >> y2;
  }
} rects[N];

int connected[N][N], visited[N], match[N];
int n, m;

void dedup(std::vector<int>& v) {
  std::sort(v.begin(), v.end());
  v.resize(std::unique(v.begin(), v.end()) - v.begin());
}

int get_id(const std::vector<int>& v, int x) {
  return std::lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}

struct Edge {
  int to, flow, capa, next;
  Edge(int v = 0, int c = 0, int n = 0): to(v), flow(0), capa(c), next(n) {}
} g[M];
int first[N], arc[N], edge_count;
int vs, vt;

void add_edge(int u, int v, int c) {
  edge_count ++;
  g[edge_count] = Edge(v, c, first[u]), first[u] = edge_count;
  g[M - edge_count] = Edge(u, 0, first[v]), first[v] = M - edge_count;
}

int queue[N], label[N];

bool bfs() {
  memset(label, 0, sizeof(label));
  queue[0] = vs;
  label[vs] = 1;
  for (int head = 0, tail = 0; head <= tail; ++ head) {
    int u = queue[head];
    for (int iter = first[u]; iter; iter = g[iter].next) {
      int v = g[iter].to;
      if (g[iter].flow < g[iter].capa && label[v] == 0) {
        label[v] = label[u] + 1;
        queue[++ tail] = v;
      }
    }
  }
  return label[vt];
}

int dfs(int u, int d) {
  if (u == vt) {
    return d;
  }
  int delta = 0;
  for (int& iter = arc[u]; iter; iter = g[iter].next) {
    int v = g[iter].to;
    if (g[iter].flow < g[iter].capa && label[u] + 1 == label[v]) {
      int r = dfs(v, std::min(d - delta, g[iter].capa - g[iter].flow));
      g[iter].flow += r;
      g[M - iter].flow -= r;
      delta += r;
      if (delta == d) {
        break;
      }
    }
  }
  return delta;
}

void run(int case_id = 0) {
  std::cin >> n >> m;
  std::vector<int> rows, columns;
  for (int i = 1; i <= m; ++ i) {
    rects[i].input();
    rows.push_back(rects[i].x1);
    rows.push_back(rects[i].x2 + 1);
    columns.push_back(rects[i].y1);
    columns.push_back(rects[i].y2 + 1);
  }
  dedup(rows);
  dedup(columns);

  vs = rows.size() + columns.size() + 1;
  vt = rows.size() + columns.size() + 2;
  for (int i = 0; i + 1 < rows.size(); ++ i) {
    add_edge(vs, i + 1, rows[i + 1] - rows[i]);
  }
  for (int i = 0; i + 1 < columns.size(); ++ i) {
    add_edge(rows.size() + i + 1, vt, columns[i + 1] - columns[i]);
  }

  for (int i = 1; i <= m; ++ i) {
    int x1 = get_id(rows, rects[i].x1);
    int x2 = get_id(rows, rects[i].x2 + 1);
    int y1 = get_id(columns, rects[i].y1);
    int y2 = get_id(columns, rects[i].y2 + 1);
    for (int x = x1; x < x2; ++ x) {
      for (int y = y1; y < y2; ++ y) {
        add_edge(x, rows.size() + y, INF);
      }
    }
  }
  int answer = 0;
  while (bfs()) {
    memcpy(arc, first, sizeof(first));
    answer += dfs(vs, INF);
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
