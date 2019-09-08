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

const int N = 100000 + 10;
const int S = N << 2;

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

int a[N], l1[N], l2[N], r1[N], r2[N], n;

int values[S];

void update(int u) {
  values[u] = std::max(values[L(u)], values[R(u)]);
}

void insert(int u, int l, int r, int x, int y) {
  if (l == r) {
    values[u] = y;
  } else {
    int m = (l + r) >> 1;
    if (x <= m) {
      insert(L(u), l, m, x, y);
    } else {
      insert(R(u), m + 1, r, x, y);
    }
    update(u);
  }
}

int query_right(int u, int l, int r, int a, int b, int k) {
  if (a > b || b < l || a > r || values[u] < k) {
    return -1;
  }
  if (l == r) {
    return l;
  }
  int m = (l + r) >> 1;
  int result = query_right(R(u), m + 1, r, a, b, k);
  if (result == -1) {
    result = query_right(L(u), l, m, a, b, k);
  }
  return result;
}

int query_left(int u, int l, int r, int a, int b, int k) {
  if (a > b || b < l || a > r || values[u] < k) {
    return -1;
  }
  if (l == r) {
    return l;
  }
  int m = (l + r) >> 1;
  int result = query_left(L(u), l, m, a, b, k);
  if (result == -1) {
    result = query_left(R(u), m + 1, r, a, b, k);
  }
  return result;
}

void run(int case_id = 0) {
  read(n);
  read_array(a, 1, n);

  for (int i = 1; i <= n; ++ i) {
    l1[i] = query_right(1, 1, n, 1, i - 1, a[i]);
    if (l1[i] == -1) {
      l2[i] = -1;
    } else {
      l2[i] = query_right(1, 1, n, 1, l1[i] - 1, a[i]);
    }
    insert(1, 1, n, i, a[i]);
  }

  memset(values, 0, sizeof(values));
  for (int i = n; i >= 1; -- i) {
    r1[i] = query_left(1, 1, n, i + 1, n, a[i]);
    if (r1[i] == -1) {
      r2[i] = -1;
    } else {
      r2[i] = query_left(1, 1, n, r1[i] + 1, n, a[i]);
    }
    insert(1, 1, n, i, a[i]);
  }

  // debug_array(l1 + 1, l1 + n + 1);
  // debug_array(l2 + 1, l2 + n + 1);
  // debug_array(r1 + 1, r1 + n + 1);
  // debug_array(r2 + 1, r2 + n + 1);

  long long answer = 0;
  for (int i = 1; i <= n; ++ i) {
    if (l1[i] > 0) {
      int x = l2[i] == -1 ? 0 : l2[i];
      int y = r1[i] == -1 ? n + 1 : r1[i];
      long long temp = (long long)(l1[i] - x) * (y - i) * a[i];
      answer += temp;
    }
    if (r1[i] > 0) {
      int y = r2[i] == -1 ? n + 1 : r2[i];
      int x = l1[i] == -1 ? 0 : l1[i];
      long long temp = (long long)(i - x) * (y - r1[i]) * a[i];
      answer += temp;
    }
  }
  print(answer);
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
