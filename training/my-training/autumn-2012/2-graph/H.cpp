#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
using namespace std ;

const int N = 1005 ;
const int M = 100000 ;
const int INF = INT_MAX ;

struct Edge {
    Edge () {}
    Edge ( int u , int v , int w , int c , int n ) : from(u) , to(v) , weight(w) , capa(c) , next(n) , flow(0) {}
    int from , to , weight , capa , flow , next ;
} g[M] ;

int first[N] ;
int n , m , edgeCount ;

inline void insert ( int u , int v , int w , int c ) {
    edgeCount ++ ;
    g[edgeCount] = Edge ( u , v , w , c , first[u] ) , first[u] = edgeCount ;
    g[M - edgeCount] = Edge ( v , u , -w , 0 , first[v] ) , first[v] = M - edgeCount ;
}

int arc[N] , dist[N] , links[N] ;
bool vis[N] , inQueue[N] ;
int totalCost , totalFlow , vs , vt ;

int dfs ( int u , int flow ) {
    if ( u == vt ) {
        totalCost += dist[u] * flow ;
        return flow ;
    }
    int result = 0 ;
    inQueue[u] = vis[u] = true ;
    for ( int &iter = arc[u] ; iter != 0 ; iter = g[iter].next ) {
        int v = g[iter].to ;
        int r = dist[u] + g[iter].weight - dist[v] ;
        int limit = flow ;
        if ( g[iter].capa < limit )
            limit = g[iter].capa ;
        if ( limit > 0 && r < links[v] )
            links[v] = r ;
        if ( limit > 0 && r == 0 && !inQueue[v] ) {
            r = dfs ( v , limit ) ;
            result += r ;
            flow -= r ;
            g[iter].capa -= r ;
            g[M - iter].capa += r ;
        }
        if ( flow == 0 ) break ;
    }
    inQueue[u] = false ;
    return result ;
}

void MinCostFlow () {
    totalCost = totalFlow = 0 ;
    while ( 1 ) {
        memcpy ( arc , first , sizeof ( arc ) ) ;
        memset ( vis , 0 , sizeof ( vis ) ) ;
        memset ( links , 100 , sizeof ( links ) ) ;
        totalFlow += dfs ( vs , INF ) ;
        int delta = links[0];
        for ( int i = 1 ; i <= vt ; ++i ) {
            if ( !vis[i] && links[i] < delta ) {
                delta = links[i] ;
            }
        }
        for ( int i = 1 ; i <= vt ; ++i ) {
            if ( !vis[i] ) {
                dist[i] += delta ;
            }
        }
        if ( delta == links[0] ) break ;
    }
}

int main() {
    scanf ( "%d%d" , &n , &m ) ;
    for ( int i = 1 ; i <= m ; ++i ) {
        int u , v , w ;
        scanf ( "%d%d%d" , &u , &v , &w ) ;
        insert ( u , v , w , 1 ) ;
        insert ( v , u , w , 1 ) ;
    }
    vs = n + 1 ;
    vt = n + 2 ;
    insert ( vs , 1 , 0 , 2 ) ;
    insert ( n , vt , 0 , 2 ) ;
    MinCostFlow () ;
    printf ( "%d\n" , totalCost ) ;
    return 0 ;
}
