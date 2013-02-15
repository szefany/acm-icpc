// POJ 3208, Apocalypse Someday
#include <iostream>
#include <cstdio>
#include <cstring>

const int N = 20;
const long long MAX = 10000000000000LL;

long long number[N][4][2][2];
int digit[N];

long long solve (int pivot, bool less, bool first, bool exist, int sixes) {
    if (pivot == 0) {
        return exist;
    }
    if (less && number[pivot][sixes][exist][first] != -1) {
        return number[pivot][sixes][exist][first];
    }
    long long result = 0;
    int limit = less ? 9 : digit[pivot];
    for (int i = 0; i <= limit; ++ i) {
        if (first && i == 0) {
            continue;
        }
        int new_sixes = i == 6 ? std::min (3, sixes + 1) : 0;
        result += solve (pivot - 1, less || i < limit, false, exist || new_sixes == 3, new_sixes);
    }
    if (less) {
        number[pivot][sixes][exist][first] = result;
    }
    return result;
}

long long count (long long x) {
    memset (digit, 0, sizeof (x));
    int length = 0;
    while (x) {
        digit[++ length] = x % 10;
        x /= 10;
    }
    long long result = 0;
    for (int l = 1; l <= length; ++ l) {
        result += solve (l, l < length, true, false, 0);
    }
    return result;
}

int main () {
    memset (number, -1, sizeof (number));
    int test_count;
    scanf ("%d", &test_count);
    while (test_count --) {
        int nth;
        scanf ("%d", &nth);
        long long l = 0, r = MAX;
        while (l < r) {
            long long mid = l + r >> 1;
            if (count (mid) >= nth) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        std::cout << l << std::endl;
    }
    return 0;
}
