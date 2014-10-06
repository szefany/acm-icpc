#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

const int N = 10000 + 10;

char element[N];
int order[N], rank[N], rank1[N], rank2[N], sa[N], temp_sa[N], height[N], bucket[N];
int n;

bool cmp(int x, int y) {
    return element[x] < element[y];
}

void build_sa(int n) {
    for (int i = 1; i <= n; ++ i) {
        order[i] = i;
    }
    std::sort(order + 1, order + n + 1, cmp);
    rank[order[1]] = 1;
    sa[1] = order[1];
    for (int i = 2; i <= n; ++ i) {
        rank[order[i]] = rank[order[i - 1]] + (element[order[i - 1]] != element[order[i]]);
        sa[rank[order[i]]] = order[i];
    }
    for (int length = 1; length < n; length <<= 1) {
        for (int i = 1; i <= n; ++ i) {
            rank1[i] = rank[i];
            rank2[i] = i + length <= n ? rank[i + length] : 0;
        }
        memset(bucket, 0, sizeof(bucket));
        for (int i = 1; i <= n; ++ i) {
            bucket[rank2[i]] ++;
        }
        for (int i = 1; i <= n; ++ i) {
            bucket[i] += bucket[i - 1];
        }
        for (int i = 1; i <= n; ++ i) {
            temp_sa[bucket[rank2[i]] --] = i;
        }
        memset(bucket, 0, sizeof(bucket));
        for (int i = 1; i <= n; ++ i) {
            bucket[rank1[i]] ++;
        }
        for (int i = 1; i <= n; ++ i) {
            bucket[i] += bucket[i - 1];
        }
        for (int i = n; i >= 1; -- i) {
            sa[bucket[rank1[temp_sa[i]]] --] = temp_sa[i];
        }
        rank[sa[1]] = 1;
        for (int i = 2; i <= n; ++ i) {
            rank[sa[i]] = rank[sa[i - 1]] + (rank1[sa[i - 1]] != rank1[sa[i]] || rank2[sa[i - 1]] != rank2[sa[i]]);
        }
    }

    for (int i = 1, lcp = 0, value = 0; i <= n; ++ i) {
        if (rank[i] > 1) {
            int j = sa[rank[i] - 1];
            while (i + lcp <= n && j + lcp <= n && element[i + lcp] == element[j + lcp]) {
                lcp ++;
            }
        }
        height[rank[i]] = lcp;
        lcp -= (lcp > 0);
    }
}

int main() {
    scanf("%s", element + 1);
    n = strlen(element + 1);
    build_sa(n);

    long long answer = 0;
    for (int length = 1; length <= n; ++ length) {
        int current = 0;
        for (int i = 1; i <= n; ) {
            int j = i + 1;
            int left = sa[i];
            int right = sa[i];
            while (j <= n && height[j] >= length) {
                left = std::min(left, sa[j]);
                right = std::max(right, sa[j]);
                j ++;
            }
            if (right - left >= length) {
                current ++;
            }
            i = j;
        }
        answer += current;
        if (current == 0) break;
    }
    printf("%lld\n", answer);
}
