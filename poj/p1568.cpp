#include <cstdio>
#include <cstring>

const int N = 4;
const int S = 600000;

int hash[2][S];
char map[10][10], board[10][10];

bool full_board() {
    for (int i = 0; i < N; ++ i) {
        for (int j = 0; j < N; ++ j) {
            if (board[i][j] == '.') {
                return false;
            }
        }
    }
    return true;
}

int trans(char token) {
    int result;
    if (token == '.') {
        result = 0;
    } else if (token == 'x') {
        result = 1;
    } else {
        result = 2;
    }
    return result;
}

int get_hash() {
    int result = 0;
    for (int i = 0; i < N; ++ i) {
        for (int j = 0; j < N; ++ j) {
            if (map[i][j] == '.') {
                result = result * 3 + trans(board[i][j]);
            }
        }
    }
    return result;
}

bool check_win(char token) {
    for (int i = 0; i < N; ++ i) {
        bool row = true;
        for (int j = 0; j < N; ++ j) {
            row &= board[i][j] == token;
        }
        if (row) {
            return true;
        }
    }
    for (int i = 0; i < N; ++ i) {
        bool column = true;
        for (int j = 0; j < N; ++ j) {
            column &= board[j][i] == token;
        }
        if (column) {
            return true;
        }
    }
    bool diag = true;
    for (int i = 0; i < N; ++ i) {
        diag &= board[i][i] == token;
    }
    if (diag) {
        return true;
    }
    diag = true;
    for (int i = 0; i < N; ++ i) {
        diag &= board[i][3 - i] == token;
    }
    return diag;
}

int solve(int step) {
    char token = step == 0 ? 'x' : 'o';
    int mask = get_hash();
    if (check_win(token)) {
        return hash[step][mask] = 1;
    } else if (check_win('x' + 'o' - token)) {
        return hash[step][mask] = 2;
    } else if (full_board()) {
        return hash[step][mask] = 3;
    }
    if (hash[step][mask]) {
        return hash[step][mask];
    }
    bool all_one = true;
    for (int i = 0; i < N; ++ i) {
        for (int j = 0; j < N; ++ j) {
            if (board[i][j] == '.') {
                board[i][j] = token;
                int flag = solve(step ^ 1);
                board[i][j] = '.';
                if (flag == 2) {
                    return hash[step][mask] = 1;
                }
                all_one &= flag == 1;
            }
        }
    }
    return hash[step][mask] = all_one ? 2 : 3;
}

int main() {
    char buffer[2];
    while (scanf("%s", buffer) && *buffer != '$') {
        memset(hash, 0, sizeof(hash));
        for (int i = 0; i < N; ++ i) {
            scanf("%s", map[i]);
            strcpy(board[i], map[i]);
        }
        int x = -1, y = -1;
        for (int i = 0; i < N && x < 0; ++ i) {
            for (int j = 0; j < N && x < 0; ++ j) {
                if (map[i][j] == '.') {
                    board[i][j] = 'x';
                    if (solve(1) == 2) {
                        x = i;
                        y = j;
                        break;
                    }
                    board[i][j] = '.';
                }
            }
        }
        if (x == -1) {
            puts("#####");
        } else {
            printf("(%d,%d)\n", x, y);
        }
    }
    return 0;
}
