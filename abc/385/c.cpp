#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
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
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }


void solve() {
    ll N; cin >> N;
    vector<ll> H(N);
    for(ll i=0; i<N; i++) cin >> H[i];

    vector done(N, vector(N, false));
    ll ans = 1;
    for(ll i=0; i<N; i++) {
        for(ll step=1; step<N; step++) {
            if (done[i][step]) continue;
            done[i][step] = true;

            ll total = 1;
            for(ll j=i+step; j<N; j+=step) {
                if (H[j]==H[j-step]) {
                    done[j][step] = true;
                    total++;
                    continue;
                }
                break;
            }
            chmax(ans, total);
        }
    }
    cout << ans << endl;
}


void solve2() {
    ll N; cin >> N;
    vector<ll> H(N);
    for(ll i=0; i<N; i++) cin >> H[i];

    ll ans = 1;
    for(ll i=0; i<N; i++) {
        for(ll step=1; step<N; step++) {
            ll total = 1;
            for(ll j=i+step; j<N; j+=step) {
                if (H[j] == H[j-step]) {
                    total++;
                    continue;
                }
                break;
            }
            chmax(ans, total);
        }
    }
    cout << ans << endl;
}

void solve3() {
    ll N; cin >> N;
    vector<ll> H(N);
    for(ll i=0; i<N; i++) cin >> H[i];

    // dp[i][step] := iまで見て、ステップ数がstepのときの、最大値
    vector dp(N, vector(N, 1LL));
    for(ll i=0; i<N; i++) {
        for(ll step=1; step<N; step++) {
            if (i-step < 0) break;
            if (H[i] == H[i-step]) {
                chmax(dp[i][step], dp[i-step][step]+1);
            }
        }
    }

    ll ans = 1;
    for(ll i=0; i<N; i++) {
        for(ll step=1; step<N; step++) {
            chmax(ans, dp[i][step]);
        }
    }
    cout << ans << endl;
}

int main() {
    solve();
    // solve2();
    // solve3();
    return 0;
}