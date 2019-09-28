#include <bits/stdc++.h>

namespace {

#ifdef LOCAL
#define run_if_local(statement) statement
#else
#define run_if_local(statement)
#endif

#ifdef LOCAL
auto start_timestamp = clock();
void tag_execution_time() {
  std::cerr << "Execution timestamp: " << std::setprecision(4) << std::fixed
            << ((double)clock() - start_timestamp) / CLOCKS_PER_SEC << "s\n";
}
#else
void tag_execution_time() {}
#endif

template <typename Arg, typename... Args>
void __internal_print(std::ostream& out, Arg&& arg, Args&&... args) {
  out << std::forward<Arg>(arg);
  using expander = int[];
  (void)expander{0, (void(out << ' ' << std::forward<Args>(args)), 0)...};
  out << "\n";
}

template <typename Arg, typename... Args>
void __internal_read(Arg&& arg, Args&&... args) {
  std::cin >> std::forward<Arg>(arg);
  using expander = int[];
  (void)expander{0, (void(std::cin >> std::forward<Args>(args)), 0)...};
}

#define __internal_print_array(out, array, start, end) \
  for (auto _i = start; _i <= end; ++_i) {             \
    out << (array)[_i] << (_i == end ? "\n" : " ");    \
  }

#define __internal_print_2d_array(out, array, rows, cols) \
  for (int i = 1; i <= rows; ++i) {                       \
    for (int j = 1; j <= cols; ++j) {                     \
      out << (array)[i][j] << (j == cols ? "\n" : " ");   \
    }                                                     \
  }

#define __internal_print_container(out, container)                          \
  for (auto _iter = container.begin(); _iter != container.end(); ++_iter) { \
    out << *(_iter) << (_iter + 1 == container.end() ? "\n" : " ");         \
  }

#define print(...) __internal_print(std::cout, __VA_ARGS__)
#define debug(...) __internal_print(std::cerr, __VA_ARGS__)
#define print_array(array, start, end) __internal_print_array(std::cout, array, start, end)
#define debug_array(array, start, end) __internal_print_array(std::cerr, array, start, end)
#define print_container(container) __internal_print_container(std::cout, container)
#define debug_container(container) __internal_print_container(std::cerr, container)
#define print_2d_array(array, rows, cols) __internal_print_2d_array(std::cout, array, rows, cols)
#define debug_2d_array(array, rows, cols) __internal_print_2d_array(std::cerr, array, rows, cols)
#define read(...) __internal_read(__VA_ARGS__)
#define read_array(array, start, end)     \
  for (int _i = start; _i <= end; ++_i) { \
    std::cin >> (array)[_i];              \
  }
#define read_2d_array(array, n, m) \
  for (int i = 1; i <= n; ++i) {   \
    for (int j = 1; j <= m; ++j) { \
      std::cin >> array[i][j];     \
    }                              \
  }

template <typename Type>
void update_max(Type& a, const Type& b) {
  if (a < b) a = b;
}

template <typename Type>
void update_min(Type& a, const Type& b) {
  if (a > b) a = b;
}

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

}  // namespace

const int N = 2000 + 10;

std::vector<int> neighbors[N];
int n, m;

bool visited[N], in_stack[N];
int pos[N];
int stack[N], size = 0;

int dfs(int u) {
  stack[++ size] = u;
  pos[u] = size;
  visited[u] = true;
  in_stack[u] = true;
  for (auto v : neighbors[u]) {
    if (in_stack[v]) {
      return v;
    }
    if (!visited[v]) {
      int x = dfs(v);
      if (x > 0) {
        return x;
      }
    }
  }
  in_stack[u] = false;
  pos[u] = 0;
  size --;
  return 0;
}

std::pair<int, int> edges[N];

void run(int case_id = 0) {
  read(n, m);
  for (int i = 1; i <= m; ++ i) {
    int u, v;
    read(u, v);
    edges[i] = std::make_pair(u, v);
    neighbors[u].push_back(v);
  }
  int found = -1;
  for (int i = 1; i <= n; ++ i) {
    if (!visited[i]) {
      int x = dfs(i);
      if (x > 0) {
        found = x;
        break;
      }
    }
  }
  if (found == -1) {
    print("-1");
    return;
  }

  int l = pos[found], r = size;
  for (auto p : edges) {
    int u = p.first;
    int v = p.second;
    if (l <= pos[u] && pos[u] <= r && l <= pos[v] && pos[v] <= r) {
      if (pos[u] + 1 == pos[v]) continue;
      if (pos[u] == r && pos[v] == l) continue;
      if (pos[u] < pos[v]) {
        for (int i = pos[u] + 1; i < pos[v]; ++ i) {
          pos[stack[i]] = 0;
        }

        int pivot = pos[u];
        for (int i = pos[v]; i <= r; ++ i) {
          stack[++ pivot] = stack[i];
          pos[stack[pivot]] = pivot;
        }
        r = pivot;
      } else {
        l = pos[v];
        r = pos[u];
      }
    }
  }
  print(r - l + 1);
  for (int i = l; i <= r; ++ i) {
    print(stack[i]);
  }
}

void multi_cases_main() {
  int num_tests;
  std::cin >> num_tests;
  for (int t = 1; t <= num_tests; ++t) {
    run(t);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  run();
  return 0;
}
