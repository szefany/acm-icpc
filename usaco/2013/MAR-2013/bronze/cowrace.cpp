#include <cstdio>
#include <cstring>

const int N = 1000 + 10;

int speed[2][N], during[2][N];
int n, m;

int main() {
	freopen("cowrace.in", "r", stdin);
	freopen("cowrace.out", "w", stdout);
	scanf("%d%d", &n, &m);
	int total = 0;
	for (int i = 1; i <= n; ++ i) {
		scanf("%d%d", &speed[0][i], &during[0][i]);
		total += during[0][i];
	}
	for (int i = 1; i <= m; ++ i) {
		scanf("%d%d", &speed[1][i], &during[1][i]);
	}

	int answer = 0;
	int now[2] = {0, 0};
	int lead = -1;
	for (int i = 1, a = 1, b = 1; i <= total; ++ i) {
		if (during[0][a] == 0) {
			a ++;
		}
		if (during[1][b] == 0) {
			b ++;
		}
		during[0][a] --;
		during[1][b] --;
		now[0] += speed[0][a];
		now[1] += speed[1][b];
		for (int j = 0; j < 2; ++ j) {
			if (now[j] > now[j ^ 1] && j != lead) {
				if (lead != -1) {
					answer ++;
				}
				lead = j;
				break;
			}
		}
	}
	printf("%d\n", answer);
	return 0;
}
