// Codeforces Round #156 (Div. 1)
// Problem A, Almost Arithmetical Progression
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 4000;
const int M = 1000005;

int elements[N], next[N];
int location[M], visit[M][3], number[M];
int n;

int main () {
    scanf ("%d", &n);
    if (n < 3) {
        cout << n << endl;
        return 0;
    }
    int answer = 0;
    for (int i = 0; i < n; ++ i) {
        scanf ("%d", &elements[i]);
        location[elements[i]] = n;
        number[elements[i]] ++;
        if (number[elements[i]] > answer) {
            answer = number[elements[i]];
        }
    }
    for (int i = n - 1; i >= 0; -- i) {
        next[i] = location[elements[i]];
        location[elements[i]] = i;
    }
    memset (visit, -1, sizeof (visit));
    for (int start = 0; start < n; ++ start) {
        int temp = 1;
        for (int now = start; now < n; now = next[now]) {
            bool flag = false;
            for (int i = now + 1; i < next[now]; ++ i) {
                int key = elements[i];
                if (visit[key][0] != start) {
                    visit[key][0] = start;
                    visit[key][1] = 1;
                    visit[key][2] = now;
                }
                else if (visit[key][2] != now) {
                    visit[key][1] ++;
                    visit[key][2] = now;
                }
                temp = max (temp, visit[key][1] * 2 + (next[now] < n));
            }
        }
        answer = max (answer, temp);
    }
    cout << answer << endl;
    return 0;
}
