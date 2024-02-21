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
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    sort(A.begin(), A.end());

    // 正と負に分ける
    vector<ll> plus; // 正の数列(0含む)
    vector<ll> minus; // 負の数列
    for(ll i=0; i<N; i++) {
        if (A[i] >= 0) plus.push_back(A[i]);
        else minus.push_back(A[i]);
    }

    // 積がx以下となるものはK個以上か？
    auto f = [&](ll x) {
        ll cnt = 0; // 個数
        if (x >= 0) {
            // 負x負の探索
            for(ll i=0; i<(ll)minus.size(); i++) {// 負を固定
                ll idx = lower_bound(minus.begin(), minus.end(), x/minus[i]) - minus.begin();
                if (idx > i) cnt += minus.size() - idx;
                else cnt += minus.size() - i - 1;
            }

            // 正x正の探索
            for(ll i=0; i<(ll)plus.size(); i++) {// 正を固定
                if (plus[i] != 0) {
                    ll idx = upper_bound(plus.begin(), plus.end(), x/plus[i]) - plus.begin();
                    if (idx > i) cnt += idx - i - 1;
                }
                else {
                    cnt += plus.size() - i - 1;
                }
            }

            // 負x正の探索
            cnt += (ll)minus.size() * plus.size();
        }
        else { // xが負の場合
            // 負x正の探索
            for(ll i=0; i<(ll)minus.size(); i++) {// 負を固定
                ll idx =
                plus.begin(), plus.end(), intceil(-x,-minus[i])) - plus.begin();
                cnt += (ll)plus.size() - idx;
            }
        }
        return cnt >= K;
    };

    ll l=-1e18-1, r=1e18+1;
    while(r-l != 1) {
        ll mid = (l+r)/2;
        if (f(mid)) r = mid;
        else l = mid;
    }
    if (f(l)) cout << l << endl;
    else cout << r << endl;
}


int main() {
    solve();
    return 0;
}