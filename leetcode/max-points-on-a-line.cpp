/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

class Solution {
public:
    long long det(Point& a, Point& b, Point& c) {
        long long x1 = b.x - a.x;
        long long y1 = b.y - a.y;
        long long x2 = c.x - a.x;
        long long y2 = c.y - a.y;
        return x1 * y2 - x2 * y1;
    }
    
    bool equal(const Point& a, const Point& b) {
        return a.x == b.x && a.y == b.y;
    }
    int maxPoints(vector<Point> &points) {
        int n = points.size();
        vector<int> weights(n);
        
        for (int i = 0; i < n; ++ i) {
            weights[i] = 1;
            for (int j = 0; j < n; ++ j) {
                if (i != j && equal(points[i], points[j])) {
                    weights[i] ++;
                }
            }
        }
        
        int answer = 0;
        for (int i = 0; i < n; ++ i) {
            answer = max(answer, weights[i]);
        }
        
        for (int from = 0; from < n; ++ from) {
            for (int to = from + 1; to < n; ++ to) {
                if (equal(points[from], points[to])) {
                    continue;
                }
                int count = 2;
                for (int i = 0; i < n; ++ i) {
                    if (i != from && i != to && det(points[from], points[to], points[i]) == 0) {
                        count ++;
                    }
                }
                answer = max(answer, count);
            }
        }
        return answer;
    }
};
