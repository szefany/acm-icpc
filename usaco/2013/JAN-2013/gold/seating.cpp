#include <cstdio>
#include <vector>

const int N = 500000 + 10;
const int S = N << 2;

int value[S], topleft[S], topright[S], cover[S], width[S];

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

void update(int u) {
	topleft[u] = topleft[L(u)];
	if (topleft[L(u)] == width[L(u)]) {
		topleft[u] += topleft[R(u)];
	}
	topright[u] = topright[R(u)];
	if (topright[R(u)] == width[R(u)]) {
		topright[u] += topright[L(u)];
	}
	value[u] = std::max(value[L(u)], value[R(u)]);
	value[u] = std::max(value[u], topright[L(u)] + topleft[R(u)]);
}

void push_down(int u) {
	if (cover[u] == 1) {
		topleft[L(u)] = topright[L(u)] = value[L(u)] = 0;
		topleft[R(u)] = topright[R(u)] = value[R(u)] = 0;
		cover[L(u)] = cover[R(u)] = 1;
	} else if (cover[u] == -1) {
		topleft[L(u)] = topright[L(u)] = value[L(u)] = width[L(u)];
		topleft[R(u)] = topright[R(u)] = value[R(u)] = width[R(u)];
		cover[L(u)] = cover[R(u)] = -1;
	}
	cover[u] = 0;
}

void insert(int u, int l, int r, int a, int b) {
	if (b < l || a > r) {
		return;
	}
	if (a <= l && b >= r) {
		value[u] = topright[u] = topleft[u] = 0;
		cover[u] = 1;
		return;
	}
	push_down(u);
	int m = l + r >> 1;
	insert(L(u), l, m, a, b);
	insert(R(u), m + 1, r, a, b);
	update(u);
}

bool find(int u, int l, int r, int length) {
	if (l > r || value[u] < length) {
		return false;
	}
	push_down(u);
	int m = l + r >> 1;
	if (!find(L(u), l, m, length)) {
		if (topright[L(u)] + topleft[R(u)] >= length) {
			int x = topright[L(u)];
			int y = length - x;
			insert(L(u), l, m, m - x + 1, m);
			insert(R(u), m + 1, r, m + 1, m + y);
		} else {
			find(R(u), m + 1, r, length);
		}
	}
	update(u);
	return true;
}

void erase(int u, int l, int r, int a, int b) {
	if (b < l || a > r) {
		return;
	}
	if (a <= l && b >= r) {
		topleft[u] = topright[u] = value[u] = width[u];
		cover[u] = -1;
		return;
	}
	push_down(u);
	int m = l + r >> 1;
	erase(L(u), l, m, a, b);
	erase(R(u), m + 1, r, a, b);
	update(u);
}

void build(int u, int l, int r) {
	value[u] = topleft[u] = topright[u] = width[u] = r - l + 1;
	if (l < r) {
		int m = l + r >> 1;
		build(L(u), l, m);
		build(R(u), m + 1, r);
	}
}

int main() {
	freopen("seating.in", "r", stdin);
	freopen("seating.out", "w", stdout);
	int n, m, answer = 0;
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	while (m --) {
		char command[2];
		scanf("%s", command);
		if (*command == 'A') {
			int x;
			scanf("%d", &x);
			if (value[1] < x) {
				answer ++;
			} else {
				find(1, 1, n, x);
			}
		} else {
			int a, b;
			scanf("%d%d", &a, &b);
			erase(1, 1, n, a, b);
		}
	}
	printf("%d\n", answer);
	return 0;
}
