#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> all_values;

void discrete(std::vector<int> &v) {
	std::sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
}

int find(std::vector<int> &v, int x) {
	return std::lower_bound(v.begin(), v.end(), x) - v.begin();
}

const int N = 200000 + 10;

int delta[N], left[N], right[N];
int count;

void insert(int a, int b, int id) {
	if (a > b) {
		std::swap(a, b);
	}
	left[id] = a;
	right[id] = b;
	all_values.push_back(a);
	all_values.push_back(b);
}

int main() {
	freopen("paint.in", "r", stdin);
	freopen("paint.out", "w", stdout);
	int n, m, start = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		int x;
		char buffer[2];
		scanf("%d%s", &x, buffer);
		int d = *buffer == 'R' ? 1 : -1;
		int end = start + x * d;
		insert(start, end, i);
		start = end;
	}
	discrete(all_values);
	for (int i = 1; i <= n; ++ i) {
		left[i] = find(all_values, left[i]);
		right[i] = find(all_values, right[i]);
		delta[left[i]] ++;
		delta[right[i]] --;
	}

	int answer = 0;
	int now = -1, cover = 0;
	for (int i = 0; i < all_values.size(); ++ i) {
		if (cover >= m) {
			answer += all_values[i] - now;
		}
		cover += delta[i];
		now = all_values[i];
	}
	printf("%d\n", answer);
	return 0;
}
