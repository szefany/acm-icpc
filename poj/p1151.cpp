// POJ 1151, Atlantis
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct Event {
    int min_y, max_y, type;
    double x;
    Event () {}
    Event (double x0, int y1, int y2, int t): x (x0), min_y (y1), max_y (y2), type (t) {}
    bool operator < (const Event& other) const {
        return x < other.x;
    }
};

const int S = 200000 + 5;
const int N = 100;

vector<Event> events;
vector<double> all;

int cover[S << 1];
double length[S << 1];

int get_id (int l, int r) {
    return l + r | l != r;
}

void build (int l, int r) {
    int id = get_id (l, r);
    cover[id] = length[id] = 0;
    // printf ("%d %d %d\n", l, r, id);
    if (l + 1 < r) {
        int m = l + r >> 1;
        build (l, m);
        build (m + 1, r);
    }
}

void insert (int l, int r, int a, int b, int value) {
    if (a > r || b < l) {
        return;
    }
    int id = get_id (l, r);
    int m = l + r >> 1;
    if (a <= l && b >= r) {
        cover[id] += value;
    }
    else {
        insert (l, m, a, b, value);
        insert (m + 1, r, a, b, value);
    }
    if (cover[id]) {
        length[id] = all[r + 1] - all[l];
    }
    else {
        length[id] = l == r ? 0 : length[get_id (l, m)] + length[get_id (m + 1, r)];
    }
}

int find (double key) {
    return lower_bound (all.begin(), all.end(), key) - all.begin();
}

void add_rectangle (double x, int min_y, int max_y, int type) {
    events.push_back (Event (x, min_y, max_y, type));
}

double x0[N], y0[N], x1[N], y1[N];
int n;

void inititalise () {
    all.clear ();
    events.clear ();
}

int main () {
    for (int test_count = 1; scanf ("%d", &n) != EOF && n > 0; ++ test_count) {
        inititalise ();
        for (int i = 0; i < n; ++ i) {
            scanf ("%lf%lf%lf%lf", &x0[i], &y0[i], &x1[i], &y1[i]);
            all.push_back (y0[i]);
            all.push_back (y1[i]);
        }
        sort (all.begin(), all.end());
        all.resize (unique (all.begin(), all.end()) - all.begin());
        for (int i = 0; i < n; ++ i) {
            int min_y = find (y0[i]);
            int max_y = find (y1[i]);
            add_rectangle (x0[i], min_y, max_y, -1);
            add_rectangle (x1[i], min_y, max_y, 1);
        }
        sort (events.begin(), events.end());
        int MAX = all.size();
        build (0, 12);
        double area = 0;
        for (int i = 0; i < events.size(); ++ i) {
            if (i) {
                area += (events[i].x - events[i - 1].x) * length[get_id (0, MAX)];
            }
            insert (0, MAX, events[i].min_y, events[i].max_y - 1, events[i].type);
        }
        printf ("Test case #%d\n", test_count);
        printf ("Total explored area: %.2f\n\n", area);
    }
    return 0;
}
