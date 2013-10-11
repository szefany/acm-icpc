#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <climits>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 400000 + 10;
const int INF = 1 << 30;

struct Data {
	int a, b, height, id;
	Data(int a = 0, int b = 0, int h = 0, int id = 0): a(a), b(b), height(h), id(id) {}
};
std::vector<Data> bricks, boards;

bool by_height(const Data &a, const Data &b) {
	return a.height < b.height;
}

std::vector<int> all_values;

int get_id(int x) {
	return std::lower_bound(all_values.begin(), all_values.end(), x) - all_values.begin() + 1;
}

int n, m;

const int S = N << 2;

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

int value[S];

void cover_down(int u) {
	if (value[u]) {
		value[L(u)] = value[R(u)] = value[u];
		value[u] = 0;
	}
}

void cover(int u, int l, int r, int a, int b, int v) {
	if (a >= r || b <= l) {
		return;
	}
	if (a <= l && b >= r) {
		value[u] = v;
		return;
	}
	cover_down(u);
	int m = l + r >> 1;
	cover(L(u), l, m, a, b, v);
	cover(R(u), m, r, a, b, v);
}

int belong[N];
long long answer[N];

void get_belongs(int u, int l, int r) {
	if (l + 1 == r) {
		belong[l] = value[u];
		return;
	}
	cover_down(u);
	int m = l + r >> 1;
	get_belongs(L(u), l, m);
	get_belongs(R(u), m, r);
}

void add_down(int u) {
	if (value[u]) {
		value[L(u)] += value[u];
		value[R(u)] += value[u];
		value[u] = 0;
	}
}

void add(int u, int l, int r, int a, int b) {
	if (a >= r || b <= l) {
		return;
	}
	if (a <= l && b >= r) {
		value[u] ++;
		return;
	}
	add_down(u);
	int m = l + r >> 1;
	add(L(u), l, m, a, b);
	add(R(u), m, r, a, b);
}

void get_answer(int u, int l, int r) {
	if (l + 1 == r) {
		answer[belong[l]] += (long long)value[u] * (all_values[r - 1] - all_values[l - 1]);
		return;
	}
	add_down(u);
	int m = l + r >> 1;
	get_answer(L(u), l, m);
	get_answer(R(u), m, r);
}

void initialise() {
	all_values.clear();
	boards.clear();
	bricks.clear();
	memset(answer, 0, sizeof(answer));
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		initialise();
		for (int i = 1; i <= n; ++ i) {
			int a, b;
			scanf("%d%d", &a, &b);
			bricks.push_back(Data(a, b, 0, i));
			all_values.push_back(a);
			all_values.push_back(b);
		}
		
		for (int i = 1; i <= m; ++ i) {
			int a, b, h;
			scanf("%d%d%d", &a, &b, &h);
			boards.push_back(Data(a, b, h, i));
			all_values.push_back(a);
			all_values.push_back(b);
		}
		std::sort(all_values.begin(), all_values.end());
		all_values.resize(unique(all_values.begin(), all_values.end()) - all_values.begin());
		int s = all_values.size();
		
		std::sort(boards.begin(), boards.end(), by_height);
		memset(value, 0, sizeof(value));
		
		foreach(iter, boards) {
			int a = (*iter).a;
			int b = (*iter).b;
			int id = (*iter).id;
			int new_a = get_id(a);
			int new_b = get_id(b);
			cover(1, 1, s, new_a, new_b, id);
		}
		get_belongs(1, 1, s);
		
		memset(value, 0, sizeof(value));
		foreach(iter, bricks) {
			int a = (*iter).a;
			int b = (*iter).b;
			int new_a = get_id(a);
			int new_b = get_id(b);
			add(1, 1, s, new_a, new_b);
		}
		
		get_answer(1, 1, s);
		for (int i = 1; i <= m; ++ i) {
			printf("%lld\n", answer[i]);
		}
		puts("");
	}
	return 0;
}
