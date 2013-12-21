class Solution {
public:
    void solve(vector<vector<char>> &board) {
        if (!initialise(board)) {
            return;
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                if (board[i][j] == 'X') {
                    continue;
                }
                int id = getID(i, j);
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                    on_edge[getAncestor(id)] = true;
                }
                for (int d = 0; d < 4; ++ d) {
                    int x = i + DELTA[d][0];
                    int y = j + DELTA[d][1];
                    if (inRange(x, y) && board[x][y] == 'O') {
                        joint(getID(x, y), id);
                    }
                }
            }
        }
        
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                if (board[i][j] == 'O') {
                    int id = getID(i, j);
                    if (!on_edge[getAncestor(id)]) {
                        board[i][j] = 'X';
                    }
                }
            }    
        }
    }
    
private:
    const int DELTA[4][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}    
    };
    int n, m;
    int *ancestor;
    bool *on_edge;
    
    int getAncestor(int u) {
        return ancestor[u] == u ? u : ancestor[u] = getAncestor(ancestor[u]);
    }
    void joint(int u, int v) {
        u = getAncestor(u);
        v = getAncestor(v);
        if (u != v) {
            ancestor[u] = v;
            on_edge[v] |= on_edge[u];
        }
    }
    
    bool inRange(int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < m;
    }
    int getID(int x, int y) {
        return x * m + y;
    }
    
    bool initialise(vector<vector<char> >& board) {
        n = board.size();
        if (n == 0) {
            return false;
        }
        m = board[0].size();
        if (m == 0) {
            return false;
        }
        
        on_edge = new bool [n * m];
        ancestor = new int [n * m];
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                int id = getID(i, j);
                on_edge[id] = false;
                ancestor[id] = id;
            }
        }
        return true;
    }
};
