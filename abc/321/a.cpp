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
    string N; cin >> N;
    if (N.size() == 1) {
        cout << "Yes" << endl;
        return;
    }
    ll pre_n = N[0]-'0';
    for(ll i=1; i<N.size(); i++) {
        ll n = N[i]-'0';
        if (n < pre_n) {
            pre_n = n;
            continue;
        }
        cout << "No" << endl;
        return;
    }
    cout << "Yes" << endl;
}


int main() {
    solve();
    return 0;
}