#include <cstdio>
#include <cstring>
#include <map>
#include <set>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 200000 + 10;
const int INF = 1 << 30;
const int D[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}};

struct Point {
	int x, y;
	Point(int x = 0, int y = 0): x(x), y(y) {}
	bool operator < (const Point &o) const {
		return x < o.x || x == o.x && y < o.y;
	}
	bool operator == (const Point &o) const {
		return x == o.x && y == o.y;
	}
};

std::map<Point, int> all_points;
int counter;

int get_id(const Point &p) {
	if (all_points.find(p) == all_points.end()) {
		return -1;
	}
	return all_points[p];
}

int add(const Point &p) {
	if (all_points.find(p) == all_points.end()) {
		all_points[p] = ++ counter;
	}
	return all_points[p];
}

std::set<Point> set;
Point points[N];
int n;

#define update_min(a, b) if ((a) > (b)) (a) = (b)
#define update_max(a, b) if ((a) < (b)) (a) = (b)

int ancestor[N];

int get_ancestor(int u) {
	return ancestor[u] == u ? u : ancestor[u] = get_ancestor(ancestor[u]);
}

void joint(int u, int v) {
	u = get_ancestor(u);
	v = get_ancestor(v);
	if (u != v) {
		ancestor[u] = v;
	}
}

int main() {
	freopen("perimeter.in", "r", stdin);
	freopen("perimeter.out", "w", stdout);
	int min_x = INF, min_y = INF;
	int max_x = -INF, max_y = -INF;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		int x, y;
		scanf("%d%d", &x, &y);
		update_min(min_x, x);
		update_min(min_y, y);
		update_max(max_x, x);
		update_max(max_y, y);
		points[i] = Point(x, y);
		set.insert(points[i]);
	}

	for (int i = 1; i <= n; ++ i) {
		int x = points[i].x;
		int y = points[i].y;
		for (int j = 0; j < 8; ++ j) {
			int dx = x + D[j][0];
			int dy = y + D[j][1];
			if (set.find(Point(dx, dy)) == set.end()) {
				add(Point(dx, dy));
			}
		}
	}


	for (int i = 0; i <= counter; ++ i) {
		ancestor[i] = i;
	}
	foreach(iter, all_points) {
		int x = (*iter).first.x;
		int y = (*iter).first.y;
		if (x <= min_x || x >= max_x || y <= min_y || y >= max_y) {
			joint(0, (*iter).second);
		}
		for (int i = 0; i < 4; ++ i) {
			int dx = x + D[i][0];
			int dy = y + D[i][1];
			int id = get_id(Point(dx, dy));
			if (id != -1) {
				joint((*iter).second, id);
			}
		}
	}

	/*
	foreach(iter, all_points) {
		Point p = (*iter).first;
		printf("%d: (%d %d) %d\n", (*iter).second, p.x, p.y, get_ancestor((*iter).second));
	}
	*/
	int answer = 0;
	for (int i = 1; i <= n; ++ i) {
		int x = points[i].x;
		int y = points[i].y;
		for (int j = 0; j < 4; ++ j) {
			int dx = x + D[j][0];
			int dy = y + D[j][1];
			int id = get_id(Point(dx, dy));
			if (id != -1 && get_ancestor(id) == get_ancestor(0)) {
				answer ++;
			}
		}
	}
	printf("%d\n", answer);
	return 0;
}
