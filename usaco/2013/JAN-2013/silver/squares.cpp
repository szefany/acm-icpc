#include <cstdio>
#include <cstring>
#include <set>
#include <iostream>
#include <algorithm>
#include <vector>

const int N = 50000 + 10;

struct Point {
	int x, y;
	Point(int x = 0, int y = 0): x(x), y(y) {}
	bool operator < (const Point &o) const {
		return x < o.x;
	}
	void input() {
		scanf("%d%d", &x, &y);
	}
} points[N];

struct by_y {
	bool operator () (const Point &a, const Point &b) const {
		return a.y < b.y || a.y == b.y && a.x < b.x;
	}
};

std::multiset<Point, by_y> set;
int queue[N];
int n, m;

Point a, b;
bool found;

int abs(int x) {
	return x > 0 ? x : -x;
}

void judge(const Point &p, const Point &q) {
	if (abs(p.y - q.y) < m) {
		if (found) {
			puts("-1");
			exit(0);
		}
		found = true;
		a = p;
		b = q;
	}
}

int main() {
	freopen("squares.in", "r", stdin);
	freopen("squares.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		points[i].input();
	}
	std::sort(points + 1, points + n + 1);

	int head = 0, tail = 0;
	for (int i = 1; i <= n; ++ i) {
		while (head < tail) {
			int u = queue[head];
			if (points[i].x - points[u].x >= m) {
				set.erase(set.find(points[u]));
				head ++;
			} else {
				break;
			}
		}
		if (!set.empty()) {
			__typeof(set.begin()) iter = set.lower_bound(points[i]);
			if (iter != set.end()) {
				judge(points[i], *iter);
			}
			if (iter != set.begin()) {
				iter --;
				judge(points[i], *iter);
			}
		}
		queue[tail ++] = i;
		set.insert(points[i]);
	}
	if (!found) {
		puts("0");
	} else {
		int dx = abs(a.x - b.x);
		int dy = abs(a.y - b.y);
		long long answer = ((long long)m - dx) * (m - dy);
		std::cout << answer << std::endl;
	}
	return 0;
}
