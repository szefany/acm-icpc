#include <cstdio>
#include <cstring>

const int N = 60;
const int M = 16;
const int S = 1 << M;
const int D[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

char map[N][N];
int belongs[N][N];
int dp[S][M], weight[M][M];
int n, m, total;

bool in_range(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= m;
}

void get_belongs(int x, int y) {
	belongs[x][y] = total;
	for (int i = 0; i < 4; ++ i) {
		int dx = x + D[i][0];
		int dy = y + D[i][1];
		if (in_range(dx, dy) && map[dx][dy] == 'X' && belongs[dx][dy] == -1) {
			get_belongs(dx, dy);
		}
	}
}

#define update_min(a, b) if ((a) > (b)) (a) = (b)

const int Q = N * N;

int queue[Q + Q][2];
int dist[N][N];
bool in_queue[N][N];

void get_weight(int sx, int sy) {
	memset(dist, 1, sizeof(dist));
	memset(in_queue, 0, sizeof(in_queue));
	dist[sx][sy] = 0;
	queue[1][0] = sx;
	queue[1][1] = sy;
	for (int head = 0, tail = 1; head != tail; ) {
		head = head % Q + 1;
		int x = queue[head][0];
		int y = queue[head][1];
		in_queue[x][y] = false;
		for (int i = 0; i < 4; ++ i) {
			int dx = x + D[i][0];
			int dy = y + D[i][1];
			if (in_range(dx, dy) && map[dx][dy] != '.') {
				int temp = dist[x][y] + (map[dx][dy] == 'S');
				if (temp < dist[dx][dy]) {
					dist[dx][dy] = temp;
					if (!in_queue[dx][dy]) {
						in_queue[dx][dy] = true;
						tail = tail % Q + 1;
						queue[tail][0] = dx;
						queue[tail][1] = dy;
					}
				}
			}
		}
	}
	int id = belongs[sx][sy];
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			if (map[i][j] == 'X' && belongs[i][j] != id) {
				update_min(weight[id][belongs[i][j]], dist[i][j]);
			}
		}
	}
}

int main() {
	freopen("island.in", "r", stdin);
	freopen("island.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		scanf("%s", map[i] + 1);
	}
	memset(belongs, -1, sizeof(belongs));
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			if (map[i][j] == 'X' && belongs[i][j] == -1) {
				get_belongs(i, j);
				total ++;
			}
		}
	}
	memset(weight, 1, sizeof(weight));
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			if (map[i][j] == 'X') {
				get_weight(i, j);
			}
		}
	}
	memset(dp, 1, sizeof(dp));
	for (int i = 0; i < total; ++ i) {
		dp[1 << i][i] = 0;
	}
	for (int mask = 1; mask < 1 << total; ++ mask) {
		for (int i = 0; i < total; ++ i) {
			if (!(1 << i & mask)) {
				continue;
			}
			for (int j = 0; j < total; ++ j) {
				if (!(1 << j & mask)) {
					update_min(dp[mask | 1 << j][j], dp[mask][i] + weight[i][j]);
				}
			}
		}
	}
	int answer = 1 << 30;
	for (int i = 0; i < total; ++ i) {
		update_min(answer, dp[(1 << total) - 1][i]);
	}
	printf("%d\n", answer);
	return 0;
}
