#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
#include <cmath>
#include <cassert>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 200000 + 10;

struct Point {
	int x, y;
	Point(int x = 0, int y = 0): x(x), y(y) {}
	Point operator - (const Point &p) const {
		return Point(x - p.x, y - p.y);
	}
	bool operator < (const Point &p) const {
		return x < p.x || x == p.x && y < p.y;
	}
	bool operator == (const Point &p) const {
		return x == p.x && y == p.y;
	}
};

struct Event {
	Point p;
	int flag, id;
	Event(int x = 0, int y = 0, int flag = 0, int id = 0): p(Point(x, y)), flag(flag), id(id) {}
	bool operator < (const Event &e) const {
		return p < e.p || p == e.p && flag < 0;
	}
} events[N];

long long det(const Point &a, const Point &b) {
	return (long long)a.x * b.y - (long long)b.x * a.y;
}

struct Segment {
	Point a, b;
	int id;
	Segment() {}
	Segment(const Point &a, const Point &b, int id): a(a), b(b), id(id) {}
	bool operator < (const Segment &s) const {
		bool rev = false;
		Segment s1 = *this;
		Segment s2 = s;
		if (s2.a < s1.a) {
			rev = true;
			std::swap(s1, s2);
		}
		bool flag = det(s2.a - s1.a, s1.b - s1.a) < 0;
		flag ^= rev;
		return flag;
	}
} segments[N];

int n;

int main() {
	freopen("hillwalk.in", "r", stdin);
	freopen("hillwalk.out", "w", stdout);
	scanf("%d", &n);
	int counter = 0;
	for (int i = 0; i < n; ++ i) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		events[counter ++] = Event(x1, y1, 1, i);
		events[counter ++] = Event(x2, y2, -1, i);
		segments[i] = Segment(Point(x1, y1), Point(x2, y2), i);
	}

	std::sort(events, events + counter);
	std::multiset<Segment> set;
	int answer = 0;
	int now = 0;
	int prefix = 0;
	while (1) {
		answer ++;
		int x = segments[now].b.x;
		int y = segments[now].b.y;
		while (prefix < counter && events[prefix].p.x <= x) {
			int id = events[prefix].id;
			if (events[prefix].flag == 1) {
				set.insert(segments[id]);
			} else if (id != now) {
				if (set.find(segments[id]) == set.end()) {
					printf("%d\n", id);
				};
				set.erase(set.find(segments[id]));
			}
			prefix ++;
		}
		typeof(set.begin()) iter = set.lower_bound(segments[now]);
		if (iter == set.begin()) {
			break;
		}
		iter --;
		int next = (*iter).id;
		set.erase(++ iter);
		now = next;
	}
	printf("%d\n", answer);
	return 0;
}
