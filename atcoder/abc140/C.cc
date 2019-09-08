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

const int N = 200;

int a[N], b[N], n;

void run(int case_id = 0) {
  read(n);
  read_array(b, 1, n - 1);

  long long answer = b[1] + b[n - 1];
  a[1] = b[1];
  a[n] = b[n - 1];
  for (int i = 2; i <= n - 1; ++ i) {
    a[i] = std::min(b[i - 1], b[i]);
    answer += a[i];
  }
  print(answer);
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
