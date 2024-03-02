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

    ll ans = 1;
    for(ll i=1; i*i*i<=N; i++) {
        string s = to_string(i*i*i);

        // 回分判定
        bool is_kaibun = true;
        ll l=0, r=s.size()-1;
        while(l <= r) {
            if (s[l]==s[r]) {
                l++; r--;
                continue;
            }
            is_kaibun = false;
            break;
        }
        if (is_kaibun) {
            ans = i*i*i;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}