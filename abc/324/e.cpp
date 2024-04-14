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
    ll N; string T; cin >> N >> T;
    ll TS = T.size();

    vector<ll> dp1(N); // Tの前半何文字までいける？
    vector<ll> dp2(N); // Tの後半何文字までいける？
    vector<string> S(N);
    for(ll i=0; i<N; i++) {
        cin >> S[i];

        // dp1
        {
            ll ti = 0;
            for(ll j=0; j<(ll)S[i].size(); j++) {
                if (T[ti] == S[i][j]) {
                    ti++;
                    if (ti == (ll)T.size()) break;
                }
            }
            dp1[i] = ti;
        }

        // dp2
        {
            ll ti=(ll)T.size()-1;
            ll num = 0;
            for(ll j=(ll)S[i].size()-1; j>=0; j--) {
                if (T[ti] == S[i][j]) {
                    ti--;
                    num++;
                    if (ti == -1) break;
                }
            }
            dp2[i] = num;
        }
    }

    ll ans = 0;
    sort(dp1.begin(), dp1.end());
    sort(dp2.begin(), dp2.end());
    for(ll i=0; i<(ll)dp1.size(); i++) {
        ll j = lower_bound(dp2.begin(), dp2.end(), TS-dp1[i]) - dp2.begin();
        ans += (N - j);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}