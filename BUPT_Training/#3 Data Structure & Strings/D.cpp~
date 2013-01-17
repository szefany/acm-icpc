#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std ;

const int N = 20005 ;
const int Q = 40005 ;

int size[N] , rela[N] , key[N] , father[N] ;
int n , q ;

struct Query {
    int type ;
    vector<int> values ;
    inline void input () {
        values.clear () ;
        char str[2] ;
        scanf ( "%s" , str ) ;
        if ( *str == 'Q' ) {
            type = 2 ;
            int num ;
            scanf ( "%d" , &num ) ;
            while ( num -- ) {
                int x ;
                scanf ( "%d" , &x ) ;
                values.push_back ( x + 1 ) ;
            }
        }
        else {
            char buffer[200] ;
            gets ( buffer ) ;
            int blankCount = 0 ;
            for ( int i = 0 , len = strlen ( buffer ) ; i < len ; blankCount += buffer[i] == ' ' , ++ i ) ;
            values.resize ( blankCount ) ;
            if ( blankCount == 2 ) {
                sscanf ( buffer , "%d %d" , &values[0] , &values[1] ) ;
                values[0] ++ ;
            }
            else {
                sscanf ( buffer , "%d%d%d" , &values[0] , &values[1] , &values[2] ) ;
                values[0] ++ ;
                values[1] ++ ;
            }
            type = blankCount - 2 ;
        }
    }
} querys[Q] ;

inline void error ( int x ) {
    printf ( "The first %d facts are conflicting.\n" , x ) ;
}

inline void joint ( int x , int y , int value ) {
    if ( key[y] != -1 ) {
        father[x] = y ;
        rela[x] = value ;
    }
    else {
        father[y] = x ;
        rela[y] = value ;
    }
}

int que[N] ;
int find ( int u ) {
    int len = 0 , root = u ;
    while ( root != father[root] ) {
        que[++ len] = root ;
        root = father[root] ;
    }
    for ( int i = len , now = 0 ; i >= 1 ; -- i ) {
        int u = que[i] ;
        now ^= rela[u] ;
        rela[u] = now ;
        father[u] = root ;
    }
    return root ;
}

bool vis[20] ;

int main() {
    for ( int testCount = 1 ; scanf ( "%d%d" , &n , &q ) != EOF && n + q ; testCount ++ ) {
        printf ( "Case %d:\n" , testCount ) ;
        for ( int i = 1 ; i <= q ; ++ i )
            querys[i].input () ;
        for ( int i = 1 ; i <= n ; ++ i ) {
            size[i] = 1 ;
            key[i] = -1 ;
            rela[i] = 0 ;
            father[i] = i ;
        }
        for ( int i = 1 , factCount = 0 ; i <= q ; ++ i ) {
            if ( querys[i].type == 0 ) {
                factCount ++ ;
                int x = querys[i].values[0] ;
                int v = querys[i].values[1] ;
                int dx = find ( x ) ;
                if ( key[dx] != -1 && (key[dx] ^ rela[x]) != v ) {
                    error ( factCount ) ;
                    break ;
                }
                key[dx] = rela[x] ^ v ;
            }
            if ( querys[i].type == 1 ) {
                factCount ++ ;
                int x = querys[i].values[0] ;
                int y = querys[i].values[1] ;
                int v = querys[i].values[2] ;
                int dx = find ( x ) , dy = find ( y ) ;
                if ( (dx == dy && (rela[x] ^ rela[y]) != v ) || ( dx != dy && key[dx] != -1 && key[dy] != -1 && (rela[x] ^ rela[y] ^ key[dx] ^ key[dy]) != v ) ) {
                    error ( factCount ) ;
                    break ;
                }
                if ( dx != dy ) {
                    joint ( dx , dy , rela[x] ^ rela[y] ^ v ) ;
                }
            }
            if ( querys[i].type == 2 ) {
                memset ( vis , 0 , sizeof ( vis ) ) ;
                int m = querys[i].values.size() ;
                int ans = 0 ;
                bool flag = true ;
                for ( int j = 0 ; j < m ; ++ j ) {
                    if ( vis[j] ) continue ;
                    vis[j] = 1 ;
                    int x = querys[i].values[j] ;
                    int dx = find ( x ) ;
                    if ( key[dx] != -1 ) {
                        ans ^= key[dx] ^ rela[x] ;
                        continue ;
                    }
                    int y = 0 ;
                    for ( int k = j + 1 ; k < m ; ++ k ) {
                        int v = querys[i].values[k] ;
                        if ( find ( v ) == dx ) {
                            y = v ;
                            vis[k] = 1 ;
                            break ;
                        }
                    }
                    if ( y == 0 ) {
                        flag = false ;
                        break ;
                    }
                    ans ^= rela[x] ^ rela[y] ;
                }
                if ( !flag ) {
                    puts ( "I don't know." ) ;
                }
                else printf ( "%d\n" , ans ) ;
            }
        }
        puts ( "" ) ;
    }
}
