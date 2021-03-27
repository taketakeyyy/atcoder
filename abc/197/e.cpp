#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N; cin >> N;
    // ボールを回収する方針は、
    // (1) 現在地より右のすべてのボールを回収してから、左のボールを回収する
    // (2) 現在地より左のずべてのぼーるを回収してから、右のボールを回収する
    // の2通り
    // この2通りでDP？
    // dp[i][op] := 色iを回収する際に、op=0(左右)の順で回収するパターンと、op=1(右左)の順で回収するパターンの、時間の最小値と現在地座標
    vector<vector<ll>> cords(N+1);  // cords[i] := 色iのボールの最小座標と最大座標
    for(int i=1; i<N+1; i++) {
        ll x, c; cin >> x >> c;
        cords[c].push_back(x);
    }
    for(int i=1; i<N+1; i++) {
        sort(cords[i].begin(), cords[i].end());
    }

    vector<vector<pair<ll,ll>>> dp(N+1, vector<pair<ll,ll>>(2, make_pair(INF, 0)));
    dp[0][0] = make_pair(0,0);
    dp[0][1] = make_pair(0,0);
    for(int i=1; i<N+1; i++) {
        if (cords[i].size()==0) {
            dp[i][0] = dp[i-1][0];
            dp[i][1] = dp[i-1][1];
            continue;
        }
        ll mn = cords[i][0];
        ll mx = cords[i][cords[i].size()-1];

        ll x0 = dp[i-1][0].second;
        ll x1 = dp[i-1][1].second;
        ll cost0 = dp[i-1][0].first;
        ll cost1 = dp[i-1][1].first;
        // 左右の順で回収するパターン
        ll new0 = cost0+abs(mn-x0)+abs(mx-mn);
        ll new1 = cost1+abs(mn-x1)+abs(mx-mn);
        if (new0 < new1) {
            dp[i][0].first = new0;
        }
        else {
            dp[i][0].first = new1;
        }
        dp[i][0].second = mx;
        // 右左の順で回収するパターン
        new0 = cost0+abs(mx-x0)+abs(mx-mn);
        new1 = cost1+abs(mx-x1)+abs(mx-mn);
        if (new0 < new1) {
            dp[i][1].first = new0;
        }
        else {
            dp[i][1].first = new1;
        }
        dp[i][1].second = mn;
    }
    ll ans = dp[N][0].first + abs(dp[N][0].second - 0);
    ans = min(ans, dp[N][1].first + abs(dp[N][1].second - 0));
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}