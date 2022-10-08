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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    vector<ll> odds, evens;

    // 2和が偶数になるのは、
    // * 偶数 + 偶数
    // * 奇数 + 奇数
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        if (a%2 == 0) evens.push_back(a);
        else odds.push_back(a);
    }
    sort(evens.begin(), evens.end());
    sort(odds.begin(), odds.end());
    reverse(evens.begin(), evens.end());
    reverse(odds.begin(), odds.end());

    ll ans1 = -1;
    if (evens.size() >= 2) {
        ans1 = evens[0] + evens[1];
    }
    ll ans2 = -1;
    if (odds.size() >= 2) {
        ans2 = odds[0] + odds[1];
    }

    if (ans1==-1 && ans2==-1) {
        cout << -1 << endl;
    }
    else {
        cout << max(ans1, ans2) << endl;
    }

}


int main() {
    solve();
    return 0;
}