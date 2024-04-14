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
    ll N; cin >> N;

    // 素因数分解する
    map<ll,ll> mp;
    while(N%2 == 0) {
        mp[2]++;
        N /= 2;
    }
    while(N%3 == 0) {
        mp[3]++;
        N /= 3;
    }

    if (N >= 2) {
        cout << "No" << endl;
    }
    else {
        cout << "Yes" << endl;
    }
}


int main() {
    solve();
    return 0;
}