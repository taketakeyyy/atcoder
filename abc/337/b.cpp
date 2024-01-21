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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    string S; cin >> S;
    ll step = -1;
    for(ll i=0; i<(ll)S.size(); i++) {
        if (step == -1) {
            if (S[i]=='A') {
                step = 0; continue;
            }
            if (S[i]=='B') {
                step = 1; continue;
            }
            if (S[i]=='C') {
                step = 2; continue;
            }
        }
        else if (step == 0) {
            if (S[i]=='A') continue;
            if (S[i]=='B') {
                step = 1; continue;
            }
            else {
                step = 2; continue;
            }
        }
        else if (step == 1) {
            if (S[i]=='B') continue;
            if (S[i]=='C') {
                step = 2; continue;
            }
            else {
                cout << "No" << endl;
                return;
            }
        }
        else {
            if (S[i]=='C') continue;
            else {
                cout << "No" << endl;
                return;
            }
        }
    }
    cout << "Yes" << endl;
}


int main() {
    solve();
    return 0;
}