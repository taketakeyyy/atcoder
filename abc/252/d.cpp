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


void solve() {
    /* 真ん中を決め打ちする天才解法 */
    ll N; cin >> N;
    vector<ll> A;
    set<ll> st;
    map<ll,ll> mp;  // 度数
    for(ll i=0; i<N; i++) {
        ll a;
        cin >> a;
        if (st.count(a)) {
            ;
        }
        else {
            A.push_back(a);
        }
        st.insert(a);
        mp[a]++;
    }
    sort(A.begin(), A.end());

    // 累積和作成
    vector<ll> r(A.size()+1, 0);
    for (ll i=1; i<A.size()+1; i++) {
        r[i] = r[i-1] + mp[A[i-1]];
    }

    ll ans = 0;
    for(ll j=1; j<A.size()-1; j++) {
        ans += mp[A[j]] * r[j-1+1] * (r[A.size()] - r[j+1]);
    }

    cout << ans << endl;
}

void solve2() {
    /* dp使う解法 */
    ll N; cin >> N;
    vector<ll> A;
    map<ll,ll> mp;  // 度数
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        if (!mp.count(a)) {
            A.push_back(a);
        }
        mp[a]++;
    }

    // dp[i][j] := A[i]のi番目まで見て、j個選んでるときの場合の数
    ll NA = A.size();
    vector<vector<ll>> dp(NA, vector<ll>(4, 0));
    dp[0][1] = mp[A[0]];
    for(ll i=1; i<NA; i++) {
        // 選ぶ場合
        dp[i][1] = mp[A[i]];
        dp[i][2] = dp[i-1][1] * mp[A[i]];
        dp[i][3] = dp[i-1][2] * mp[A[i]];

        // 選ばない場合
        dp[i][1] += dp[i-1][1];
        dp[i][2] += dp[i-1][2];
        dp[i][3] += dp[i-1][3];
    }

    cout << dp[NA-1][3] << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}