#include <bits/stdc++.h>

const int N = 150;

std::vector<std::pair<int, int>> positive, negative;
bool visited[N];
int n, r;

bool cmp(const std::pair<int, int>& a, const std::pair<int, int>& b) {
  return a.first - a.second > b.first - b.second;
}

int main() {
  scanf("%d%d", &n, &r);
  for (int i = 1; i <= n; ++ i) {
    int a, b;
    scanf("%d%d", &a, &b);
    if (b >= 0) {
      positive.push_back(std::make_pair(a, b));
    } else {
      negative.push_back(std::make_pair(a, -b));
    }
  }
  std::sort(positive.begin(), positive.end());

  bool valid = true;
  for (auto p : positive) {
    if (r < p.first) {
      valid = false;
      break;
    }
    r += p.second;
  }
  if (!valid) {
    puts("NO");
    return 0;
  }

  for (auto& p : negative) {
    p.first = std::max(p.first, p.second);
  }
  std::sort(negative.begin(), negative.end(), cmp);

  for (auto p : negative) {
    if (r < p.first) {
      valid = false;
      break;
    }
    r -= p.second;
  }
  puts(valid ? "YES" : "NO");
  return 0;
}
