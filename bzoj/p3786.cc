#include <bits/stdc++.h>

namespace {

#ifdef LOCAL
template <typename Arg, typename... Args>
void __internal_print(std::ostream& out, Arg&& arg, Args&&... args) {
  out << std::forward<Arg>(arg);
  using expander = int[];
  (void)expander{0, (void(out << ' ' << std::forward<Args>(args)), 0)...};
  out << "\n";
}

#define print(...) __internal_print(std::cout, __VA_ARGS__)
#define debug(...) __internal_print(std::cerr, __VA_ARGS__)

#else
void tag_execution_time() {}
#define debug(...) void()
#endif

char buf[1 << 20], *p1 = buf, *p2 = buf;
#define getchar() \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)

namespace io {

template <typename Type>
inline void read(Type& result) {
  result = 0;
  int flag = 1;
  char c;
  while (c = getchar(), c < '0' || c > '9') {
    if (c == '-') flag = -1;
  }
  while (c >= '0' && c <= '9') {
    result = result * 10 + (c & 15);
    c = getchar();
  }
  if (flag == -1) result = -result;
}

}  // namespace io

#define FAST_INPUT 1

#ifdef FAST_INPUT
#define read(x) io::read(x)
#else
template <typename Arg, typename... Args>
void __internal_read(Arg&& arg, Args&&... args) {
  std::cin >> std::forward<Arg>(arg);
  using expander = int[];
  (void)expander{0, (void(std::cin >> std::forward<Args>(args)), 0)...};
}
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
#endif

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

}  // namespace

const int N = 200000 + 10;

int weight[N];

struct SplayTree {
  static const int N = 200000 + 10;

  int child[N][2], size[N], father[N];
  int mark[N];
  long long sum[N], value[N], cover[N];
  int root, n;

  inline int& L(int u) {
    return child[u][0];
  }
  inline int& R(int u) {
    return child[u][1];
  }

  inline void new_node(int& u, int f, int x, int v) {
    u = x;
    father[u] = f;
    L(u) = R(u) = 0;
    mark[u] = x > n ? 0 : (v > 0 ? 1 : -1);
    size[u] = mark[u];
    value[u] = sum[u] = weight[std::abs(v)] * mark[u];
    cover[u] = 0;
  }

  inline void update(int u) {
    if (u) {
      size[u] = size[L(u)] + size[R(u)] + mark[u];
      sum[u] = sum[L(u)] + sum[R(u)] + value[u];
    }
  }

  inline void update_cover(int u, int c) {
    if (u) {
      cover[u] += c;
      value[u] += c * mark[u];
      sum[u] += (long long)c * size[u];
    }
  }

  void push_down(int u) {
    if (u > 0 && father[u] > 0) push_down(father[u]);
    if (u > 0 && cover[u] != 0) {
      update_cover(L(u), cover[u]);
      update_cover(R(u), cover[u]);
      cover[u] = 0;
    }
  }

  void build(int l, int r, int& u, int f, int* elements) {
    if (l <= r) {
      int m = (l + r) >> 1;
      new_node(u, f, m, elements[m]);
      build(l, m - 1, L(u), u, elements);
      build(m + 1, r, R(u), u, elements);
      update(u);
    }
  }

  void init(int* elements, int n) {
    root = 0;
    value[0] = sum[0] = size[0] = 0;
    cover[0] = 0;
    this->n = n;

    new_node(root, 0, n + 1, 0);
    new_node(R(root), root, n + 2, 0);
    build(1, n, L(R(root)), R(root), elements);
    update(R(root));
    update(root);
  }

  inline void rotate(int u, int d) {
    int f = father[u], r = R(f) == u;
    int v = child[u][d];
    int w = child[v][d ^ 1];

    child[u][d] = w, father[w] = u;
    child[v][d ^ 1] = u, father[u] = v;
    child[f][r] = v, father[v] = f;
    update(u);
  }

  void splay(int u, int target) {
    if (u == 0) return;  // splay(0) might introduce unpredictable bugs.
    push_down(u);
    while (father[u] != target) {
      int f = father[u];
      if (father[f] == target) {
        rotate(f, R(f) == u);
      } else {
        int g = father[f];
        int d = R(g) == f;
        if (child[f][d] == u) {
          rotate(g, d);
          rotate(f, d);
        } else {
          rotate(f, d ^ 1);
          rotate(g, d);
        }
      }
    }
    update(u);
    if (target == 0) {
      root = u;
    }
  }

  void cover_value(int l, int r, int c) {
    l = prev_node(l);
    r = next_node(r);
    splay(l, 0);
    splay(r, root);

    int u = L(R(root));
    update_cover(u, c);
    update(R(root));
    update(root);
  }

  long long get_prefix_sum(int u) {
    splay(u, 0);
    return sum[L(root)] + value[u];
  }

  int prev_node(int u) {
    splay(u, 0);
    int v = L(root);
    while (R(v) != 0) v = R(v);
    return v;
  }

  int next_node(int u) {
    splay(u, 0);
    int v = R(root);
    while (L(v) != 0) v = L(v);
    return v;
  }

  int cut(int l, int r) {
    l = prev_node(l);
    r = next_node(r);
    splay(l, 0);
    splay(r, root);
    int u = L(R(root));
    L(R(root)) = 0;
    father[u] = 0;
    update(R(root));
    update(root);
    return u;
  }

  void link(int f, int u) {
    int r = next_node(f);
    splay(f, 0);
    splay(r, root);
    L(R(root)) = u;
    father[u] = R(root);
    update(R(root));
    update(root);
  }

  void debug_tree(int u) {
    push_down(u);
    debug(u, "size =", size[u], "value =", value[u], "sum =", sum[u], "left =", L(u),
          ", right =", R(u));
    if (L(u)) {
      debug_tree(L(u));
    }
    if (R(u)) {
      debug_tree(R(u));
    }
  }
};

struct EulerTourTree {
  static const int N = 200000 + 10;

  std::vector<int> neighbors[N];
  int enter[N], leave[N], positions[N], num_entries;
  int root;
  int n;
  SplayTree splay;

  inline void init(int n) {
    root = 1;
    num_entries = 0;
    this->n = n;
  }

  void add_edge(int u, int v) {
    neighbors[u].push_back(v);
  }

  void build() {
    dfs(1, 0);
    splay.init(positions, n * 2);
  }

  void dfs(int u, int p) {
    positions[++num_entries] = u;
    enter[u] = num_entries;
    for (int i = 0; i < neighbors[u].size(); ++i) {
      int v = neighbors[u][i];
      if (v != p) {
        dfs(v, u);
      }
    }
    positions[++num_entries] = -u;
    leave[u] = num_entries;
  }

  inline void set_father(int u, int f) {
    int node = splay.cut(enter[u], leave[u]);
    splay.link(enter[f], node);
  }

  inline long long get_sum(int u) {
    return splay.get_prefix_sum(enter[u]);
  }

  inline void add_value(int u, int delta) {
    splay.cover_value(enter[u], leave[u], delta);
  }
} tree;

int n;

void run(int case_id = 0) {
  read(n);
  tree.init(n);
  for (int i = 2; i <= n; ++i) {
    int f;
    read(f);
    tree.add_edge(f, i);
  }
  for (int i = 1; i <= n; ++i) {
    read(weight[i]);
  }
  tree.build();

  int q;
  read(q);
  while (q--) {
    char oper = 0;
    while (oper < 'A' || oper > 'Z') oper = getchar();
    if (oper == 'Q') {
      int u;
      read(u);
      printf("%lld\n", tree.get_sum(u));
    } else {
      int u, v;
      read(u);
      read(v);
      if (oper == 'C') {
        tree.set_father(u, v);
      } else {
        tree.add_value(u, v);
      }
    }
  }
}

int main() {
  run();
  return 0;
}
