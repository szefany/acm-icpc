#include <cstdio>

const int N = 2000 + 10;

int ancestor[N];

int get_ancestor(int u) {
	return u == ancestor[u] ? u : ancestor[u] = get_ancestor(ancestor[u]);
}

void joint(int u, int v) {
	u = get_ancestor(u);
	v = get_ancestor(v);
	if (u != v) {
		ancestor[u] = v;
	}
}

int n, m;

int main() {
	freopen("truth.in", "r", stdin);
	freopen("truth.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n + n; ++ i) {
		ancestor[i] = i;
	}
	int count = 1;
	while (count <= m) {
		int a, b;
		char buffer[2];
		scanf("%d%d%s", &a, &b, buffer);
		if (*buffer == 'T') {
			joint(a, b);
			joint(a + n, b + n);
		} else {
			joint(a, b + n);
			joint(a + n, b);
		}
		bool flag = true;
		for (int i = 1; i <= n && flag; ++ i) {
			flag &= get_ancestor(i) != get_ancestor(i + n);
		}
		if (!flag) {
			break;
		}
		count ++;
	}
	printf("%d\n", count - 1);
	return 0;
}
