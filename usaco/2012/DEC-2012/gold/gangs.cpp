#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

const int N = 100 + 10;

int a[N], n, sum;

using std::pair;
using std::make_pair;
typedef pair<int, int> Pair;

int buffer[N];
int solve(int field, int id) {
	memcpy(buffer, a, sizeof(a));
	std::priority_queue<Pair> heap_1;
	for (int i = 2; i <= n; ++ i) {
		if (buffer[i] && i != id) {
			heap_1.push(make_pair(buffer[i], i));
		}
	}
	while (!heap_1.empty() && field > 0) {
		Pair p = heap_1.top();
		heap_1.pop();
		buffer[p.second] --;
		if (p.first > 1) {
			heap_1.push(make_pair(p.first - 1, p.second));
		}
		field --;
	}
	if (field > 0 || field >= buffer[1]) {
		return -1;
	}
	buffer[1] -= field;

	std::priority_queue<int> heap;
	for (int i = 2; i <= n; ++ i) {
		if (buffer[i]) {
			heap.push(buffer[i]);
		}
	}
	while (heap.size() > 1) {
		int u = heap.top();
		heap.pop();
		int v = heap.top();
		heap.pop();
		if (u > 1) {
			heap.push(u - 1);
		}
		if (v > 1) {
			heap.push(v - 1);
		}
	}
	int other = heap.empty() ? 0 : heap.top();
	return buffer[1] - other;
}

int main() {
	freopen("gangs.in", "r", stdin);
	freopen("gangs.out", "w", stdout);
	scanf("%d%d", &sum, &n);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", a + i);
	}
	int remain = solve(0, -1);
	if (remain <= 0) {
		puts("NO");
	} else {
		puts("YES");
		printf("%d\n", remain);
		int amount = 0;
		int id = -1;
		while (sum > remain) {
			bool flag = false;
			for (int i = 1; i <= n && !flag; ++ i) {
				if (a[i] == 0) {
					continue;
				}
				int m_id = id;
				int m_amount = amount;
				a[i] --;
				if (i == id || id == -1) {
					amount ++;
					id = i;
				} else {
					amount --;
				}
				if (amount == 0) {
					id = -1;
				}
				if (solve(amount, id) == remain) {
					printf("%d\n", i);
					flag = true;
					break;
				}
				a[i] ++;
				amount = m_amount;
				id = m_id;
			}
			sum --;
		}
		while (a[1]) {
			printf("%d\n", 1);
			a[1] --;
		}
	}
	return 0;
}
