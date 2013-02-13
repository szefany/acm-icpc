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
const int B = 505 ;
const int M = 50005 ;
const int N = 250005 ;

int n , len , blockCount ;
int a[N] , belong[N] ;
int sum[B][M] , length[B] ;
long long ans ;

inline int lowbit ( int x ) {
    return x & (-x) ;
}

inline int getSum ( int t , int x ) {
    int result = 0 ;
    for ( ; x > 0 ; x -= lowbit ( x ) )
        result += sum[t][x] ;
    return result ;
}

inline void add ( int t , int x , int key ) {
    for ( ; x < M ; x += lowbit ( x ) )
        sum[t][x] += key ;
}

inline int findMax ( int r , int key ) {
    if ( r < 1 ) return 0 ;
    int result = 0 ;
    int i = 1 ;
    for ( int b = 1 ; i + length[b] - 1 <= r ; i += length[b] , b ++ ) {
        result += getSum ( b , M - 1 ) - getSum ( b , key ) ; 
    }
    for ( int j = i ; j <= r ; ++ j )
        result += (a[j] > key) ;
    return result ;
}

inline int findMin ( int l , int key ) {
    if ( l > n ) return 0 ;
    int result = 0 ;
    int i = n ;
    for ( int b = blockCount ; i - length[b] + 1 >= l ; i -= length[b] , b -- )
        result += getSum ( b , key - 1 ) ; 
    for ( int j = i ; j >= l ; -- j )
        result += (a[j] < key) ;
    return result ;
}

inline void modify ( int pos , int key ) {
    // int b = 1 ;
    // for ( int i = 1 ; i + length[b] - 1 < pos ; i += length[b] , b ++ ) ;
    int b = belong[pos] ;
    add ( b , a[pos] , -1 ) ;
    a[pos] = key ;
    add ( b , a[pos] , 1 ) ;
}

int main() {
    scanf ( "%d" , &n ) ;
    for ( int i = 1 ; i <= n ; ++ i ) {
        scanf ( "%d" , &a[i] ) ;
        ans += getSum ( 0 , M - 1 ) - getSum ( 0 , a[i] ) ;
        add ( 0 , a[i] , 1 ) ;
    }
    len = sqrt ( n * 1.0 ) * 2 ;
    blockCount = 0 ;
    for ( int i = 1 ; i <= n ; i += len ) {
        int j = min ( i + len - 1 , n ) ;
        length[++ blockCount] = j - i + 1 ;
        for ( int k = i ; k <= j ; ++ k ) {
            belong[k] = blockCount ;
            add ( blockCount , a[k] , 1 ) ;
        }
    }
    int q ;
    scanf ( "%d" , &q ) ;
    while ( q -- ) {
        int pos , key ;
        scanf ( "%d%d" , &pos , &key ) ;
        int delta = (findMax ( pos - 1 , key ) + findMin ( pos + 1 , key )) - (findMax ( pos - 1 , a[pos] ) + findMin ( pos + 1 , a[pos] )) ;
        modify ( pos , key ) ;
        ans += delta ;
        printf ( "%lld\n" , ans ) ;
    }
    return 0 ;
}
