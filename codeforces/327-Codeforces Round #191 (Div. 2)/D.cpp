#include <cstdio>
#include <cstring>
#include <set>
#include <vector>

const int N = 600;
const int D[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

bool visit[N][N], block[N][N];
int n, m;

struct data {
    int x, y;
    char type;
    data(int x = 0, int y = 0, char type = 0): x(x), y(y), type(type) {}
};

std::vector<data> answer;

void dfs(int x, int y, int fx, int fy) {
    visit[x][y] = true;
    answer.push_back(data(x, y, 'B'));
    for (int i = 0; i < 4; ++ i) {
        int dx = x + D[i][0];
        int dy = y + D[i][1];
        if (dx >= 1 && dx <= n && dy >= 1 && dy <= m && !block[dx][dy] && !visit[dx][dy]) {
            dfs(dx, dy, fx, fy);
        }
    }
    if (x != fx || y != fy) {
        answer.push_back(data(x, y, 'D'));
        answer.push_back(data(x, y, 'R'));
    }
}

int main() {
    scanf("%d%d", &n, &m);
    char buffer[N];
    for (int i = 1; i <= n; ++ i) {
        scanf("%s", buffer + 1);
        for (int j = 1; j <= m; ++ j) {
            if (buffer[j] == '#') {
                block[i][j] = true;
            }
        }
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            if (!visit[i][j] && !block[i][j]) {
                dfs(i, j, i, j);
            }
        }
    }
    printf("%d\n", (int)answer.size());
    for (int i = 0; i < answer.size(); ++ i) {
        printf("%c %d %d\n", answer[i].type, answer[i].x, answer[i].y);
    }
    return 0;
}
