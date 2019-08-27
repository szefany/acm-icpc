#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 100000 + 10;

std::vector<Pair> comps;
char string[N];
int answer[N];

void run(int case_id = 0) {
  std::cin >> string + 1;
  int length = strlen(string + 1);
  for (int i = 1; i <= length; ) {
    int j = i;
    while (j <= length && string[i] == string[j]) {
      j ++;
    }
    comps.push_back(make_pair(string[i] - '0', j - i));
    i = j;
  }

  std::priority_queue<int> heap;
  int longest = 0;
  int old_zeros = 0;
  int new_zeros = 0;
  int prev = 0;
  for (auto p : comps) {
    int x = p.first;
    int size = p.second;
    if (x == 0) {
      update_max(longest, old_zeros + size);
      old_zeros += size;
      new_zeros += size;
      for (int i = 1; i <= size; ++ i) {
        answer[prev + i] = 0;
      }
      while (new_zeros > longest) {
        int y = heap.top();
        heap.pop();
        answer[y] = 1;
        new_zeros --;
      }
    } else {
      longest += size;
      new_zeros += size;
      for (int i = 1; i <= size; ++ i) {
        answer[prev + i] = 0;
        heap.push(prev + i);
      }
    }
    prev += size;
  }
  for (int i = 1; i <= prev; ++ i) {
    std::cout << answer[i];
  }
  std::cout << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  run();
  return 0;
}
