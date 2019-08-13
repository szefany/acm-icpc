#include <bits/stdc++.h>

const int N = 2500 + 10;
const int INF = (1 << 30) - 1;

std::vector<std::pair<int, int>> neighbors[N];
bool in_queue[N];
int dist[N], times[N];
int n, m, p;

int main() {
  scanf("%d%d%d", &n, &m, &p);
  for (int i = 0; i < m; ++ i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    neighbors[u].push_back(std::make_pair(v, w - p));
  }

  for (int i = 1; i <= n; ++ i) {
    dist[i] = -INF;
  }
  dist[1] = 0;

  std::queue<int> queue;
  queue.push(1);
  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    in_queue[u] = false;
    for (auto x : neighbors[u]) {
      int v = x.first;
      int w = x.second;
      if (dist[u] + w > dist[v]) {
        dist[v] = dist[u] + w;
        if (!in_queue[v] && times[v] <= n) {
          queue.push(v);
          in_queue[v] = true;
          times[v] ++;
          if (times[v] > n) {
            dist[v] = INF;
          }
        }
      }
    }
  }
  if (dist[n] >= INF) {
    puts("-1");
  } else {
    printf("%d\n", std::max(0, dist[n]));
  }
  return 0;
}
