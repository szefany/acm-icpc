#include <cstdio>
#include <iostream>

const int N = 50000 + 10;

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

Pair a[N], b[N];
int n, m;

int main() {
	freopen("greetings.in", "r", stdin);
	freopen("greetings.out", "w", stdout);
	scanf("%d%d", &n, &m);

	for (int i = 1; i <= n; ++ i) {
		int x;
		char buffer[2];
		scanf("%d%s", &x, buffer);
		int delta = *buffer == 'R' ? 1 : -1;
		a[i] = make_pair(x, delta);
	}
	for (int i = 1; i <= m; ++ i) {
		int x;
		char buffer[2];
		scanf("%d%s", &x, buffer);
		int delta = *buffer == 'R' ? 1 : -1;
		b[i] = make_pair(x, delta);
	}
	int answer = 0;
	for (int i = 1, j = 1, x = 0, y = 0, moment = 0; i <= n || j <= m; ++ moment) {
		int new_x = x;
		int new_y = y;
		while (i <= n && a[i].first == 0) {
			i ++;
		}
		while (j <= m && b[j].first == 0) {
			j ++;
		}
		if (i <= n) {
			new_x = x + a[i].second;
			a[i].first --;
		}
		if (j <= m) {
			new_y = y + b[j].second;
			b[j].first --;
		}
		if (x != y && new_x == new_y) {
			answer ++;
		}
		x = new_x;
		y = new_y;
	}
	printf("%d\n", answer);
}
