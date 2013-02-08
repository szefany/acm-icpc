// POJ 1389, Area of Simple Polygons
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct Event {
    int x, min_y, max_y, type;
    Event () {}
    Event (int x0, int y1, int y2, int t): x (x0), min_y (y1), max_y (y2), type (t) {}
    bool operator < (const Event& other) const {
        return x < other.x;
    }
};

const int S = 200000 + 5;
const int N = 2000;

vector<Event> events;
vector<int> all;

int cover[S << 1];
double length[S << 1];

int get_id (int l, int r) {
    return l + r | l != r;
}

void build (int l, int r) {
    int id = get_id (l, r);
    cover[id] = length[id] = 0;
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

int x0[N], y0[N], x1[N], y1[N];
int n;

void inititalise () {
    all.clear ();
    events.clear ();
}

int main () {
    while (scanf ("%d%d%d%d", &x0[0], &y0[0], &x1[0], &y1[0]) != EOF) {
        int sum = x0[0] + x1[0] + y0[0] + y1[0];
        if (sum == -4) {
            break;
        }
        inititalise ();
        all.push_back (y0[0]);
        all.push_back (y1[0]);
        for (n = 1; sum >= 0; ++ n) {
            scanf ("%d%d%d%d", &x0[n], &y0[n], &x1[n], &y1[n]);
            sum = x0[n] + x1[n] + y0[n] + y1[n];
            all.push_back (y0[n]);
            all.push_back (y1[n]);
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
        build (0, MAX);
        long long area = 0;
        for (int i = 0; i < events.size(); ++ i) {
            if (i) {
                area += (long long)length[get_id (0, MAX)] * (events[i].x - events[i - 1].x);
            }
            insert (0, MAX, events[i].min_y, events[i].max_y - 1, events[i].type);
        }
        cout << area << '\n';
    }
    return 0;
}
