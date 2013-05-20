#include <cstdio>
#include <map>

const int N = 100000 + 1;

int a[N], temp[N], n;

std::map<int, int> counter;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", &a[i]);
        counter[a[i]] ++;
    }
    int answer = 0, last = -1;
    for (std::map<int, int>::iterator iter = counter.begin(); iter != counter.end(); iter ++) {
        int x = (*iter).first, y = (*iter).second;
        answer += x - last - 1;
        y --;

        if (y & 1) {
            answer ++;
            y ++;
        }
        int size = 0;
        while (y) {
            temp[size ++] = y & 1;
            y >>= 1;
        }
        for (int i = 0; i < size; ++ i) {
            if (temp[i]) {
                counter[i + x] ++;
            }
        }
        last = x;
    }
    printf("%d\n", answer);
    return 0;
}
