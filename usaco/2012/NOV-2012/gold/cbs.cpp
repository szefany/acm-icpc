#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

const int N = 10;
const int M = 50000 + 10;

int n, m;

struct Data {
	int element[N];
	Data() {
		memset(element, 0, sizeof(element));
	}
	const int operator [] (int i) const {
		return element[i];
	}
	int& operator [] (int i) {
		return element[i];
	}
	bool operator < (const Data &o) const {
		for (int i = 0; i < n; ++ i) {
			if (element[i] != o[i]) {
				return element[i] - o[i] < 0;
			}
		}
		return false;
	}
};

int closest[M], depth[M];
char map[N][M];
std::map<Data, std::vector<int> > history;

int queue[M];

int main() {
	freopen("cbs.in", "r", stdin);
	freopen("cbs.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) {
		scanf("%s", map[i] + 1);
	}

	memset(closest, -1, sizeof(closest));
	for (int i = 0; i < n; ++ i) {
		int length = 0;
		queue[0] = 0;
		depth[0] = 0;
		for (int j = 1; j <= m; ++ j) {
			depth[j] = depth[j - 1] + (map[i][j] == '(' ? 1 : -1);
			while (length >= 0 && depth[j] <= depth[queue[length]]) {
				length --;
			}
			if (length >= 0) {
				closest[j] = std::max(closest[j], queue[length]);
			}
			queue[++ length] = j;
		}
	}

	Data now;
	history[now].push_back(0);

	int answer = 0;
	for (int j = 1; j <= m; ++ j) {
		for (int i = 0; i < n; ++ i) {
			now[i] += map[i][j] == '(' ? 1 : -1;
		}
		std::vector<int>::iterator iter = std::upper_bound(history[now].begin(), history[now].end(), closest[j]);
		answer += history[now].end() - iter;
		history[now].push_back(j);
	}
	std::cout << answer << std::endl;
	return 0;
}
