#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
using namespace std ;

const int N = 200005 ;
const int M = N * 2 ;

struct Graph {
    Graph () {}
    Graph ( int u , int v , int w , int n ) : from(u) , to(v) , weight(w) , next(n) {}
    int from , to , next , weight ;
} g[M] ;
int edgeCount ;
int first[N] ;

int n ;

inline void addEdge ( int u , int v , int w ) {
    edgeCount ++ ;
    g[edgeCount] = Graph ( u , v , w , first[u] ) , first[u] = edgeCount ;
    g[M - edgeCount] = Graph ( v , u , w , first[v] ) , first[v] = M - edgeCount ;
}

struct Tree {
    int l , r , lch , rch , min_key , max_key ;
} T[N * 2] ;
int nodeCount , root ;

#define L (T[u].lch)
#define R (T[u].rch)
int keys[N] ;
void build ( int &u , int l , int r ) {
    u = ++ nodeCount ;
    T[u].l = l ;
    T[u].r = r ;
    if ( l == r ) {
        T[u].min_key = T[u].max_key = keys[l] ;
        return ;
    }
    build ( T[u].lch , l , l + r >> 1 ) ;
    build ( T[u].rch , (l + r >> 1) + 1 , r ) ;
    T[u].min_key = min ( T[L].min_key , T[R].min_key ) ;
    T[u].max_key = max ( T[L].max_key , T[R].max_key ) ;
}

/*
void insert ( int u , int pos , int key ) {
    if ( T[u].l == T[u].r ) {
        T[u].min_key = T[u].max_key = key ;
        return ;
    }
    if ( pos < T[R].l ) insert ( L , pos , key ) ;
    else insert ( R , pos , key ) ;
    T[u].min_key = min ( T[L].min_key , T[R].min_key ) ;
    T[u].max_key = max ( T[L].max_key , T[R].max_key ) ;
}
*/

int depth[N] , pos[N] , top[N] , size[N] , father[N] , son[N] , son_weight[N] ;
void dfs ( int u , int key , int weight ) {
    pos[u] = ++ nodeCount ;
    keys[nodeCount] = weight ;
    top[u] = key ;
    if ( son[u] ) 
        dfs ( son[u] , key , son_weight[u] ) ;
    for ( int iter = first[u] ; iter != 0 ; iter = g[iter].next ) {
        int v = g[iter].to ;
        if ( v != father[u] && v != son[u] )
            dfs ( v , v , g[iter].weight ) ;
    }
}

bool vis[N] ;
int q[N] ;
void bfs () {
    q[1] = 1 , vis[1] = true , depth[1] = 1 ;
    int head , tail ;
    for ( head = 1 , tail = 1 ; head <= tail ; ++ head ) {
        int u = q[head] ;
        for ( int iter = first[u] ; iter != 0 ; iter = g[iter].next ) {
            int v = g[iter].to ;
            if ( !vis[v] ) {
                q[++ tail] = v ;
                vis[v] = true ;
                father[v] = u ;
                depth[v] = depth[u] + 1 ;
            }
        }
    }
    for ( int i = tail ; i >= 1 ; -- i ) {
        int u = q[i] ;
        int id = 0 ;
        size[u] = 1 ;
        for ( int iter = first[u] ; iter != 0 ; iter = g[iter].next ) {
            int v = g[iter].to ;
            if ( v != father[u] ) {
                size[u] += size[v] ;
                if ( size[v] > size[id] ) {
                    id = v ;
                    son_weight[u] = g[iter].weight ;
                }
            }
        }
        son[u] = id ;
    }

    nodeCount = 0 ;
    dfs ( 1 , 1 , -1 ) ;
    nodeCount = 0 ;
    build ( root , 1 , n ) ;
/*
    for ( int iter = 1 ; iter <= edgeCount ; ++ iter ) {
        int u = g[iter].from ;
        int v = g[iter].to ;
        if ( depth[u] < depth[v] )
            swap ( u , v ) ;
        insert ( root , pos[u] , g[iter].weight ) ;
    }
*/
}

const int INF = INT_MAX ;
int Min , Max ;
int Q[N * 2] ;
void findKey ( int u , int l , int r ) {
    Q[1] = 1 ;
    for ( int head = 1 , tail = 1 ; head <= tail ; ++ head ) {
        int u = Q[head] ;
        if ( l <= T[u].l && r >= T[u].r ) {
            if ( T[u].min_key < Min ) Min = T[u].min_key ;
            if ( T[u].max_key > Max ) Max = T[u].max_key ;
            continue ;
        }
        // if ( T[u].min_key > Min || T[u].max_key < Max ) continue ;
        if ( l < T[R].l ) Q[++ tail] = L ;
        if ( r > T[L].r ) Q[++ tail] = R ;
    }
}

void find ( int u , int v ) {
    int f1 = top[u] ;
    int f2 = top[v] ;
    Min = INF , Max = -INF ;
    while ( f1 != f2 ) {
        if ( depth[f1] < depth[f2] ) {
            swap ( u , v ) ;
            swap ( f1 , f2 ) ;
        }
        findKey ( root , pos[f1] , pos[u] ) ;
        u = father[f1] ;
        f1 = top[u] ; 
    }
    if ( u == v ) return ;
    if ( depth[u] < depth[v] )
        swap ( u , v ) ;
    findKey ( root , pos[son[v]] , pos[u] ) ;
}

int main() {
    freopen ( "input.txt" , "r" , stdin ) ;
    scanf ( "%d" , &n ) ;
    for ( int i = 1 ; i < n ; ++ i ) {
        int u , v , w ;
        scanf ( "%d%d%d" , &u , &v , &w ) ;
        addEdge ( u , v , w ) ;
        // addEdge ( v , u , w ) ;
    }
    bfs () ;
    int q ;
    scanf ( "%d" , &q ) ;
    while ( q -- ) {
        int u , v ;
        scanf ( "%d%d" , &u , &v ) ;
        if ( u == v ) {
            printf ( "0 0\n" ) ;
            continue ;
        }
        find ( u , v ) ;
        printf ( "%d %d\n" , Min , Max ) ;
    }
}
