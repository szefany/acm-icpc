#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <climits>

#define clr(x) memset ( (x) , 0 , sizeof ( x ) )
#define Mp make_pair
#define Pb push_back

using namespace std ;

typedef long long LL ;
typedef pair<int, int> Pr ;

const double EPS = 1e-6 ;
const int INF = INT_MAX ;
const int N = 100005 ;
const int D = 2 ;

struct Point {
    int x[D] ;
    int id ;
    inline void input ( int id1 ) {
        id = id1 ;
        for ( int i = 0 ; i < D ; ++ i ) {
            scanf ( "%d" , &x[i] ) ;
        }
    }
} ;

vector<Point> points , total ;
Point current ;

int n ;
int divide[N] , T[N] ;
long long ans ;

void init () {
    clr ( divide ) , clr ( T ) ;
    points.clear () ;
    total.clear () ;
}

int now ;
inline bool cmp ( const Point &a , const Point &b ) {
    return a.x[now] < b.x[now] ;
}

void build ( int l , int r ) {
    if ( l >= r ) return ;
    int mid = l + r >> 1 ;
    int min_values[D] , max_values[D] ;
    for ( int i = 0 ; i < D ; ++ i ) {
        min_values[i] = INF ;
        max_values[i] = -INF ;
    }
    for ( int i = l ; i < r ; ++ i ) {
        for ( int j = 0 ; j < D ; ++ j ) {
#define updateMin(a, b) if ((b) < (a)) (a) = (b)
#define updateMax(a, b) if ((b) > (a)) (a) = (b) 
            updateMin ( min_values[j] , total[i].x[j] ) ;
            updateMax ( max_values[j] , total[i].x[j] ) ;
        }
    }
    now = (long long)max_values[0] - min_values[0] > (long long)max_values[1] - min_values[1] ? 0 : 1 ;
    divide[mid] = now ;
    nth_element ( total.begin() + l , total.begin() + mid , total.begin() + r , cmp ) ;
    for ( int i = 0 ; i < D ; ++ i ) {
        T[mid] = total[mid].id ;
    }
    build ( l , mid ) ;
    build ( mid + 1 , r ) ;
}

void find ( int l , int r ) {
    if ( l >= r ) return ;
    int mid = l + r >> 1 ;
    long long delta[D] ;
    long long d = 0 ;
    for ( int i = 0 ; i < D ; ++ i ) {
        delta[i] = (long long)current.x[i] - points[ T[mid] ].x[i] ;
        d += (long long)delta[i] * delta[i] ;
    }
    if ( current.id != points[ T[mid] ].id && d < ans ) ans = d ;
    if ( l + 1 == r ) return ;
    int l1 = l , r1 = mid ;
    int l2 = mid + 1 , r2 = r ;
    if ( delta[ divide[mid] ] > 0 ) {
        swap ( l1 , l2 ) ;
        swap ( r1 , r2 ) ;
    }
    find ( l1 , r1 ) ;
    if ( ans > (long long)delta[ divide[mid] ] * delta[ divide[mid] ] )
        find ( l2 , r2 ) ;
}

int main() {
    int testCount ;
    scanf ( "%d" , &testCount ) ;
    while ( testCount -- ) {
        init () ;
        scanf ( "%d" , &n ) ;
        for ( int i = 0 ; i < n ; ++ i ) {
            Point p ;
            p.input ( i ) ;
            points.push_back ( p ) ;
            total.push_back ( p ) ;
        }
        build ( 0 , n ) ;
        for ( int i = 0 ; i < points.size() ; ++ i ) {
            current = points[i] ;
            ans = 1LL << 62 ;
            find ( 0 , n ) ;
            printf ( "%lld\n" , ans ) ;
        }
    }
}
