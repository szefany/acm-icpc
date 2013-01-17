#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <set>
using namespace std ;

const int N = 100005 ;

int n ;
char s[N] ;
int next[N] ;

int main() {
    int caseCount ;
    scanf ( "%d" , &caseCount ) ;
    while ( caseCount -- ) {
        scanf ( "%s" , s + 1 ) ;
        int len = strlen ( s + 1 ) ;
        next[1] = 0 ;
        for ( int i = 2 , j = 0 ; i <= len ; ++ i ) {
            while ( j > 0 && s[j + 1] != s[i] ) j = next[j] ;
            if ( s[j + 1] == s[i] ) j ++ ;
            next[i] = j ;
        }
        printf ( "%d\n" , (next[len] != 0 && len % (len - next[len]) == 0 ) ? 0 : len - next[len] - len % (len - next[len]) ) ;
    }
}
