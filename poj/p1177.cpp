// POJ 1177, Picture
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 10000 + 5;
const int S = 20000 + 5;

struct Event {
    int x, min_y, max_y, value;
    Event () {}
    Event (int x0, int y0, int y1, int v): x (x0), min_y (y0), max_y (y1), value (v) {}
    bool operator < (const Event& other) const {
        return x < other.x;
    }
};

int n;
int x[N][2], y[N][2];

vector <Event> events;
vector <int> all;

int number[S << 1], cover[S << 1];
bool left_end[S << 1], right_end[S << 1];

int get_id (int l, int r) {
    return l + r | l != r;
}

void build (int l, int r) {
    int id = get_id (l, r);
    number[id] = cover[id] = 0;
    left_end[id] = right_end[id] = false;
    if (l < r) {
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
        number[id] = 1;
        left_end[id] = right_end[id] = true;
    }
    else if (l == r) {
        number[id] = 0;
        left_end[id] = right_end[id] = false;
    }
    else {
        left_end[id] = left_end[get_id (l, m)];
        right_end[id] = right_end[get_id (m + 1, r)];
        number[id] = number[get_id (l, m)] + number[get_id (m + 1, r)] \
            - (right_end[get_id (l, m)] && left_end[get_id (m + 1, r)]);
    }
}

int find (int key) {
    return lower_bound (all.begin(), all.end(), key) - all.begin();
}

int solve () {
    events.clear();
    all.clear();
    for (int i = 0; i < n; ++ i) {
        all.push_back (y[i][0]);
        all.push_back (y[i][1]);
    }
    sort (all.begin(), all.end());
    all.resize (unique (all.begin(), all.end()) - all.begin());
    for (int i = 0; i < n; ++ i) {
        int min_y = find (y[i][0]);
        int max_y = find (y[i][1]);
        events.push_back (Event (x[i][0], min_y, max_y, 1));
        events.push_back (Event (x[i][1], min_y, max_y, -1));
    }
    sort (events.begin(), events.end());
    int MAX = all.size();
    build (0, MAX);
    int result = 0;
    for (int i = 0; i < events.size(); ++ i) {
        if (i) {
            result += number[get_id (0, MAX)] * 2 * (events[i].x - events[i - 1].x);
        }
        insert (0, MAX, events[i].min_y, events[i].max_y - 1, events[i].value);
    }
    return result;
}

int main () {
    scanf ("%d", &n);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < 2; ++ j) {
            scanf ("%d%d", &x[i][j], &y[i][j]);
        }
    }
    int perimeter = solve ();
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < 2; ++ j) {
            swap (x[i][j], y[i][j]);
        }
    }
    perimeter += solve ();
    printf ("%d\n", perimeter);
    return 0;
}
