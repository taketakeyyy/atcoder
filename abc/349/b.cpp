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
    map<char,ll> mp;
    for(char ch: S) {
        mp[ch]++;
    }

    map<ll,ll> mp2;
    for(auto[key, val]: mp) {
        mp2[val]++;
    }

    bool is_ok = true;
    for(auto[key, val]: mp2) {
        if(val==0 or val==2) continue;
        is_ok = false;
        break;
    }
    if(is_ok) cout << "Yes" << endl;
    else cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}