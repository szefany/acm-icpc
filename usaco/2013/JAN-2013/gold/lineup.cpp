#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

std::vector<int> all_values;

void discrete(std::vector<int> &v) {
	std::sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
}

int new_value(std::vector<int> &v, int x) {
	return std::lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}

const int N = 100000 + 10;

int count[N];
struct cmp {
	bool operator () (int a, int b) const {
		return count[a] > count[b];
	}
};

std::set<int, cmp> set;
int a[N], next[N], n, m;

int main() {
	freopen("lineup.in", "r", stdin);
	freopen("lineup.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", a + i);
		all_values.push_back(a[i]);
	}
	discrete(all_values);
	for (int i = n; i >= 1; -- i) {
		a[i] = new_value(all_values, a[i]);
		next[i] = a[i] == a[i + 1] ? next[i + 1] : i;
	}

	int answer = 0;
	int current = 0;
	int bound = 0;
	for (int i = 1; i <= n; ++ i) {
		int x = a[i];
		if (count[x]) {
			set.erase(x);
		} else if (current < m + 1) {
			current ++;
		} else {
			while (1) {
				int y = a[bound + 1];
				set.erase(y);
				count[y] -= next[bound + 1] - bound;
				bound = next[bound + 1];
				if (count[y]) {
					set.insert(y);
				} else {
					break;
				}
			}
		}
		count[x] ++;
		set.insert(x);
		answer = std::max(answer, count[*set.begin()]);
	}
	printf("%d\n", answer);
	return 0;
}
