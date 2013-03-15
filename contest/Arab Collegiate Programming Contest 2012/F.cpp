#include <cstdio>
#include <iostream>

const int N = 13;
const int S = 1 << N;
const int T = 200;

long long dp[S][N][T];
int n, length;

struct Point {
    Point () {}
    Point (int x, int y): x (x), y (y) {}
    Point operator - (const Point other) const {
        return Point (x - other.x, y - other.y);
    }
    int x, y;
};

int get_id (int x, int y) {
    return x * 4 + y;
}

Point decode (int code) {
    return Point (code / 4, code % 4);
}

int abs (int x) {
    return x > 0 ? x : -x;
}

int get_dist (int start, int end) {
    Point a = decode (start), b = decode (end);
    return abs (a.x - b.x) + abs (a.y - b.y);
}

int det (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

int dot (Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

bool on_segment (Point p, Point a, Point b) {
    return det (p - a, p - b) == 0 && dot (p - a, p - b) <= 0;
}

bool check (int mask, int start, int end) {
    if (1 << end & mask) {
        return false;
    }
    Point a = decode (start), b = decode (end);
    for (int i = 0; i < 12; ++ i) {
        if (i != start && i != end && !(1 << i & mask)) {
            Point p = decode (i);
            if (on_segment (p, a, b)) {
                return false;
            }
        }
    }
    return true;
}

int main () {
    for (int i = 0; i < 12; ++ i) {
        dp[1 << i][i][0] = 1;
    }
    for (int mask = 0; mask < 1 << 12; ++ mask) {
        for (int i = 0; i < 12; ++ i) {
            if (1 << i & mask) {
                for (int next = 0; next < 12; ++ next) {
                    if (check (mask, i, next)) {
                        int dist = get_dist (i, next);
                        for (int length = dist; length < T; ++ length) {
                            dp[mask | 1 << next][next][length] += dp[mask][i][length - dist];
                        }
                    }
                }
            }
        }
    }
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        scanf ("%d%d", &length, &n);
        int total_mask = (1 << 12) - 1;
        for (int i = 0; i < n; ++ i) {
            int x, y;
            scanf ("%d%d", &x, &y);
            int id = get_id (x - 1, y - 1);
            total_mask ^= 1 << id; 
        }
        long long answer = 0;
        if (length < T) {
            for (int mask = total_mask; mask; mask = (mask - 1) & total_mask) {
                int number = __builtin_popcount (mask);
                if (number >= 2) {
                    for (int i = 0; i < 12; ++ i) {
                        if (1 << i & mask) {
                            answer += dp[mask][i][length];
                        }
                    }
                }
            }
        }
        if (answer == 0) {
            puts ("BAD MEMORY");
        } else {
            std::cout << answer << std::endl;
        }
    }
    return 0;
}
