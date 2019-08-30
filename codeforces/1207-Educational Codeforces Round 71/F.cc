#include <bits/stdc++.h>

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

#define update_max(a, b) if ((a) < (b)) (a) = (b)
#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int N = 500000 + 1;
const int B = 1000;

int delta[B][B];
int a[N];

int read() {
  char c;
  int flag = 1;
  while (c = getchar(), c < '0' || c > '9') {
    if (c == '-') flag = -1;
  }
  int result = c & 15;
  while (c = getchar(), c >= '0' && c <= '9') {
    result = result * 10 + (c & 15);
  }
  return flag > 0 ? result : -result;
  return result * flag;
}

void write(int x) {
  static char buf[20], len;
  len = 0;
	if (x < 0) {
    putchar('-');
    x = -x;
  }
	for (; x; x /= 10) {
    buf[len ++] = x % 10 + '0';
  }
	if (!len) {
    putchar('0');
  } else {
    while (len) {
      putchar(buf[-- len]);
    }
  }
}

void run(int case_id = 0) {
  int q = read();
  int sum = 0;
  while (q --) {
    int t = read();
    int x = read();
    int y = read();
    if (t == 1) {
      a[x] += y;
      sum += y;
      for (int i = 2; i < B; ++ i) {
        delta[i][x % i] += y;
      }
    } else {
      int result = 0;
      if (x == 1) {
        result = sum;
      } else if (x < B) {
        result = delta[x][y];
      } else {
        for (int i = y; i < N; i += x) {
          result += a[i];
        }
      }
      write(result);
      putchar('\n');
    }
  }
}

int main() {
  run();
  return 0;
}
