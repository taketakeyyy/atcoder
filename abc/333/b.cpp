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
    string T; cin >> T;
    ll s0 = S[0]-'A';
    ll s1 = S[1]-'A';
    ll t0 = T[0]-'A';
    ll t1 = T[1]-'A';

    auto calc_len = [&](ll a, ll b) {
        ll mx = max(a,b);
        ll mn = min(a,b);
        ll len1 = mx-mn;
        ll len2 = (5-mx)+mn;
        return min(len1, len2);
    };

    ll len1 = calc_len(s0, s1);
    ll len2 = calc_len(t0, t1);
    if (len1 == len2) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main() {
    solve();
    return 0;
}