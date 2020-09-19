#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    string S;
    cin >> S;
    if (S.at(S.size()-1) != 's') {
        cout << S << "s" << endl;
    }
    else {
        cout << S << "es" << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}