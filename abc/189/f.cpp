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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, M, K; cin >> N >> M >> K;
    set<ll> furidashi;
    for(ll i=0; i<K; i++) {
        ll a; cin >> a;
        furidashi.insert(a);
    }

    // ゴール不可能か？
    ll seq = 0; // 「ふりだしに戻る」マスの連続回数
    for(ll i=0; i<=N; i++) {
        if (furidashi.count(i)) {
            seq++;
            if (seq == M) {
                cout << -1 << endl;
                return;
            }
            continue;
        }
        seq = 0;
    }

    // dp[i] := 現在iマスにいる状態で、終了するまでに回すルーレットの回数の期待値E[i]
    // 以下ではE[0] = xとおいている
    vector<double> dpa(N+1, 0); // dpa[i] := E[i]のときのax+bのa
    vector<double> dpb(N+1, 0); // dpb[i] := E[i]のときのax+bのb
    vector<double> ruia(N+2, 0); // ruia[i] := dpa[N]~dpa[i]の累積和
    vector<double> ruib(N+2, 0); // ruib[i] := dpb[N]~dpb[i]の累積和
    for(ll i=N-1; i>=0; i--) {
        if (furidashi.count(i)) {
            // ふりだしマスのとき
            dpa[i] = 1;
            dpb[i] = 0;
            ruia[i] = ruia[i+1] + dpa[i];
            ruib[i] = ruib[i+1] + dpb[i];
            continue;
        }

        // ふりだしマスでないとき
        const static double p = (double)1.0/M; // 遷移確率
        if (i+1+M <= N) {
            dpa[i] = p*(ruia[i+1]-ruia[i+1+M]);
            dpb[i] = 1 + p*(ruib[i+1]-ruib[i+1+M]);
        }
        else {
            dpa[i] = p*ruia[i+1];
            dpb[i] = 1 + p*ruib[i+1];
        }
        ruia[i] = ruia[i+1] + dpa[i];
        ruib[i] = ruib[i+1] + dpb[i];
    }

    // E[0] = aE[0]+b
    // x = ax+b より、xについて解く
    double x = dpb[0]/(1.0-dpa[0]);
    printf("%.10f", x);
}


int main() {
    solve();
    return 0;
}