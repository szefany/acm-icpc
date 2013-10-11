#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 1000 + 10;
const int D[8][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

bool ghost[N][N];
char map[N][N];
int n, m;

bool in_range(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}

bool visit[N][N];

int queue[N * N][2];
int solve(int sx, int sy) {
	visit[sx][sy] = true;
	queue[0][0] = sx;
	queue[0][1] = sy;
	int result = 0;
	for (int head = 0, tail = 0; head <= tail; ++ head) {
		result ++;
		int x = queue[head][0];
		int y = queue[head][1];
		for (int i = 0; i < 8; ++ i) {
			int dx = x + D[i][0];
			int dy = y + D[i][1];
			if (in_range(dx, dy) && !visit[dx][dy] && map[dx][dy] == 'P') {
				tail ++;
				queue[tail][0] = dx;
				queue[tail][1] = dy;
				visit[dx][dy] = true;
			}
		}
	}
	return result;
}

void cover(int sx, int sy) {
	visit[sx][sy] = true;
	queue[0][0] = sx;
	queue[0][1] = sy;
	for (int head = 0, tail = 0; head <= tail; ++ head) {
		int x = queue[head][0];
		int y = queue[head][1];
		for (int i = 0; i < 4; ++ i) {
			int dx = x + D[i][0];
			int dy = y + D[i][1];
			if (in_range(dx, dy) && map[dx][dy] == '.' && !visit[dx][dy]) {
				visit[dx][dy] = true;
				tail ++;
				queue[tail][0] = dx;
				queue[tail][1] = dy;
			}
		}
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++ i) {
			scanf("%s", map[i] + 1);
		}
		memset(ghost, 0, sizeof(ghost));
		memset(visit, 0, sizeof(visit));
		for (int i = 1; i <= n; ++ i) {
			cover(i, 0);
			cover(i, m + 1);
		}
		for (int i = 1; i <= m; ++ i) {
			cover(0, i);
			cover(n + 1, i);
		}
		
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= m; ++ j) {
				if (i == 1 || i == n || j == 1 || j == m) {
					continue;
				}
				if (map[i][j] == 'P') {
					bool flag = false;
					for (int k = 0; k < 4; ++ k) {
						int dx = i + D[k][0];
						int dy = j + D[k][1];
						if (in_range(dx, dy) && visit[dx][dy]) {
							flag = true;
							break;
						}
					}
					if (!flag) {
						ghost[i][j] = true;
					}
				}
			}
		}
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= m; ++ j) {
				if (ghost[i][j]) {
					map[i][j] = 'G';
				}
			}
		}
		memset(visit, 0, sizeof(visit));
		int answer = 0;
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= m; ++ j) {
				if (!visit[i][j] && map[i][j] == 'P') {
					answer = std::max(answer, solve(i, j));
				}
			}
		}
		printf("%d\n", answer);
	}
	return 0;
}
