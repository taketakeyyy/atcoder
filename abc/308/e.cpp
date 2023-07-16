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

// {a,b,c}のmexを求める
ll mex(ll a, ll b, ll c) {
    set<ll> st = {a,b,c};
    ll res = 0;
    while (st.count(res)) res++;
    return res;
}

void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    string S; cin >> S;

    // idxM[a] := Aの値がaになるMのインデックスのリスト
    // idxX[a] := Aの値がaになるXのインデックスのリスト
    vector idxM(3, vector<ll>()), idxX(3, vector<ll>());
    vector<ll> idxE; // Eのインデックス
    for(ll i=0; i<N; i++) {
        if (S[i] == 'M') idxM[A[i]].push_back(i);
        if (S[i] == 'X') idxX[A[i]].push_back(i);
        if (S[i] == 'E') idxE.push_back(i);
    }

    // (i,j,k)のjを固定して全探索
    ll ans = 0;
    for(auto j: idxE) {
        if (S[j] != 'E') continue;

        for(ll a=0; a<3; a++) {
            // jとペアになれるiを探す
            ll idxm = lower_bound(idxM[a].begin(), idxM[a].end(), j) - idxM[a].begin();
            if (idxm == 0) continue;
            idxm--;
            // [0, idxm]までとペアになるので個数は…
            ll num_M = idxm+1;

            for(ll c=0; c<3; c++) {
                // jとペアになれるkを探す
                ll idxx = lower_bound(idxX[c].begin(), idxX[c].end(), j) - idxX[c].begin();
                if (idxx == (ll)idxX[c].size()) continue;
                // [idxx, idxX.size()-1]までとペアになるので個数は…
                ll num_X = (ll)idxX[c].size() - idxx;

                // 答えがmex(a,A[j],c)となるものを一気に足し合わせる
                ans += mex(a, A[j], c) * num_M * num_X;
            }
        }
    }
    cout << ans << endl;
}

void solve2() {
    ll N; cin >> N;
    vector<ll> A(N+1);
    for(ll i=1; i<=N; i++) cin >> A[i];
    string S; cin >> S;
    S = ' ' + S;

    // dp[i][j][k] := 左からi文字目まで見て、MEXのj文字目まで数えた状態で、{0,1,2}のどれを含むかの状態がk(8通り)のときの場合の数
    vector dp(N+1, vector<vector<ll>>(4, vector<ll>(8, 0)));
    dp[0][0][0] = 1;
    for(ll i=1; i<=N; i++) {
        // i文字目を選ばない場合
        for(ll j=0; j<4; j++) {
            for(ll k=0; k<8; k++) dp[i][j][k] += dp[i-1][j][k];
        }

        // i文字目を選ぶ場合
        for(ll k=0; k<8; k++) {
            if (S[i] == 'M') dp[i][1][k|(1<<A[i])] += dp[i-1][0][k];
            if (S[i] == 'E') dp[i][2][k|(1<<A[i])] += dp[i-1][1][k];
            if (S[i] == 'X') dp[i][3][k|(1<<A[i])] += dp[i-1][2][k];
        }
    }

    // 状態kからmexを計算する
    auto mex = [&](ll k) -> ll{
        for(ll d=0; d<3; d++) {
            if (k>>d&1) continue;
            return d;
        }
        return 3LL;
    };

    // 各mexを計算して個数を足し合わせる
    ll ans = 0;
    for(ll k=0; k<8; k++) {
        ans += mex(k) * dp[N][3][k];
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}