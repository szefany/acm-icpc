#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 40;
const int Q = 10000;
const int D[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

char map[N][N];
bool visit[N][N];
int dist[N][N], queue[Q][2];
int n, a, b;

int solve(int sx, int sy) {
	memset(visit, 0, sizeof(visit));
	memset(dist, 127, sizeof(dist));
	queue[1][0] = sx;
	queue[1][1] = sy;
	dist[sx][sy] = 0;
	for (int head = 0, tail = 1; head != tail; ) {
		head = head % Q + 1;
		int x = queue[head][0];
		int y = queue[head][1];
		visit[x][y] = false;
		for (int i = 0; i < 4; ++ i) {
			int dx = x + D[i][0];
			int dy = y + D[i][1];
			if (dx >= 1 && dx <= n && dy >= 1 && dy <= n) {
				int temp = dist[x][y] + (map[dx][dy] == map[x][y] ? a : b);
				if (temp < dist[dx][dy]) {
					dist[dx][dy] = temp;
					if (!visit[dx][dy]) {
						visit[dx][dy] = true;
						tail = tail % Q + 1;
						queue[tail][0] = dx;
						queue[tail][1] = dy;
					}
				}
			}
		}
	}
	int result = 0;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= n; ++ j) {
			result = std::max(result, dist[i][j]);
		}
	}
	return result;
}

int main() {
	freopen("distant.in", "r", stdin);
	freopen("distant.out", "w", stdout);
	scanf("%d%d%d", &n, &a, &b);
	for (int i = 1; i <= n; ++ i) {
		scanf("%s", map[i] + 1);
	}
	int answer = 0;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= n; ++ j) {
			answer = std::max(answer, solve(i, j));
		}
	}
	printf("%d\n", answer);
	return 0;
}
