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

const int N = 100005 ;

char s[N] , s1[N] ;
int L[N] , R[N] ;
int len ;

int trans ( char ch , int type ) {
	if ( type == 0 ) return ch == '(' ? 1 : -1 ;
	return ch == ')' ? 1 : -1 ;
}

bool check() {
	int tail = 0 ;
	for ( int i = 0 ; i < len ; ++i ) {
		if ( s[i] == '(' ) s1[++tail] = '(' ;
		else if ( tail > 0 && s1[tail] == '(' ) tail -- ;
		else {
			tail = 1 ;
			break ;
		}
	}
	return tail == 0 ;
}

int main() {
	freopen ( "typo.in" , "r" , stdin ) ;
	freopen ( "typo.out" , "w" , stdout ) ;
	scanf ( "%s" , s ) ;
	len = strlen ( s ) ;
	if ( s[0] == ')' ) {
		s[0] = '(' ;
		bool flag = check() ;
		printf ( "%d\n" , flag ? 1 : 0 ) ;
		return 0 ;
	}
	L[0] = trans ( s[0] , 0 ) ;
	for ( int i = 1 ; i < len ; ++i ) {
		L[i] = L[i - 1] + trans ( s[i] , 0 ) ;
	}
	if ( s[len - 1] == '(' ) {
		s[len - 1] = ')' ;
		bool flag = check() ;
		printf ( "%d\n" , flag ? 1 : 0 ) ;
		return 0 ;
	}
	int first = -1 ;
	R[len - 1] = trans ( s[len - 1] , 1 ) ;
	for ( int i = len - 2 ; i >= 0 ; --i ) {
		R[i] = R[i + 1] + trans ( s[i] , 1 ) ;
		if ( R[i] == -1 ) {
			if ( first == -1 ) first = i ;
		}
	}
	/*
	for ( int i = 0 ; i < len ; ++i ) cout << L[i] << "  " ; cout << endl ;
	for ( int i = 0 ; i < len ; ++i ) cout << R[i] << " " ; cout << endl ;
	*/
	int ans = 0 ;
	for ( int i = 0 ; i < len ; ++i ) {
		if ( first != -1 && i < first ) continue ;
		if ( s[i] == '(' && L[i] - 3 == R[i] ) ans ++ ;
		if ( s[i] == ')' && L[i] + 3 == R[i] ) ans ++ ;
		if ( L[i] == -1 ) break ;
	}
	printf ( "%d\n" , ans ) ;
	return 0 ;
}
