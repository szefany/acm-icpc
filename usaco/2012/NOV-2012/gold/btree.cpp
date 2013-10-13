#include <cstdio>
#include <cstring>
#include <vector>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 40000 + 10;
const int INF = 1 << 29;

std::vector<int> neighbors[N];
int type[N];
int n, answer;

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

Pair min_down[N][2], max_down[N][2];

void count_down(int u, int p) {
	foreach(iter, neighbors[u]) {
		int v = *iter;
		if (v != p) {
			count_down(v, u);
		}
	}
	min_down[u][1] = make_pair(INF, -1);
	max_down[u][1] = make_pair(-INF, -1);
	max_down[u][0] = min_down[u][0] = make_pair(type[u], u);
	foreach(iter, neighbors[u]) {
		int v = *iter;
		if (v != p) {
			int temp = min_down[v][0].first + type[u];
			if (temp < min_down[u][0].first) {
				min_down[u][1] = min_down[u][0];
				min_down[u][0] = make_pair(temp, v);
			} else if (temp < min_down[u][1].first) {
				min_down[u][1] = make_pair(temp, v);
			}

			temp = max_down[v][0].first + type[u];
			if (temp > max_down[u][0].first) {
				max_down[u][1] = max_down[u][0];
				max_down[u][0] = make_pair(temp, v);
			} else if (temp > max_down[u][1].first) {
				max_down[u][1] = make_pair(temp, v);
			}
		}
	}
}

void count_up(int u, int p, int up) {
	up += type[u];
	foreach(iter, neighbors[u]) {
		int v = *iter;
		if (v != p) {
			int x = min_down[u][0].second == v ? min_down[u][1].first : min_down[u][0].first;
			x = std::min(x, up);
			x = -x;
			int y = max_down[v][0].first;
			answer = std::max(answer, std::min(x, y));
		}
	}
	foreach(iter, neighbors[u]) {
		int v = *iter;
		if (v != p) {
			int x = min_down[u][0].second == v ? min_down[u][1].first : min_down[u][0].first;
			count_up(v, u, std::min(up, x));
		}
	}
}

int main() {
	freopen("btree.in", "r", stdin);
	freopen("btree.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 2; i <= n; ++ i) {
		int x;
		scanf("%d", &x);
		neighbors[i].push_back(x);
		neighbors[x].push_back(i);
	}
	for (int i = 1; i <= n; ++ i) {
		char buffer[2];
		scanf("%s", buffer);
		type[i] = *buffer == '(' ? 1 : -1;
	}

	answer = 0;
	count_down(1, 0);
	count_up(1, 0, 0);
	for (int i = 1; i <= n; ++ i) {
		type[i] = -type[i];
	}
	count_down(1, 0);
	count_up(1, 0, 0);

	printf("%d\n", answer);
	return 0;
}
