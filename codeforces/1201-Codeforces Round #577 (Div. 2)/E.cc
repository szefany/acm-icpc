#include <bits/stdc++.h>

const int N = 1000 + 10;
const int D[8][2] = {
  {-2, 1}, {-2, -1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1},
};

int d_white[N][N], d_black[N][N];
int n, m;
int enemy_x, enemy_y;

bool in_board(int x, int y) {
  return 1 <= x && x <= n && 1 <= y && y <= m;
}

void get_dist(int x, int y, int dist[N][N]) {
  for (int i = 1; i <= n; ++ i) {
    for (int j = 1; j <= m; ++ j) {
      dist[i][j] = 1 << 20;
    }
  }
  dist[x][y] = 0;
  std::queue<std::pair<int, int>> queue;
  queue.push(std::make_pair(x, y));
  while (!queue.empty()) {
    int x = queue.front().first;
    int y = queue.front().second;
    queue.pop();
    for (int i = 0; i < 8; ++ i) {
      int nx = x + D[i][0];
      int ny = y + D[i][1];
      if (in_board(nx, ny) && dist[x][y] + 1 < dist[nx][ny]) {
        dist[nx][ny] = dist[x][y] + 1;
        queue.push(std::make_pair(nx, ny));
      }
    }
  }
}

void go(int x, int y, int dist[N][N]) {
  while (1) {
    if (dist[x][y] == 0) {
      break;
    }
    for (int i = 0; i < 8; ++ i) {
      int nx = x + D[i][0];
      int ny = y + D[i][1];
      if (nx == enemy_x && ny == enemy_y) {
        std::cout << nx << " " << ny << std::endl;
        return;
      }
    }

    for (int i = 0; i < 8; ++ i) {
      int nx = x + D[i][0];
      int ny = y + D[i][1];
      if (in_board(nx, ny) && dist[nx][ny] == dist[x][y] - 1) {
        std::cout << nx << " " << ny << std::endl;
        x = nx;
        y = ny;
        break;
      }
    }
    if (dist[x][y] == 0) {
      break;
    }
    std::cin >> enemy_x >> enemy_y;
  }
}

int main() {
  std::cin >> n >> m;
  get_dist(n / 2, m / 2, d_white);
  get_dist(n / 2 + 1, m / 2, d_black);

  int x1, y1, x2, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;

  int white_1 = d_white[x1][y1];  // white -> white_goal
  int white_2 = d_black[x1][y1];  // white -> black_goal
  int black_1 = d_black[x2][y2];  // black -> black_goal
  int black_2 = d_white[x2][y2];  // black -> white_goal

  if ((x1 + y1) % 2 != (x2 + y2) % 2) {
    // White captures black.
    if (white_1 <= black_1) {
      std::cout << "WHITE" << std::endl;
      go(x1, y1, d_white);
    } else if (white_2 <= black_1 + 1) {
      std::cout << "WHITE" << std::endl;
      go(x1, y1, d_black);            // (x1, y1) -> black_goal
      go(n / 2 + 1, m / 2, d_white);  // black_goal -> white_goal
    } else {
      std::cout << "BLACK" << std::endl;
      std::cin >> enemy_x >> enemy_y;
      go(x2, y2, d_black);
    }
  } else {
    // Black captures white.
    if (black_1 < white_1) {
      std::cout << "BLACK" << std::endl;
      std::cin >> enemy_x >> enemy_y;
      go(x2, y2, d_black);
    } else if (black_2 <= white_1) {
      std::cout << "BLACK" << std::endl;
      std::cin >> enemy_x >> enemy_y;
      go(x2, y2, d_white);          // (x2, y2) -> white_goal
      go(n / 2, m / 2, d_black);    // white_goal -> black_goal
    } else {
      std::cout << "WHITE" << std::endl;
      go(x1, y1, d_white);
    }
  }
  return 0;
}
