#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std ;

const int N = 100005 ;
const int INF = 1 << 30 ;

struct Tree {
    int index[26] ;
    int step , prev , key ;
} T[N * 4] ;
int nodeCount ;

char s[N * 2] ;

void build ( char *s ) {
    int len = strlen ( s ) ;
    nodeCount = 1 ;
    for ( int i = 0 , last = 1 , current ; i < len ; ++ i , last = current ) {
        int key = s[i] - 'a' ;
        current = ++ nodeCount ;
        T[current].step = T[last].step + 1 ;
        T[current].key = INF ;
        int node ;
        for ( node = last ; node && T[node].index[key] == 0 ; node = T[node].prev )
            T[node].index[key] = current ;
        if ( node == 0 ) {
            T[current].prev = 1 ;
            continue ;
        }
        int v = T[node].index[key] ;
        if ( T[v].step == T[node].step + 1 )
            T[current].prev = v ;
        else {
            int nv = ++ nodeCount ;
            T[nv] = T[v] ;
            T[nv].step = T[node].step + 1 ;
            T[v].prev = T[current].prev = nv ;
            for ( ; node && T[node].index[key] == v ; node = T[node].prev )
                T[node].index[key] = nv ;
        }
    }
}

int main() {
    scanf ( "%s" , s ) ;
    int len = strlen ( s ) ;
    for ( int i = 0 ; i < len ; ++ i )
        s[i + len] = s[i] ;
    s[len + len] = '\0' ;
    build ( s ) ;
    for ( int i = 0 , u = 1 ; i < len + len ; ++ i ) {
        int key = s[i] - 'a' ;
        for ( ; u && T[u].index[key] == 0 ; u = T[u].prev ) ;
        if ( !u ) u = 1 ;
        else u = T[u].index[key] ;
        T[u].key = min ( T[u].key , i ) ;
    }
    int u = 1 ;
    for ( int i = 0 ; i < len ; ++ i ) {
        int j ;
        for ( j = 0 ; T[u].index[j] == 0 ; ++ j ) ;
        u = T[u].index[j] ;
    }
    printf ( "%d\n" , T[u].key - len + 1 ) ;
}
