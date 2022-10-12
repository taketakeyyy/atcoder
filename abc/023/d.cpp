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


// 高度xまでに風船を全て割ることができるか二分探索
void solve() {
    ll N; cin >> N;
    vector<pair<ll,ll>> baloons(N);
    for(ll i=0; i<N; i++) {
        ll h, s; cin >> h >> s;
        baloons[i] = {h,s};
    }

    // 二分探索用ラムダ式O(N logN)
    auto f = [&baloons, &N](ll x) {
        vector<ll> times(N);  // times[i] := 時刻iまでに割れなければならない
        for(ll i=0; i<N; i++) {
            auto[h, s] = baloons[i];
            if (h > x) return false;
            times[i] = (x-h)/s;  // この時刻までなら待てる
        }

        sort(times.begin(), times.end());

        for(ll i=0; i<N; i++) {
            if (times[i] >= i) continue;
            return false;
        }
        return true;
    };

    // 二分探索O(log(right) NlogN)
    ll left = 1;
    ll right = 1e9 + 1e9*N + 1;  // 全ての風船がh=1e9、s=1e9のとき
    while(right-left != 1) {
        ll mid = (right+left)/2;

        if (f(mid)) right = mid;
        else left = mid;
    }
    if (f(left))  cout << left << endl;
    else cout << right << endl;
}


int main() {
    solve();
    return 0;
}