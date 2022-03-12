#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N, X; cin >> N >> X;
    string S; cin >> S;

    // RU
    // LU
    // のようなものは、移動しない扱いできる
    string T = "";
    ll u = 0;
    for(ll i=S.size()-1; i>=0; i--) {
        if (S[i] == 'U') {
            u++; continue;
        }
        else {
            if (u >= 1) {
                u--; continue;
            }
            else {
                T = S[i] + T;
                continue;
            }
        }
    }
    for(ll i=0; i<u; i++) {
        T = "U" + T;
    }

    // cout << T << endl;

    for(ll i=0; i<T.size(); i++) {
        if (T[i] == 'U') {
            X /= 2;
        }
        else if (T[i] == 'L') {
            X *= 2;
        }
        else {
            X = X*2+1;
        }
    }

    cout << X << endl;
}


int main() {
    solve();
    return 0;
}