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
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;


void solve() {
    ll N; cin >> N;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }
    ll totalB = accumulate(B.begin(), B.end(), 0LL);

    if (totalB%3 != 0) {
        cout << -1 << endl;
        return;
    }

    // dp[i][x][y] := 人iまで見て、チーム1の強さがx、チーム2の強さがyのときの、最小コスト
    ll AVE = totalB/3;
    vector dp(AVE+1, vector(AVE+1, INF)); // インライン化
    dp[0][0] = 0;
    for(ll i=0; i<N; i++) {
        vector newdp(AVE+1, vector(AVE+1, INF));

        // 人iをチーム1にするとき
        for(ll x=0; x<=AVE; x++) {
            if (x+B[i] > AVE) break;
            for(ll y=0; y<=AVE; y++) {
                if (dp[x][y] == INF) continue;
                if (A[i]==1) chmin(newdp[x+B[i]][y], dp[x][y]);
                else chmin(newdp[x+B[i]][y], dp[x][y]+1);
            }
        }

        // 人iをチーム2にするとき
        for(ll y=0; y<=AVE; y++) {
            if (y+B[i] > AVE) break;
            for(ll x=0; x<=AVE; x++) {
                if (dp[x][y] == INF) continue;
                if (A[i]==2) chmin(newdp[x][y+B[i]], dp[x][y]);
                else chmin(newdp[x][y+B[i]], dp[x][y]+1);
            }
        }

        // 人iをチーム3にするとき
        for(ll x=0; x<=AVE; x++) {
            for(ll y=0; y<=AVE; y++) {
                if (dp[x][y] == INF) continue;
                if (A[i]==3) chmin(newdp[x][y], dp[x][y]);
                else chmin(newdp[x][y], dp[x][y]+1);
            }
        }

        swap(dp, newdp);
    }

    // 答え
    if (dp[AVE][AVE] == INF) cout << -1 << endl;
    else cout << dp[AVE][AVE] << endl;
}


int main() {
    solve();
    return 0;
}