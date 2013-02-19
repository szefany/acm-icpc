#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <set>
using namespace std ;

const int N = 16000005 ;

int n , p ;
int label[300] ;
char s[N] ;
bool hash[N] ;

int main () {
    scanf ( "%d%d" , &n , &p ) ;
    int Pow = 1 ;
    for ( int i = 1 ; i < n ; ++ i )
        Pow = Pow * p % N ;
    getchar () ;
    gets ( s ) ;
    int len = strlen ( s ) ;
    if ( n > len ) {
        printf ( "0\n" ) ;
        return 0 ;
    }
    int temp = 0 , labelCount = 0 ;
    for ( int i = 0 ; i < n ; ++ i ) {
        char key = s[i] ;
        if ( !label[key] )
            label[key] = ++ labelCount ;
        temp = (temp * p + label[key]) % N ;
    }
    int ans = 1 ;
    hash[temp] = 1 ;
    for ( int i = n ; i < len ; ++ i ) {
        char key = s[i] ;
        if ( !label[key] )
            label[key] = ++ labelCount ;
        temp = ((temp - label[s[i - n]] * Pow) * p + label[key]) % N ;
        if ( !hash[temp] ) {
            hash[temp] = 1 ;
            ans ++ ;
        }
    }
    printf ( "%d\n" , ans ) ;
}
