#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class TheBoredomDivTwo {
public:
    int find(int, int, int, int);
};

int TheBoredomDivTwo::find(int n, int m, int j, int b) {
    int result = n;
    result += (j > n) + (b > n);
    return result;
}

<%:testing-code%>
//Powered by [KawigiEdit] 2.0!
