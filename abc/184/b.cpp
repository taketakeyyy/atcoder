#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    int N, X;
    string S;
    cin >> N >> X;
    cin >> S;

    for (char c : S) {
        if (c=='o') {
            X++;
        }
        else {
            if (X==0) continue;
            X--;
        }
    }
    cout << X << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}