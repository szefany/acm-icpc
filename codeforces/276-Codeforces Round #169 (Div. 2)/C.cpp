// Codeforces Round #169 (Div. 2)
// Problem C, Little Girl and Maximum Sum
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>

const int N = 200000 + 5;

int values[N], elements[N];
int n, q;

struct Node {
    Node () {}
    Node (int index, int value): index (index), value (value) {}
    int index, value;
    bool operator < (const Node& other) const {
        return value < other.value;
    }
};

bool cmp (int x, int y) {
    return x > y;
}

int lowbit (int x) {
    return x & -x;
}

int get (int x) {
    int result = 0;
    for (; x > 0; x -= lowbit (x)) {
        result += values[x];
    }
    return result;
}

void add (int x, int value) {
    for (; x <= n; x += lowbit (x)) {
        values[x] += value;
    }
}

int main () {
    scanf ("%d%d", &n, &q);
    for (int i = 1; i <= n; ++ i) {
        scanf ("%d", &elements[i]);
    }
    while (q --) {
        int l, r;
        scanf ("%d%d", &l, &r);
        add (l, 1);
        add (r + 1, -1);
    }
    std::priority_queue <Node> queue;
    for (int i = 1; i <= n; ++ i) {
        queue.push (Node (i, get (i)));
    }
    std::sort (elements + 1, elements + n + 1, cmp);
    long long answer = 0;
    for (int i = 1; i <= n; ++ i) {
        int value = queue.top().value;
        queue.pop();
        answer += (long long)elements[i] * value;
    }
    std::cout << answer << std::endl;
    return 0;
}
