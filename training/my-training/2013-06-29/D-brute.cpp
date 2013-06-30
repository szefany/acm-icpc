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

struct BigInteger {
    /*
        注意高精度乘法压位时不应压太多，中间乘法可能会爆int.
    */
    #define L result.length
    static const int N = 105 ;
    static const int bits = 10000 ;
    bool negative ;
    int length ;
    int A[N] ;

    /*  procedure print ;
     *  operator +, -, *, /, <, >, <=, >=, ==, mod
     */
     
    BigInteger() {
        negative = false ;
        length = 1 ;
        clr ( A ) ;
    }
    
    BigInteger ( const string& s ) {
        length = 0 ;
        clr ( A ) ;
        int pivot ;
        if ( s[0] == '-' ) {
            negative = true , pivot = 1 ;
        }
        else {
            negative = false , pivot = 0 ;
        }
        for ( int i = s.size() - 1 ; i >= pivot ; ) {
            length ++ ;
            for ( int x = 1 ; x * 10 <= bits && i >= pivot ; --i , x *= 10 )
                A[length] += ( s[i] - 48 ) * x ;
        }
    }
    
    BigInteger ( const int &number ) {
        stringstream buffer ;
        string s ;
        buffer << number ;
        buffer >> s ;
        (*this) = BigInteger ( s ) ;
    }
    
    inline void print() {
        if ( negative ) printf ( "-" ) ;
        for ( int i = length ; i >= 1 ; --i ) {
            if ( i != length ) {
                for ( int x = max ( A[i] , 1 ) ; x * 10 <= bits ; x *= 10 )
                    printf ( "0" ) ;
                if ( A[i] ) printf ( "%d" , A[i] ) ;
            }
            else printf ( "%d" , A[i] ) ;
        }
        printf ( "\n" ) ;
    }
    
    inline void addShift() {
        for ( int i = 1 ; i <= length ; ++i )
            if ( A[i] >= bits ) {
                A[i+1] += A[i] / bits ;
                A[i] %= bits ;
                if ( i == length ) length ++ ;
            }
        while ( A[length] == 0 && length > 1 ) length -- ;
    }
    
    inline void delShift ( const BigInteger &D ) {
        for ( int i = 1 ; i <= length ; ++i ) {
            A[i] -= D.A[i] ;
            if ( A[i] < 0 ) {
                int delta = ( - A[i] + bits - 1 ) / bits ;
                A[i] += delta * bits ;
                A[i+1] -= delta ;
            }
        }
        while ( A[length] == 0 && length > 1 ) length -- ;
    }

    inline bool operator < ( const BigInteger &B ) {
        if ( length < B.length ) return true ;
        if ( length > B.length ) return false ;
        for ( int i = length ; i >= 1 ; --i )
            if ( A[i] < B.A[i
            ] ) return true ;
        return false ;
    }
    
    inline bool operator == ( const BigInteger &B ) {
        if ( length != B.length ) return false ;
        for ( int i = 1 ; i <= length ; ++i )
            if ( A[i] != B.A[i] ) return false ;
        return true ;
    }
    
    inline bool operator > ( BigInteger &B ) {
        // return ( !( (*this) < B ) ) && ( !( (*this) == B ) ) ;
        return B < (*this) ;
    }
        
    BigInteger operator + ( const BigInteger &B ) {
        BigInteger result ;
        L = max ( length , B.length ) ;
        for ( int i = 1 ; i <= L ; ++i )
            result.A[i] = A[i] + B.A[i] ;
        result.addShift() ;
        return result ;
    }
    
    BigInteger& operator += ( const BigInteger &B ) {
        length = max ( length , B.length ) ;
        for ( int i = 1 ; i <= length ; ++i )
            A[i] = A[i] + B.A[i] ;
        addShift() ;
        return *this ;
    }

    BigInteger operator - ( const BigInteger &B ) {
        BigInteger result , D ;
        if ( *this < B ) {
            result = B , D = *this ;
            result.negative = true ;
        }
        else {
            result = *this , D = B ;
            result.negative = false ;
        }
        result.delShift ( D ) ;
        return result ;
    }
    
    BigInteger& operator -= ( const BigInteger &B ) {
        BigInteger D ;
        if ( *this < B ) {
            D = *this , *this = B ;
            negative = true ;
        }
        else {
            D = B ;
            negative = false ;
        }
        delShift ( D ) ;
        return *this ;
    }
    
    BigInteger operator * ( const int &c ) {
        BigInteger result ;
        L = length ;
        for ( int i = 1 ; i <= L ; ++i )
            result.A[i] = A[i] * c ;
        result.addShift() ;
        return result ;
    }

    BigInteger& operator *= ( const int &c ) {
        for ( int i = 1 ; i <= length ; ++i )
            A[i] = A[i] * c ;
        addShift() ;
        return *this ;
    }
    
    inline BigInteger operator * ( const BigInteger &B ) {
        BigInteger result ;
        int temp ;
        for ( int i = 1 ; i <= length ; ++i )
            for ( int j = 1 ; j <= B.length ; ++j ) {
                temp = A[i] * B.A[j] + result.A[ i + j - 1 ] ;
                if ( temp >= bits ) {
                    result.A[ i + j ] += temp / bits ;
                    temp %= bits ;
                }
                result.A[ i + j - 1 ] = temp ;
            }
        result.negative = ( negative != B.negative ) ;
        L = length + B.length + 1 ;
        result.addShift() ;
        return result ;
    }
    
    inline BigInteger& operator *= ( const BigInteger &B ) {
        (*this) = (*this) * B ;
        return *this ;
    }        
};

int n, m;

const int N = 5000 + 10;

int a[N], b[N];
long long sigma[N][N];

int main() {
    scanf("%d%d", &n, &m);
    /*
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
    }
    for (int i = 2; i <= n; ++ i) {
        scanf("%d", b + i);
    }
    */
    for (int i = 1; i <= n; ++ i) {
        sigma[i][1] = 1;
    }
    for (int i = 1; i <= m; ++ i) {
        sigma[1][i] = 1;
    }
    for (int i = 2; i <= n; ++ i) {
        for (int j = 2; j <= m; ++ j) {
            sigma[i][j] = sigma[i - 1][j] + sigma[i][j - 1];
        }
    }
    std::cout << sigma[n][m] << std::endl;
}
