#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 400000 + 10;

std::unordered_map<std::set<int>*, int> set_to_x;

struct Node {
  int x;
  std::set<int>* positions;

  Node() {}
  Node(int x) : x(x) {
    positions = new std::set<int>();
    set_to_x[positions] = x;
  }
};

struct Query {
  int oper, p, x;
  void input() {
    std::cin >> oper;
    if (oper == 1) {
      std::cin >> p >> x;
    } else {
      std::cin >> x;
    }
  }
};

std::vector<int> elements;
std::set<int>* belong[N];
Query queries[N];
Node nodes[N];
int a[N], n;

std::set<int>* merge(std::set<int>* s1, std::set<int>* s2) {
  if (s1->size() > s2->size()) {
    std::swap(s1, s2);
  }
  for (int p : *s1) {
    belong[p] = s2;
    s2->insert(p);
  }
  return s2;
}

int get_id(int x) {
  return std::lower_bound(elements.begin(), elements.end(), x) - elements.begin() + 1;
}

void run(int case_id = 0) {
  std::cin >> n;
  for (int i = 1; i <= n; ++ i) {
    std::cin >> a[i];
    elements.push_back(a[i]);
  }
  int q;
  std::cin >> q;
  for (int i = 1; i <= q; ++ i) {
    queries[i].input();
    elements.push_back(queries[i].x);
  }
  std::sort(elements.begin(), elements.end());
  elements.resize(std::unique(elements.begin(), elements.end()) - elements.begin());

  for (int i = 1; i <= n; ++ i) {
    a[i] = get_id(a[i]);
  }
  for (int i = 1; i <= q; ++ i) {
    queries[i].x = get_id(queries[i].x);
  }

  int size = elements.size();
  for (int i = 1; i <= size; ++ i) {
    nodes[i] = Node(i);
  }

  std::set<int> active;
  for (int i = 1; i <= n; ++ i) {
    int x = a[i];
    nodes[x].positions->insert(i);
    belong[i] = nodes[x].positions;
    active.insert(x);
  }

  for (int i = 1; i <= q; ++ i) {
    // std::cerr << "Query " << i << std::endl;
    // for (int x = 1; x <= size; ++ x) {
    //   std::cerr << "Pos " << x << ": " << nodes[x].positions->size() << "\n";
    // }
    // for (int j = 1; j <= n; ++ j) std::cerr << set_to_x[belong[j]] << " "; std::cerr << "\n";
    int p = queries[i].p;
    int x = queries[i].x;
    if (queries[i].oper == 1) {
      int old_x = set_to_x[belong[p]];
      nodes[old_x].positions->erase(p);
      nodes[x].positions->insert(p);
      belong[p] = nodes[x].positions;
      active.insert(x);
    } else {
      while (!active.empty()) {
        auto iter = active.begin();
        if (*iter < x) {
          nodes[x].positions = merge(nodes[*iter].positions, nodes[x].positions);
          set_to_x[nodes[x].positions] = x;
          nodes[*iter] = Node(*iter);
          active.erase(iter);
        } else {
          break;
        }
      }
      active.insert(x);
    }
  }
  for (int i = 1; i <= n; ++ i) {
    int x = set_to_x[belong[i]];
    std::cout << elements[x - 1] << " ";
  }
  std::cout << "\n";
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
