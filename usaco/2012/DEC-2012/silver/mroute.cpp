#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std ;

const int N = 505 ;

struct Edge {
    Edge () {}
    Edge ( int v , int w , int c , int n ) : to(v) , weight(w) , capa(c) , next(n) {}
    int to , weight , capa , next ;
} g[N * 3] ;

int edgeCount ;
int n , m ;
int first[N] , dist[N] ;
bool inQueue[N] ;

void addEdge ( int u , int v , int w , int c ) {
    edgeCount ++ ;
    g[edgeCount] = Edge ( v , w , c , first[u] ) , first[u] = edgeCount ;
}

int q[N + N + 1] ;
int calc ( int x ) {
    static const int Q = N + N ;
    memset ( dist , 60 , sizeof ( dist ) ) ;
    memset ( inQueue , 0 , sizeof ( inQueue ) ) ;
    dist[1] = 0 ;
    q[1] = 1 ;
    int head = 0 , tail = 1 ;
    while ( head != tail ) {
        head = head % Q + 1 ;
        int u = q[head] ;
        inQueue[u] = false ;
        for ( int iter = first[u] ; iter != 0 ; iter = g[iter].next ) {
            int v = g[iter].to ;
            if ( g[iter].capa >= x && dist[u] + g[iter].weight < dist[v] ) {
                dist[v] = dist[u] + g[iter].weight ;
                if ( !inQueue[v] ) {
                    inQueue[v] = true ;
                    tail = tail % Q + 1 ;
                    q[tail] = v ;
                }
            }
        }
    }
    if ( dist[n] == dist[0] ) return -1 ;
    return dist[n] ;
}

int main() {
    freopen ( "mroute.in" , "r" , stdin ) ;
    freopen ( "mroute.out" , "w" , stdout ) ;
    int X ;
    scanf ( "%d%d%d" , &n , &m , &X ) ;
    vector<int> counter ;
    for ( int i = 1 ; i <= m ; ++i ) {
        int u , v , w , c ;
        scanf ( "%d%d%d%d" , &u , &v , &w , &c ) ;
        addEdge ( u , v , w , c ) ;
        addEdge ( v , u , w , c ) ;
        counter.push_back ( c ) ;
    }
    if ( n == 1 ) {
        printf ( "%d\n" , 0 ) ;
        return 0 ;
    }
    sort ( counter.begin() , counter.end() ) ;
    counter.resize ( unique ( counter.begin() , counter.end() ) - counter.begin() ) ;
    double ans = 1e100 ;
    for ( int i = 0 ; i < counter.size() ; ++i ) {
        int len = calc ( counter[i] ) ;
        if ( len != -1 && X * 1.0 / counter[i] + len < ans )
            ans = X * 1.0 / counter[i] + len ;
    }
    printf ( "%.0f\n" , floor ( ans ) ) ;
}
