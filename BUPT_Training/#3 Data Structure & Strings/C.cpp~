#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstring>
#include <map>
#include <cstdlib>
using namespace std ;

const int N = 1005 ;

struct Oper {
    int a , b , x , y , h , key ;
    void input () {
        scanf ( "%d%d%d%d%d" , &a , &b , &h , &x , &y ) ;
    }
    bool intersect ( const Oper &other ) {
        return x < other.x + other.a && y < other.y + other.b && x + a > other.x && y + b > other.y ;
    }
} C[N] ;

int n , m , operCount ;

int main() {
    while ( scanf ( "%d%d%d" , &n , &m , &operCount ) != EOF ) {
        for ( int i = 1 ; i <= operCount ; ++ i ) {
            C[i].input () ;
        }
        int ans = 0 ;
        for ( int i = 1 ; i <= operCount ; ++ i ) {
            int temp = 0 ;
            for ( int j = 1 ; j < i ; ++ j ) {
                if ( C[i].intersect ( C[j] ) && C[j].key > temp )
                    temp = C[j].key ;
            }
            C[i].key = temp + C[i].h ;
            if ( C[i].key > ans )
                ans = C[i].key ;
        }
        printf ( "%d\n" , ans ) ;
    }
}
