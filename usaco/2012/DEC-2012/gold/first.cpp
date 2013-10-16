#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>

const int N = 300000 + 10;
const int M = 27;

int children[N][M], node_count;
bool end[N];

void insert(const std::string& string) {
	int u = 0;
	for (int i = 0; i < string.length(); ++ i) {
		int key = string[i] - 'a';
		if (children[u][key] == 0) {
			children[u][key] = ++ node_count;
		}
		u = children[u][key];
	}
	end[u] = true;
}

std::string string[N];
std::vector<int> neighbors[M];
bool visit[M];
int n;

bool judge_cycle(int u) {
	visit[u] = true;
	for (int i = 0; i < neighbors[u].size(); ++ i) {
		int v = neighbors[u][i];
		if (visit[v] || judge_cycle(v)) {
			return true;
		}
	}
	visit[u] = false;
	return false;
}

int main() {
	freopen("first.in", "r", stdin);
	freopen("first.out", "w", stdout);
	std::ios::sync_with_stdio(false);
	std::cin >> n;
	for (int i = 0; i < n; ++ i) {
		std::cin >> string[i];
		insert(string[i]);
	}
	std::vector<int> answer;
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < 26; ++ j) {
			neighbors[j].clear();
		}
		bool prefix = false;
		for (int j = 0, u = 0; j < string[i].length(); ++ j) {
			if (end[u]) {
				prefix = true;
				break;
			}
			int key = string[i][j] - 'a';
			for (int k = 0; k < 26; ++ k) {
				if (k != key && children[u][k]) {
					neighbors[k].push_back(key);
				}
			}
			u = children[u][key];
		}
		if (prefix) {
			continue;
		}
		for (int j = 0; j < 26; ++ j) {
			std::sort(neighbors[j].begin(), neighbors[j].end());
			neighbors[j].resize(unique(neighbors[j].begin(), neighbors[j].end()) - neighbors[j].begin());
		}

		memset(visit, 0, sizeof(visit));
		bool flag = false;
		for (int j = 0; j < 26; ++ j) {
			if (!visit[j]) {
				flag |= judge_cycle(j);
			}
		}
		if (!flag) {
			answer.push_back(i);
		}
	}
	std::cout << answer.size() << '\n';
	// printf("%d\n", (int)answer.size());
	for (int i = 0; i < answer.size(); ++ i) {
		std::cout << string[answer[i]] << '\n';
	}
	return 0;
}
