#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 500000 + 10;

Pair edges[N];
bool visited[N];
int n, m;

void run(int case_id = 0) {
  std::cin >> n >> m;
  for (int i = 1; i <= m; ++ i) {
    int u, v;
    std::cin >> u >> v;
    edges[i] = make_pair(u, v);
  }
  for (int i = 1; i <= 3 * n; ++ i) {
    visited[i] = false;
  }
  std::vector<int> chosen_edges;
  for (int i = 1; i <= m; ++ i) {
    int u = edges[i].first;
    int v = edges[i].second;
    if (!visited[u] && !visited[v]) {
      chosen_edges.push_back(i);
      visited[u] = visited[v] = true;
    }
  }
  if (chosen_edges.size() >= n) {
    std::cout << "Matching" << "\n";
    for (int i = 0; i < n; ++ i) {
      std::cout << chosen_edges[i] << " ";
    }
    std::cout << "\n";
  } else {
    std::cout << "IndSet" << "\n";
    int counter = 0;
    for (int i = 1; i <= 3 * n && counter < n; ++ i) {
      if (!visited[i]) {
        std::cout << i << " ";
        counter ++;
      }
    }
    std::cout << "\n";
  }
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
  multi_cases_main();
  return 0;
}
