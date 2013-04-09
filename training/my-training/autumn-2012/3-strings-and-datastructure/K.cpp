#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std ;

const int N = 2000005 ;

char total[N] , rtotal[N] , buffer[N] , buffer2[N] ;
int next[N] , extend[N] , len[N] ;
int n ;

void extended_kmp ( char *S , char *T , int len ) {
    int len_T = len ;
    next[0] = len_T ;
    int j = 0 ;
    while ( j < len_T - 1 && T[j] == T[j + 1] )
        j ++ ;
    next[1] = j ;
    for ( int i = 2 , k = 1 ; i < len_T ; ++ i ) {
        if ( next[i - k] + i < next[k] + k ) {
            next[i] = next[i - k] ;
        }
        else {
            int j = max ( 0 , next[k] + k - i ) ;
            while ( i + j < len_T && T[j] == T[j + i] )
                j ++ ;
            next[i] = j ;
            k = i ;
        }
    }
    int len_S = len ;
    int i = 0 ;
    while ( i < len_S && i < len_T && S[i] == T[i] )
        i ++ ;
    extend[0] = i ;
    for ( int i = 1 , k = 0 ; i < len_S ; ++ i ) {
        if ( next[i - k] + i < extend[k] + k ) {
            extend[i] = next[i - k] ;
        }
        else {
            int j = max ( 0 , extend[k] + k - i ) ;
            while ( i + j < len_S && j < len_T && S[i + j] == T[j + 1] )
                j ++ ;
            extend[i] = j ;
            k = i ;
        }
    }
}

struct Tree {
    int index[26] ;
    int finish , flag ;
} T[N] ; 
int nodeCount ;

inline void insert ( char *s , int len ) {
    int u = 1 ;
    for ( int i = 0 ; i < len ; ++ i ) {
        int key = s[i] - 'a' ;
        if ( T[u].index[key] == 0 )
            T[u].index[key] = ++ nodeCount ;
        u = T[u].index[key] ;
        if ( i < len - 1 && extend[i + 1] + i + 1 == len )
            T[u].flag ++ ;
    }
    T[u].finish ++ ;
}

int main() {
    scanf ( "%d" , &n ) ;
    nodeCount = 1 ;
    for ( int i = 1 , current = 0 ; i <= n ; ++ i ) {
        scanf ( "%d " , &len[i] ) ;
        for ( int j = 0 ; j < len[i] ; ++ j )
            total[current + j] = getchar () ;
        current += len[i] ;
    }
    long long ans = 0 ;
    for ( int i = 1 , current = 0 ; i <= n ; ++ i ) {
        for ( int j = 0 ; j < len[i] ; ++ j ) {
            buffer[j] = total[current + j] ;
            buffer2[j] = total[current + len[i] - (j + 1)] ;
        }
        current += len[i] ;
        extended_kmp ( buffer , buffer2 , len[i] ) ;
        int u = 1 ;
        for ( int j = 0 ; j < len[i] ; ++ j ) {
            if ( T[u].index[buffer[j] - 'a'] == 0 )
                T[u].index[buffer[j] - 'a'] = ++ nodeCount ;
            u = T[u].index[buffer[j] - 'a'] ;
            if ( j < len[i] - 1 && extend[j + 1] + j + 1 == len[i] )
                T[u].flag ++ ;
        }
        T[u].finish ++ ;
    }
    for ( int i = 1 , current = 0 ; i <= n ; ++ i ) {
        for ( int j = 0 ; j < len[i] ; ++ j ) {
            buffer[j] = total[current + j] ;
            buffer2[j] = total[current + len[i] - (j + 1)] ;
        }
        current += len[i] ;
        extended_kmp ( buffer2 , buffer , len[i] ) ;
        int u = 1 ;
        for ( int j = 0 ; j < len[i] ; ++ j ) {
            u = T[u].index[buffer2[j] - 'a'] ;
            if ( u == 0 ) break ;
            if ( j == len[i] - 1 || extend[j + 1] + j + 1 == len[i] )
                ans += T[u].finish ;
        }
        if ( u > 0 ) ans += T[u].flag ;
    }
    printf ( "%lld\n" , ans ) ;
    return 0 ;
}
