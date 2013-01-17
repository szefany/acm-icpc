#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
using namespace std ;

const int N = 5005 ;

struct Line {
    int x1 , y1 , x2 , y2 ;
    inline void input () {
        scanf ( "%d%d%d%d" , &x1 , &y1 , &x2 , &y2 ) ;
    }
} lines[N] ;

struct Point {
    Point () {}
    Point ( int x1 , int y1 ) : x(x1) , y(y1) {}
    int x , y ;
} points[N] , total[N] ;

int polyCount ;
struct Polygon {
    vector<Point> points ;
    bool inPolygon ( Point p ) {
        int num[2] = { 0 , 0 } ;
        for ( int i = 1 ; i < points.size() ; i ++ ) {
            Point last = points[i - 1] ;
            Point now = points[i] ;
            if ( (last.y < p.y && now.y >= p.y) || (now.y < p.y && last.y >= p.y) ) {
                double x = (p.y - last.y) * 1.0 * (now.x - last.x) / (now.y - last.y) + last.x ;
                if ( x < p.x ) num[0] ++ ;
                else num[1] ++ ;
            }
        }
        if ( (num[0] & 1) && (num[1] & 1) ) return 1 ;
        return 0 ;
    }
} polygons[N] ;

int pointCount ;
map<pair<int, int>, int> allPoints ;
int findIndex ( int x , int y ) {
    if ( allPoints.find ( make_pair ( x , y ) ) == allPoints.end() ) {
        allPoints[ make_pair ( x , y ) ] = ++ pointCount ;
        total[pointCount] = Point ( x , y ) ;
    }
    return allPoints[ make_pair ( x , y ) ] ;
}

int n , m ;
bool vis[N] ;
int path[N] ;
vector<int> links[N] ;
void dfs ( int u , int depth , int pre ) {
    path[depth] = u ;
    if ( vis[u] ) {
        polyCount ++ ;
        for ( int i = 1 ; i <= depth ; i ++ )
            polygons[polyCount].points.push_back ( total[ path[i] ] ) ;
        return ;
    }
    vis[u] = 1 ;
    for ( int i = 0 ; i < links[u].size() ; ++i ) {
        if ( links[u][i] != pre ) {
            dfs ( links[u][i] , depth + 1 , u ) ;
            break ;
        }
    }
}

const int P = 9973 ;
const int MAGIC = 9999991 ;
typedef pair<int, unsigned long long> Hash ;
Hash Pow[10000] ;
map<Hash, int> ans ;

int main() {
    freopen ( "crazy.in" , "r" , stdin ) ;
    freopen ( "crazy.out" , "w" , stdout ) ;
    scanf ( "%d%d" , &m , &n ) ;
    for ( int i = 1 ; i <= m ; ++i ) {
        int x1 , y1 , x2 , y2 ;
        scanf ( "%d%d%d%d" , &x1 , &y1 , &x2 , &y2 ) ;
        int u = findIndex ( x1 , y1 ) ;
        int v = findIndex ( x2 , y2 ) ;
        links[u].push_back ( v ) ;
        links[v].push_back ( u ) ;
    }
    for ( int i = 1 ; i <= n ; ++i ) {
        scanf ( "%d%d" , &points[i].x , &points[i].y ) ;
    }
    for ( int i = 1 ; i <= pointCount ; ++i ) {
        if ( !vis[i] ) {
            dfs ( i , 1 , -1 ) ;
        }
    }
    Pow[0] = make_pair ( 1 , 1 ) ;
    for ( int i = 1 ; i <= 10000 ; i ++ ) {
        Pow[i].first = ((long long)Pow[i - 1].first * P) % MAGIC ;
        Pow[i].second = Pow[i - 1].second * P ;
    }
    for ( int i = 1 ; i <= n ; ++i ) {
        Hash hash ;
        for ( int j = 1 ; j <= polyCount ; ++j ) {
            if ( polygons[j].inPolygon ( points[i] ) ) {
                hash.first = ( hash.first + Pow[j].first ) % MAGIC ;
                hash.second = hash.second + Pow[j].second ;
            }
        }
        ans[hash] ++ ;
    }
    int x = 0 ;
    for ( map<Hash, int>::iterator iter = ans.begin() ; iter != ans.end() ; iter ++ ) {
        if ( (*iter).second > x ) {
            x = (*iter).second ;
        }
    }
    cout << x << endl ;
}
