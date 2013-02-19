#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std ;

const int N = 1000005 ;

char str[N] ;
int next[N] , extend[N] ;

int main () {
    int caseCount ;
    scanf ( "%d" , &caseCount ) ;
    while ( caseCount -- ) {
        scanf ( "%s" , str ) ;
        int len = strlen ( str ) ;
        reverse ( str , str + len ) ;
        next[0] = len ;
        int j = 0 ; 
        while ( j < len - 1 && str[j] == str[j + 1] ) j ++ ;
        next[1] = j ;
        for ( int i = 2 , k = 1 ; i < len ; ++ i ) {
            if ( next[i - k] + i < next[k] + k )
                next[i] = next[i - k ] ;
            else {
                int j = max ( 0 , next[k] + k - i ) ;
                while ( i + j < len && str[j] == str[j + i] ) j ++ ;
                next[i] = j ;
                k = i ;
            }
        }
        int q ;
        scanf ( "%d" , &q ) ;
        while ( q -- ) {
            int x ;
            scanf ( "%d" , &x ) ;
            x = len - x ;
            printf ( "%d\n" , next[x] ) ;
        }
    }
}
