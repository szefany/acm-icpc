#include <cstdio>
#include <cstring>
#include <deque>

char string[100 + 10];
int min_value[100 + 10];

int main() {
    int test;
    scanf("%d", &test);
    while (test --) {
        scanf("%s", string);
        int length = strlen(string);
        min_value[length] = 1000;
        for (int i = length - 1; i >= 0; -- i) {
            if (string[i] == '0') {
                min_value[i] = min_value[i + 1];
            } else {
                min_value[i] = std::min(min_value[i + 1], (int)string[i]);
            }
        }
        std::deque<char> deque;
        deque.push_front(string[0]);
        int now = string[0];
        for (int i = 1; i < length; ++ i) {
            if (string[i] == '0') {
                if (min_value[i] == min_value[0]) {
                    deque.push_front(string[i]);
                } else {
                    deque.push_back(string[i]);
                }
            } else {
                if (deque.front() == '0') {
                    if (min_value[i + 1] > min_value[0]) {
                        deque.push_front(string[i]);
                    } else {
                        deque.push_back(string[i]);
                    }
                } else if (string[i] <= deque.front()) {
                    deque.push_front(string[i]);
                } else {
                    deque.push_back(string[i]);
                }
            }
        }
        while (!deque.empty()) {
            putchar(deque.front());
            deque.pop_front();
        }
        puts("");
    }
    return 0;
}
