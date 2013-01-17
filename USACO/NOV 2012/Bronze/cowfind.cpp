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

const int N = 50005 ;

char s[N] ;

int main() {
	freopen ( "cowfind.in" , "r" , stdin ) ;
	freopen ( "cowfind.out" , "w" , stdout ) ;
	scanf ( "%s" , s ) ;
	int len = strlen ( s ) ;
	int current = 0 , ans = 0 ;
	for ( int i = 0 ; i < len - 1 ; ++i ) {
		if ( s[i] == '(' && s[i + 1] == '(' )
			current ++ ;
		else if ( s[i] == ')' && s[i + 1] == ')' ) 
			ans += current ;
	}
	printf ( "%d\n" , ans ) ;
	return 0 ;
}
