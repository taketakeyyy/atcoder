#define _USE_MATH_DEFINES  // M_PI等のフラグ

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>
#include <list>

#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))

using namespace std;


void solve(){
    using pi = pair<int, int>;
    int N;
    cin >> N;
    int a, b;
    vector<pi> ps;
    for (int i=0; i<N; i++) {
        cin >> a >> b;
        pi p = make_pair(b, a);
        ps.push_back(p);
    }

    sort(ps.begin(), ps.end());

    for (auto p : ps) {
        int a, b;
        tie(b, a) = p;
        cout << a << " " << b << endl;
    }
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}