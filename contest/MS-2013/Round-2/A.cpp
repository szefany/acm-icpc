#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>

const int N = 50000 + 10;
const int S = 1 << 19;
const int INF = 500000 + 2;

int tree[S << 1], tree2[S << 1], judge[N];
int n;
std::set<int> set;

int query(int *element, int x) {
    int answer = 0;
    for (x += S; x; x >>= 1) {
        answer += element[x];
    }
    return answer;
}

void push(int *element, int x, int y) {
    for (x = x + S - 1, y = y + S + 1; x ^ y ^ 1; x >>= 1, y >>= 1) {
        if (~x & 1) {
            element[x ^ 1] ++;
        }
        if (y & 1) {
            element[y ^ 1] ++;
        }
    }
}

void initialise() {
    set.clear();
    memset(tree, 0, sizeof(tree));
    memset(tree2, 0, sizeof(tree2));
    set.insert(1);
    set.insert(INF);
    push(tree, 2, INF);
    push(tree2, 1, INF);    
}

int main() {
    int test_count;
    scanf("%d", &test_count);
    for (int t = 1; t <= test_count; ++ t) {
        scanf("%d", &n);
        initialise();
        for (int i = 0; i < n; ++ i) {
            scanf("%d", &judge[i]);
            judge[i] += 2;
        }
        for (int i = 0; i < n; ++ i) {
            std::set<int>::iterator iter = set.lower_bound(judge[i]);
            std::set<int>::iterator iter2 = iter;
            iter2 --;
            push(tree2, (*iter2) + 1, (*iter) - 1);
            push(tree, judge[i] + 1, (*iter) - 1);
            set.insert(judge[i]);
        }
        int current = 1;
        int left = 2;
        for (int i = 0; i < n; ++ i) {
            left += query(tree2, judge[i]);
            current += query(tree, judge[i]);
        }
        printf("Case #%d: %d %d\n", t, left, current);
    }
    return 0;
}
