#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 300;

std::vector<int> all_x, all_y;
int max_x, max_y;

void transform(std::vector<int> &v) {
	std::sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
}

struct Point {
	int x, y, id;
	Point(int x = 0, int y = 0, int id = -1): x(x), y(y), id(id) {}
	void norm() {
		x = std::lower_bound(all_x.begin(), all_x.end(), x) - all_x.begin() + 1;
		y = std::lower_bound(all_y.begin(), all_y.end(), y) - all_y.begin() + 1;
	}
	void input(int i) {
		id = i;
		scanf("%d%d", &y, &x);
	}
} points[N];

const int D[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int T[2][4] = {{3, 2, 1, 0}, {1, 0, 3, 2}};

bool to_right[N];
int n;

int tag[N][N];
bool visit[N][N][4];

bool solve() {
	memset(visit, 0, sizeof(visit));
	bool found = false;
	int x = points[n + 1].x;
	int y = points[n + 1].y;
	int d = 1;
	while (1) {
		if (x == points[0].x && y == points[0].y) {
			found = true;
			break;
		}
		if (x < 1 || x > max_x || y < 1 || y > max_y || visit[x][y][d]) {
			break;
		}
		visit[x][y][d] = true;
		if (tag[x][y] != -1) {
			d = T[tag[x][y]][d];
		}
		x += D[d][0];
		y += D[d][1];
	}
	return found;
}

int main() {
	freopen("mirrors.in", "r", stdin);
	freopen("mirrors.out", "w", stdout);
	scanf("%d", &n);
	points[0].input(0);
	for (int i = 1; i <= n; ++ i) {
		points[i].input(i);
		char buffer[2];
		scanf("%s", buffer);
		to_right[i] = *buffer == '/';
	}
	points[n + 1] = Point(0, 0);
	for (int i = 0; i <= n + 1; ++ i) {
		all_x.push_back(points[i].x);
		all_y.push_back(points[i].y);
	}
	transform(all_x);
	transform(all_y);
	max_x = all_x.size();
	max_y = all_y.size();

	memset(tag, -1, sizeof(tag));
	for (int i = 0; i <= n + 1; ++ i) {
		points[i].norm();
		if (i >= 1 && i <= n) {
			tag[points[i].x][points[i].y] = to_right[points[i].id];
		}
	}
	
	if (solve()) {
		puts("0");
	} else {
		int answer = -1;
		for (int i = 1; i <= n; ++ i) {
			tag[points[i].x][points[i].y] ^= 1;
			if (solve()) {
				answer = i;
				break;
			}
			tag[points[i].x][points[i].y] ^= 1;
		}
		printf("%d\n", answer);
	}
	
}
