#include <cstdio>
#include <vector>

const int N = 16;

using std::pair;
using std::make_pair;
typedef pair<int, bool> Pair;

std::vector<Pair> neighbors[N];
int state[N];
int n, m, answer;

void dfs(int u) {
	if (u > n) {
		answer ++;
		return;
	}
	for (state[u] = 0; state[u] < 3; ++ state[u]) {
		bool flag = true;
		for (int i = 0; i < neighbors[u].size(); ++ i) {
			int v = neighbors[u][i].first;
			if (neighbors[u][i].second != (state[u] == state[v])) {
				flag = false;
				break;
			}
		}
		if (flag) {
			dfs(u + 1);
		}
	}
}

int main() {
	freopen("assign.in", "r", stdin);
	freopen("assign.out", "w", stdout);
	scanf("%d%d", &n, &m);
	while (m --) {
		char type[2];
		int u, v;
		scanf("%s%d%d", type, &u, &v);
		bool same = *type == 'S';
		if (u < v) {
			std::swap(u, v);
		}
		neighbors[u].push_back(make_pair(v, same));
	}
	dfs(1);
	printf("%d\n", answer);
	return 0;
}
