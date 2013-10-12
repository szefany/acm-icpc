#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <climits>

#define clr(x) memset ( (x) , 0 , sizeof ( x ) )
#define Mp make_pair
#define Pb push_back
#define Vr vector<int>::iterator

using namespace std ;

template<class T> inline void updateMax ( T &x , T y ) { x = ( x > y ) ? x : y ; }
template<class T> inline void updateMin ( T &x , T y ) { x = ( x < y ) ? x : y ; }

typedef long long LL ;
typedef pair<int, int> Pr ;

const double eps = 1e-6 ;
const int Inf = INT_MAX ;

const int N = 10 ;
const int d[4][2] = { { -1 , 0 } , { 1 , 0 } , { 0 , -1 } , { 0 , 1 } } ;

struct Data {
	Data () {}
	Data ( int x1 , int y1 , int step1 ) : x ( x1 ) , y ( y1 ) , steps ( step1 ) {
		clr ( vis ) ;
	}
	int x , y , steps ;
	bool vis[N][N] ;
} q[N * N * N * N] ;

int n ;
char s[N][N] ;

bool inMap ( int x , int y ) {
	return x >= 1 && x <= n && y >= 1 && y <= n ;
}

bool check ( int len ) {
	int head = 0 , tail = 1 ;
	q[1] = Data ( 1 , 1 , 1 ) ;
	q[1].vis[1][1] = true ;
	while ( head < tail ) {
		head ++ ;
		if ( q[head].steps == len * 2 ) {
			return true ;
		}
		char nextKey = q[head].steps < len ? '(' : ')' ;
		for ( int i = 0 ; i < 4 ; ++i ) {
			int dx = q[head].x + d[i][0] ;
			int dy = q[head].y + d[i][1] ;
			if ( inMap ( dx , dy ) && s[dx][dy] == nextKey && !q[head].vis[dx][dy] ) {
				tail ++ ;
				q[tail] = Data ( dx , dy , q[head].steps + 1 ) ;
				memcpy ( q[tail].vis , q[head].vis , sizeof ( q[head].vis ) ) ;
				q[tail].vis[dx][dy] = true ;
			}
		}
	}
	return false ;
}

int main() {
	freopen ( "hshoe.in" , "r" , stdin ) ;
	freopen ( "hshoe.out" , "w" , stdout ) ;
	scanf ( "%d" , &n ) ;
	for ( int i = 1 ; i <= n ; ++i )
		scanf ( "%s" , s[i] + 1 ) ;
	if ( s[1][1] == ')' ) {
		printf ( "0\n" ) ;
		return 0 ;
	}
	int found = 0 ;
	for ( int len = n * n / 2 ; len >= 1 ; --len ) {
		if ( check ( len ) ) {
			found = len ;
			break ;
		}
	}
	printf ( "%d\n" , found * 2 ) ;
	return 0 ;
}
