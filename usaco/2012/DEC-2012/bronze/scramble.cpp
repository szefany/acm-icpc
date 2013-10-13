#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 50000 + 10;

char string[N][30], buffer[N];
int lower[N], upper[N], length[N], order[N];
int n;

bool cmp(int a, int b) {
	return strcmp(string[a], string[b]) < 0;
}

int find(int id) {
	int l = 1, r = n;
	int found = -1;
	while (l < r) {
		int m = l + r + 1 >> 1;
		if (strcmp(string[order[m]], buffer) < 0) {
			l = found = m;
		} else {
			r = m - 1;
		}
	}
	if (strcmp(string[order[l]], buffer) < 0) {
		found = l;
	}
	if (found == -1) {
		return 1;
	}
	if (strcmp(string[id], buffer) < 0) {
		found --;
	}
	return found + 1;
}

int main() {
	freopen("scramble.in", "r", stdin);
	freopen("scramble.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		scanf("%s", string[i]);
		length[i] = strlen(string[i]);
	}

	for (int i = 1; i <= n; ++ i) {
		std::sort(string[i], string[i] + length[i]);
		order[i] = i;
	}
	std::sort(order + 1, order + n + 1, cmp);

	for (int i = 1; i <= n; ++ i) {
		strcpy(buffer, string[i]);
		std::reverse(buffer, buffer + length[i]);
		upper[i] = find(i);
	}

	for (int i = 1; i <= n; ++ i) {
		std::reverse(string[i], string[i] + length[i]);
		order[i] = i;
	}
	std::sort(order + 1, order + n + 1, cmp);

	for (int i = 1; i <= n; ++ i) {
		strcpy(buffer, string[i]);
		std::reverse(buffer, buffer + length[i]);
		lower[i] = find(i);
	}

	for (int i = 1; i <= n; ++ i) {
		printf("%d %d\n", lower[i], upper[i]);
	}
	return 0;
}
