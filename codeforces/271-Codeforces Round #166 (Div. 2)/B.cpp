#include <iostream>
#include <cstdio>
#include <vector>
#include <climits>
using namespace std;

const int N = 600;
const int M = 150000;

bool visit[M];
vector <int> prime;
void get_prime () {
    for (int i = 2; i < M; ) {
        prime.push_back (i);
        for (int j = i + i; j < M; j += i) {
            visit[j] = true;
        }
        for (i ++; i < M && visit[i]; ++ i);
    }
}

int n, m, answer;
int elements[N][N];

const int INF = INT_MAX;

int solve () {
    int result = INF;
    for (int i = 0; i < n; ++ i) {
        int temp = 0;
        for (int j = 0; j < m; ++ j) {
            int delta = *(lower_bound (prime.begin(), prime.end(), elements[i][j]));
            delta -= elements[i][j];
            temp += delta;
        }
        result = min (result, temp);
    }
    return result;
}

int solve_2 () {
    int result = INF;
    for (int i = 0; i < m; ++ i) {
        int temp = 0;
        for (int j = 0; j < n; ++ j) {
            int delta = *(lower_bound (prime.begin(), prime.end(), elements[j][i]));
            delta -= elements[j][i];
            temp += delta;
        }
        result = min (result, temp);
    }
    return result;
}

int main () {
    get_prime ();
    scanf ("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            scanf ("%d", &elements[i][j]);
        }
    }
    answer = INF;
    answer = min (answer, solve ());
    answer = min (answer, solve_2 ());
    cout << answer << endl;
    return 0;
}
