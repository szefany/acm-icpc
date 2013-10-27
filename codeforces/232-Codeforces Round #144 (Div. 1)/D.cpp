#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using std::min;

const int N = 200000 + 10;
const int D = 18;

int element[N];
int order[N], rank[N], rank1[N], rank2[N], sa[N], temp_sa[N], height[N], bucket[N], temp_height[N];
int minimum[N][D];
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
        height[rank[i]] = temp_height[i] = lcp;
        lcp -= (lcp > 0);
    }

    for (int i = 1; i <= n; ++ i) {
        minimum[i][0] = height[i];
    }
    int length = floor(log(n) / log(2));
    for (int j = 1; j <= length; ++ j) {
        for (int i = 1; i <= n; ++ i) {
            int k = min(n, i + (1 << j - 1));
            minimum[i][j] = min(minimum[i][j - 1], minimum[k][j - 1]);
        }
    }
/*
    printf("elements: ");
    for (int i = 1; i <= n; ++ i) {
        printf("%d ", element[i]);
    } puts("");

    printf("sa: ");
    for (int i = 1; i <= n; ++ i) {
        printf("%d ", sa[i]);
    } puts("");

    printf("height: ");
    for (int i = 1; i <= n; ++ i) {
        printf("%d ", height[i]);
    } puts("");
*/
}

int lcp(int x, int y) {
    if (x == y) {
        return n + n - 1 - sa[x] + 1;
    }
    x ++;
    int length = floor(log(y - x + 1) / log(2));
    return min(minimum[x][length], minimum[y - (1 << length) + 1][length]);
}

int left_bound(int pos, int width) {
    int lower = 1, upper = pos;
    while (lower < upper) {
        int middle = lower + upper >> 1;
        if (lcp(middle, pos) >= width) {
            upper = middle;
        } else {
            lower = middle + 1;
        }
    }
    return lower;
}

int right_bound(int pos, int width) {
    int lower = pos, upper = n + n - 1;
    while (lower < upper) {
        int middle = lower + upper + 1 >> 1;
        if (lcp(pos, middle) >= width) {
            lower = middle;
        } else {
            upper = middle - 1;
        }
    }
    return lower;
}

const int S = N << 2;

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

std::vector<int> values[S];

void build_interval(int u, int l, int r) {
    for (int i = l; i <= r; ++ i) {
        values[u].push_back(sa[i]);
    }
    std::sort(values[u].begin(), values[u].end());
    if (l < r) {
        int m = l + r >> 1;
        build_interval(L(u), l, m);
        build_interval(R(u), m + 1, r);
    }
}

int query_interval(int u, int l, int r, int a, int b, int v) {
    if (a > r || b < l) {
        return 0;
    }
    if (a <= l && b >= r) {
        std::vector<int>::iterator iter = upper_bound(values[u].begin(), values[u].end(), v);
        return iter - values[u].begin();
    }
    int m = l + r >> 1;
    return query_interval(L(u), l, m, a, b, v) + query_interval(R(u), m + 1, r, a, b, v);
}

int get_amount(int lower, int upper, int l, int r) {
    if (l > r) {
        return 0;
    }
    int result = query_interval(1, 1, n + n - 1, lower, upper, r) - query_interval(1, 1, n + n - 1, lower, upper, l - 1);
    return result;
}

int query(int l, int r) {
    if (l > r) {
        return n - 1;
    }
    int width = r - l + 1;
    int pos = rank[l];
    int lower = left_bound(pos, width);
    int upper = right_bound(pos, width);
    return get_amount(lower, upper, n + 1, l - width - 1 + n) + get_amount(lower, upper, r + n + 2, n + n - 1);
}

const int INF = 1 << 30;

int origin[N], a[N], b[N];

int main() {
    freopen("input", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", origin + i);
    }

    for (int i = 1; i < n; ++ i) {
        element[i] = origin[i] - origin[i + 1];
        element[i + n] = -element[i];
    }
    element[n] = INF;

    build_sa(n + n - 1);
    build_interval(1, 1, n + n - 1);

    int q;
    scanf("%d", &q);
    while (q --) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r - 1));
    }
    return 0;
}
