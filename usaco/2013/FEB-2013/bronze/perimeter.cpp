#include <cstdio>
#include <cstring>

const int N = 100 + 10;
const int D[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool empty[N][N], arrived[N][N];
int n;

bool in_range(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n;
}

void dfs(int x, int y) {
	arrived[x][y] = true;
	for (int i = 0; i < 4; ++ i) {
		int dx = x + D[i][0];
		int dy = y + D[i][1];
		if (in_range(dx, dy) && empty[dx][dy] && !arrived[dx][dy]) {
			dfs(dx, dy);
		}
	}
}

int main() {
	freopen("perimeter.in", "r", stdin);
	freopen("perimeter.out", "w", stdout);
	n = 100;
	for (int i = 0; i <= n + 1; ++ i) {
		for (int j = 0; j <= n + 1; ++ j) {
			empty[i][j] = true;
		}
	}
	int m;
	scanf("%d", &m);
	while (m --) {
		int x, y;
		scanf("%d%d", &x, &y);
		empty[x][y] = false;
	}
	for (int i = 1; i <= n; ++ i) {
		dfs(i, 0);
		dfs(i, n + 1);
		dfs(0, i);
		dfs(n + 1, i);
	}
	int answer = 0;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= n; ++ j) {
			if (!empty[i][j]) {
				for (int k = 0; k < 4; ++ k) {
					int dx = i + D[k][0];
					int dy = j + D[k][1];
					if (arrived[dx][dy]) {
						answer ++;
					}
				}
			}
		}
	}
	printf("%d\n", answer);
	return 0;
}
