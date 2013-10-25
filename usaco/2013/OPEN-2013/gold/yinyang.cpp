#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 100000 + 10;
const int M = N << 1;

struct Edge {
	int to, color, next;
	Edge(int v = 0, int c = 0, int n = 0): to(v), color(c), next(n) {}
} g[M];
int first[N], edge_count;

void add_edge(int u, int v, int c) {
	edge_count ++;
	g[edge_count] = Edge(v, c, first[u]), first[u] = edge_count;
}

bool valid[N];
int black[N], white[N], father[N], size[N];
int n;
long long answer;

bool visit[N];

void get_nodes(int u, int p, std::vector<int>& nodes) {
	nodes.push_back(u);
	father[u] = p;
	for (int iter = first[u]; iter; iter = g[iter].next) {
		int v = g[iter].to;
		if (!visit[v] && v != p) {
			get_nodes(v, u, nodes);
		}
	}
}

int get_root(int r) {
	std::vector<int> nodes;
	get_nodes(r, 0, nodes);
	int s = nodes.size();
	for (int i = s - 1; i >= 0; -- i) {
		int u = nodes[i];
		size[u] = 1;
		for (int iter = first[u]; iter; iter = g[iter].next) {
			int v = g[iter].to;
			if (v != father[u] && !visit[v]) {
				size[u] += size[v];
			}
		}
	}

	int root = -1;
	int min_size = -1;
	foreach(i, nodes) {
		int u = *i;
		int temp = s - size[u];
		for (int iter = first[u]; iter; iter = g[iter].next) {
			int v = g[iter].to;
			if (v != father[u] && !visit[v]) {
				temp = std::max(temp, size[v]);
			}
		}
		if (root == -1 || temp < min_size) {
			root = u;
			min_size = temp;
		}
	}
	return root;
}

int exist[N + N];

void get_key(int u, int p, int color, int root_key) {
	white[u] = white[p] + (color == 0);
	black[u] = black[p] + (color == 1);
	int key = white[u] - black[u];
	if (key == 0 && root_key > 1) {
		answer ++;
	}
	root_key += key == 0;
	valid[u] = exist[key + N] > 0;
	exist[key + N] ++;
	
	for (int iter = first[u]; iter; iter = g[iter].next) {
		int v = g[iter].to;
		if (v != p && !visit[v]) {
			get_key(v, u, g[iter].color, root_key);
		}
	}
	exist[key + N] --;
}

std::map<int, int> map, valid_map;
std::vector<int> nodes;

void solve(int u) {
	int root = get_root(u);
	get_key(root, 0, -1, 0);

	map.clear();
	valid_map.clear();
	nodes.clear();
	int count = 0;

	for (int iter = first[root]; iter; iter = g[iter].next) {
		int v = g[iter].to;
		if (!visit[v]) {
			nodes.clear();
			get_nodes(v, root, nodes);
			foreach(iter2, nodes) {
				int w = *iter2;
				int key = white[w] - black[w];
				if (key == 0) {
					answer += count;
				} else {
					if (valid[w]) {
						answer += map[-key];
					} else {
						answer += valid_map[-key];
					}
				}
			}
			foreach(iter2, nodes) {
				int w = *iter2;
				int key = white[w] - black[w];
				if (key == 0) {
					count ++;
				} else {
					map[key] ++;
					if (valid[w]) {
						valid_map[key] ++;
					}
				}
			}
		}
	}

	visit[root] = true;
	for (int iter = first[root]; iter; iter = g[iter].next) {
		int v = g[iter].to;
		if (!visit[v]) {
			solve(v);
		}
	}
}

int main() {
	freopen("yinyang.in", "r", stdin);
	freopen("yinyang.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i < n; ++ i) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		add_edge(u, v, c);
		add_edge(v, u, c);
	}
	solve(1);
	printf("%lld\n", answer);
	return 0;
}
