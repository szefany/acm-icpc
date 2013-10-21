#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100000 + 10;

struct Event {
	int a, b, pos, flag;
	Event(int a = 0, int b = 0, int pos = 0, int flag = 0): a(a), b(b), pos(pos), flag(flag) {}
	bool operator < (const Event &e) const {
		return pos < e.pos;
	}
} events[N];

int n;

const int S = 1000000 + 10;

int sum[S];

int lowbit(int x) {
	return x & -x;
}

void add(int x, int v) {
	for (; x < S; x += lowbit(x)) {
		sum[x] += v;
	}
}

int get(int x) {
	if (x < 0) {
		return 0;
	}
	int result = 0;
	for (; x; x -= lowbit(x)) {
		result += sum[x];
	}
	return result;
}

int main() {
	freopen("painting.in", "r", stdin);
	freopen("painting.out", "w", stdout);
	scanf("%d", &n);
	int counter = 0;
	for (int i = 1; i <= n; ++ i) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		x1 ++, y1 ++, x2 ++, y2 ++;
		events[counter ++] = Event(y1, y2, x1, 1);
		events[counter ++] = Event(y1, y2, x2, -1);
	}
	std::sort(events, events + counter);

	int answer = 0;
	for (int i = 0; i < counter; ++ i) {
		int a = events[i].a;
		int b = events[i].b;
		if (events[i].flag > 0) {
			answer += get(a) == 0;
		}
		add(a, events[i].flag);
		add(b + 1, -events[i].flag);
	}
	printf("%d\n", answer);
	return 0;
}
