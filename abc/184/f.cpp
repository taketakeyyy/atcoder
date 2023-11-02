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


// dp[i][t] := 問題をi番目まで見て、時間の総和がtを作れるかどうか
// 上記はO(NT)
// dp[state] := 解いた問題の状態がstateのときの、時間の総和
// 上記はO(2^N)
// 上記はNを半分にしたら解けそうなので、半分全列挙で解く
void solve() {
    ll N, T; cin >> N >> T;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // P := 配列Bから作ることができる時間の総和のリスト
    auto genP = [&](ll l, ll r) -> vector<ll> {
        // Bを作る
        vector<ll> B;
        for(ll i=l; i<r; i++) B.push_back(A[i]);
        ll NB = B.size();

        // Bをbit全探索してPを作る
        vector<ll> P;
        for(ll state=0; state<(1<<NB); state++) {
            ll total = 0;
            for(ll d=0; d<NB; d++) {
                if (state>>d&1) {
                    total += B[d];
                }
            }
            if (total <= T) P.push_back(total);
        }
        sort(P.begin(), P.end());
        return P;
    };
    auto P1 = genP(0, N/2); // 前半部分
    auto P2 = genP(N/2, N); // 後半部分

    // 時間の総和の最大値を探す
    ll ans = 0;
    for(ll p1: P1) { // 高々2^20回
        ll target = T-p1;
        if(target < P2[0]) continue;
        auto it = upper_bound(P2.begin(), P2.end(), target); // O(log|P2|)
        it--;
        ans = max(ans, p1 + (*it));
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}