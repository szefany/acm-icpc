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

template<class T> inline void updateMax ( T &x , T y ) { x = ( x > y ) ? x : y ; }
template<class T> inline void updateMin ( T &x , T y ) { x = ( x < y ) ? x : y ; }

typedef long long LL ;
typedef pair<int, int> Pr ;

const double EPS = 1e-6 ;
const int INF = INT_MAX ;

const int N = 100005 ;
const int D = 20 ;

struct Tree {
    int l , r , lch , rch ;
} T[N * 2] ; 

int values[D][N] , toLeft[D][N] ;
int sorted[N] , a[N] ;
int n , q , size , root ;

void build ( int &u , int depth , int l , int r ) {
    u = ++ size ;
    T[u].l = l ;
    T[u].r = r ;
    if ( l == r ) return ;
    int mid = l + r >> 1 ;
    int midToLeft = mid - l + 1 ;
    for ( int i = l ; i <= r ; ++ i ) {
        if ( values[depth][i] < sorted[mid] ) {
            midToLeft -- ;
        }
    }
    for ( int i = l , Left = l - 1 , Right = mid , num = 0 ; i <= r ; ++ i ) {
        if ( i == l ) toLeft[depth][i] = 0 ;
        else toLeft[depth][i] = toLeft[depth][i - 1] ;
        if ( values[depth][i] < sorted[mid] ) {
            toLeft[depth][i] ++ ;
            values[depth + 1][++ Left] = values[depth][i] ;
        }
        else if ( values[depth][i] > sorted[mid] ) {
            values[depth + 1][++ Right] = values[depth][i] ;
        }
        else {
            if ( num < midToLeft ) {
                num ++ ;
                toLeft[depth][i] ++ ;
                values[depth + 1][++ Left] = values[depth][i] ;
            }
            else values[depth + 1][++ Right] = values[depth][i] ;
        }
    }
    build ( T[u].lch , depth + 1 , l , mid ) ;
    build ( T[u].rch , depth + 1 , mid + 1 , r ) ;
}

int query ( int l , int r , int k ) {
    int depth = 0 ;
    for ( int u = 1 ; T[u].l < T[u].r ; depth ++ ) {
        int que = 0 , rem = 0 ;
        if ( l == T[u].l ) {
            que = toLeft[depth][r] ;
            rem = 0 ;
        }
        else {
            que = toLeft[depth][r] - toLeft[depth][l - 1] ;
            rem = toLeft[depth][l - 1] ;
        }
        int Left , Right , counter ;
        if ( que >= k ) {
            Left = T[u].l + rem ;
            Right = Left + que - 1 ;
            counter = k ;
            u = T[u].lch ;
        }
        else {
            Left = (T[u].l + T[u].r >> 1) + 1 + l - T[u].l - rem ;
            Right = Left + r - l - que ;
            counter = k - que ;
            u = T[u].rch ;
        }
        l = Left ;
        r = Right ;
        k = counter ;
    }
    return values[depth][l] ;
}

void makeTree () {
    size = 0 ;
    for ( int i = 1 ; i <= n ; ++ i ) {
        sorted[i] = values[0][i] = a[i] ;
    }
    sort ( sorted + 1 , sorted + n + 1 ) ;
    build ( root , 0 , 1 , n ) ;
}

int main() {
    scanf ( "%d%d" , &n , &q ) ;
    for ( int i = 1 ; i <= n ; ++i ) {
        scanf ( "%d" , &a[i] ) ;
    }
    makeTree () ;
    while ( q -- ) {
        int l , r , k ;
        scanf ( "%d%d%d" , &l , &r , &k ) ;
        int ans = query ( l , r , k ) ;
        printf ( "%d\n" , ans ) ;
    }
}
