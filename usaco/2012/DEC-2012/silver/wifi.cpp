#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <sstream>
using namespace std ;

const int N = 2005 ;

long long f[N] , pos[N] ;
int n , a , b ;

int main() {
    freopen ( "wifi.in" , "r" , stdin ) ;
    freopen ( "wifi.out" , "w" , stdout ) ;
    scanf ( "%d%d%d" , &n , &a , &b ) ;
    for ( int i = 1 ; i <= n ; ++i ) {
        scanf ( "%lld" , &pos[i] ) ;
    }
    sort ( pos + 1 , pos + n + 1 ) ;
    memset ( f , 60 , sizeof ( f ) ) ;
    f[0] = 0 ;
    for ( int i = 1 ; i <= n ; ++i ) {
        for ( int j = 0 ; j < i ; ++j ) {
            long long cost = (long long)(((((double)pos[i] - pos[j + 1]) / 2 ) * b + a) * 2 + 0.5) ;
            if ( f[j] + cost < f[i] )
                f[i] = f[j] + cost ;
        }
    }
    if ( f[n] & 1 ) {
        printf ( "%lld.5\n" , f[n] / 2 ) ;
    }
    else printf ( "%lld\n" , f[n] / 2 ) ;
}
