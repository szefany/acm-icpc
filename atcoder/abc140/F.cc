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

#define __internal_print_array(out, start, end)     \
  for (auto iter = start; iter != end; ++iter) {    \
    out << *iter << (iter + 1 == end ? "\n" : " "); \
  }

#define __internal_print_2d_array(out, array, rows, cols) \
  for (int i = 1; i <= rows; ++i) {                       \
    for (int j = 1; j <= cols; ++j) {                     \
      out << array[i][j] << (j == cols ? "\n" : " ");     \
    }                                                     \
  }

#define print(...) __internal_print(std::cout, __VA_ARGS__)
#define debug(...) __internal_print(std::cerr, __VA_ARGS__)
#define print_array(start, end) __internal_print_array(std::cout, start, end)
#define debug_array(start, end) __internal_print_array(std::cout, start, end)
#define print_2d_array(array, rows, cols) __internal_print_2d_array(std::cin, array, rows, cols)
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

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

}  // namespace

const int N = 300000;
const int S = N << 2;

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

int values[S];
int a[N];
int n, m;

void insert(int u, int l, int r, int x) {
  if (l == r) {
    // values[u] = std::make_pair(1, l);
    values[u] = 1;
  } else {
    int m = (l + r) >> 1;
    if (x <= m) {
      insert(L(u), l, m, x);
    } else {
      insert(R(u), m + 1, r, x);
    }
    values[u] = std::min(values[L(u)], values[R(u)]);
  }
}

int query(int u, int l, int r, int a, int b) {
  if (b < l || a > r || a > b || values[u] == 1) {
    return -1;
  }
  if (l == r) return l;
  int m = (l + r) >> 1;
  int result = query(L(u), l, m, a, b);
  if (result == -1) {
    result = query(R(u), m + 1, r, a, b);
  }
  return result;
}

int right[N];

void run(int case_id = 0) {
  read(n);
  m = 1 << n;
  read_array(a, 1, m);
  std::sort(a + 1, a + m + 1, std::greater<int>());

  for (int i = m; i >= 1; ) {
    int j = i;
    while (j >= 1 && a[j] == a[i]) {
      right[j] = i + 1;
      j --;
    }
    i = j;
  }

  std::vector<int> current[2];
  current[1].push_back(1);
  insert(1, 1, m, 1);
  for (int days = 1; days <= n; ++ days) {
    int now = days & 1;
    int next = now ^ 1;
    std::sort(current[now].begin(), current[now].end());
    current[next] = current[now];
    for (auto x : current[now]) {
      int y = query(1, 1, m, right[x], m);
      if (y == -1 || a[x] <= a[y]) {
        print("No");
        return;
      }
      current[next].push_back(y);
      insert(1, 1, m, y);
    }
  }
  print("Yes");
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
