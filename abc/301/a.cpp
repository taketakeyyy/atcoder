#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    string S; cin >> S;
    ll taka=0, aoki=0;
    for(ll i=0; i<N; i++) {
        if (S[i] == 'T') taka++;
        else aoki++;
    }

    if (taka == aoki) {
        ll taka2=0, aoki2=0;
        for(ll i=0; i<N; i++) {
            if (S[i] == 'T') taka2++;
            else aoki2++;
            if (taka == taka2) {
                cout << "T" << endl;
                return;
            }
            if (aoki == aoki2) {
                cout << "A" << endl;
                return;
            }
        }
    }
    else {
        if (taka > aoki) {
            cout << "T" << endl;
            return;
        }
        else {
            cout << "A" << endl;
            return;
        }
    }
}


int main() {
    solve();
    return 0;
}