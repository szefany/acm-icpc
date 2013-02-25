#include <cstdio>
#include <vector>
#include <algorithm>

int main () {
    int a, b;
    std::vector <int> numbers;
    for (int i = 0; i < 4; ++ i) {
        int x;
        scanf ("%d", &x);
        numbers.push_back (x);
    }
    scanf ("%d%d", &a, &b);
    std::sort (numbers.begin(), numbers.end());
    int answer = std::min (b - a + 1, numbers[0] - a);
    printf ("%d\n", std::max (answer, 0));
    return 0;
}
