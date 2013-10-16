#include <cstdio>
#include <set>
#include <vector>
#include <queue>

const int N = 1000000 + 10;
const int M = 250000 + 10;

struct Group {
	int size, id;
	Group(int size = 0, int id = 0): size(size), id(id) {} 
	bool operator < (const Group &g) const {
		return size < g.size || size == g.size && id < g.id;
	}
	bool operator == (const Group &g) const {
		return size == g.size && id == g.id;
	}
};

std::set<Group> set;
std::vector<int> belongs[N];
std::set<int> contains[M];
std::queue<int> queue;
bool visit[N];
int n, m, size[M];

int main() {
	freopen("invite.in", "r", stdin);
	freopen("invite.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++ i) {
		int number;
		scanf("%d", &number);
		set.insert(Group(number, i));
		size[i] = number;
		while (number --) {
			int x;
			scanf("%d", &x);
			belongs[x].push_back(i);
			contains[i].insert(x);
		}
	}

	queue.push(1);
	int answer = 0;
	while (!queue.empty()) {
		int x = queue.front();
		queue.pop();
		if (visit[x]) {
			continue;
		}
		visit[x] = true;
		answer ++;
		for (int i = 0; i < belongs[x].size(); ++ i) {
			int id = belongs[x][i];
			set.erase(Group(size[id], id));
			contains[id].erase(x);
			size[id] --;
			if (size[id] > 0) {
				set.insert(Group(size[id], id));
			}
		}
		while (!set.empty()) {
			int s = (*set.begin()).size;
			if (s == 0) {
				set.erase(set.begin());
			} else if (s == 1) {
				int id = (*set.begin()).id;
				set.erase(Group(size[id], id));
				int x = *(contains[id].begin());
				queue.push(x);
			} else {
				break;
			}
		}
	}
	printf("%d\n", answer);
	return 0;
}
