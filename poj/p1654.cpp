// POJ 1654, Area
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int D[10][2] = {{0, 0}, {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {0, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

char buffer[1000005];

int main () {
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        scanf ("%s", buffer);
        int len = strlen (buffer);
        long long area = 0;
        int x1 = 0, y1 = 0;
        for (int i = 0; i < len - 1; ++ i) {
            int x2 = x1 + D[buffer[i] - '0'][0];
            int y2 = y1 + D[buffer[i] - '0'][1];
            area += (long long)x1 * y2 - (long long)x2 * y1;
            x1 = x2, y1 = y2;
        }
        if (area < 0) {
            area = -area;
        }
        if (area % 2) {
            printf ("%lld.5\n", area / 2);
        }
        else {
            printf ("%lld\n", area / 2);
        }
    }
    return 0;
}
