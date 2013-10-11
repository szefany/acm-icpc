#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>

typedef double Double;

const int N = 1000 + 10;

char map[N][N], buffer[N];
Double prob[N][N][3]; // left, middle, right

int main() {
	int test = 0;
	while (gets(buffer + 1)) {
		int n = 1;
		int m = strlen(buffer + 1);
		if (m == 0) {
			break;
		}
		memcpy(map[n], buffer, sizeof(buffer));
		while (gets(buffer + 1)) {
			if (strlen(buffer + 1) == 0) {
				break;
			}
			n ++;
			memcpy(map[n], buffer, sizeof(buffer));
		}
		// printf("#%d %d %d\n", ++ test, n, m);
				
		memset(prob, 0, sizeof(prob));
		for (int i = 0; i <= m + 1; ++ i) {
			for (int j = 0; j < 3; ++ j) {
				prob[n + 1][i][j] = 1;
			}
		}
		for (int i = n; i >= 1; -- i) {
			for (int j = 0; j < 3; ++ j) {
				prob[i][0][j] = 1;
				prob[i][m + 1][j] = 1;
			}
			
			for (int j = 1; j <= m; ++ j) {
				if (map[i][j] == '.') {
					if (map[i + 1][j] == '|') {
						prob[i][j][0] = prob[i + 1][j][1];
					} else if (map[i + 1][j] == '\\') {
						prob[i][j][0] = prob[i + 1][j][2];
					} else if (map[i + 1][j] == '/') {
						prob[i][j][0] = prob[i + 1][j][0];
					} else {
						prob[i][j][0] = prob[i + 1][j][0];
					}
				} else if (map[i][j] == '|' || map[i][j] == '\\') {
					prob[i][j][0] = 0;
				} else {
					prob[i][j][0] = prob[i][j - 1][0];
				}
			}
			for (int j = m; j >= 1; -- j) {
				if (map[i][j] == '.') {
					if (map[i + 1][j] == '|') {
						prob[i][j][2] = prob[i + 1][j][1];
					} else if (map[i + 1][j] == '\\') {
						prob[i][j][2] = prob[i + 1][j][2];
					} else if (map[i + 1][j] == '/') {
						prob[i][j][2] = prob[i + 1][j][0];
					} else {
						prob[i][j][2] = prob[i + 1][j][2];
					}
				} else if (map[i][j] == '|' || map[i][j] == '/') {
					prob[i][j][2] = 0;
				} else {
					prob[i][j][2] = prob[i][j + 1][2];
				}
			}
			for (int j = 1; j <= m; ++ j) {
				if (map[i][j] == '.') {
					prob[i][j][1] = prob[i + 1][j][1];
				} else if (map[i][j] == '/') {	
					prob[i][j][1] = prob[i][j - 1][0];
				} else if (map[i][j] == '\\') {
					prob[i][j][1] = prob[i][j + 1][2];
				} else if (map[i][j] == '|') {
					prob[i][j][1] = 0.5 * (prob[i][j - 1][0] + prob[i][j + 1][2]);
				} else {
					prob[i][j][1] = 0;
				}
			}
		}
		Double answer = 0;
		
		for (int i = 1; i <= m; ++ i) {
			answer += prob[1][i][1];
		}
		
		std::cout << std::setprecision(2) << std::fixed;
		std::cout << answer / m * 100 << '\n';
	}
	return 0;
}
