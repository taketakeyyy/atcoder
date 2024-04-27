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
    ll N, C; cin >> N >> C;
    vector<ll> X(N+1), V(N+1);
    for(ll i=1; i<N+1; i++) {
        cin >> X[i] >> V[i];
    }

    // 右回りで寿司を食ったときの差し引きカロリーの累積和
    vector<ll> R(N+1, 0LL); // 累積和
    vector<ll> Rmax(N+1, 0LL); // 累積max
    {
        ll nowX = 0;
        for(ll i=1; i<=N; i++) {
            R[i] = R[i-1] + V[i] - (X[i]-nowX);
            Rmax[i] = max(Rmax[i-1], R[i]);
            nowX = X[i];
        }
    }
    // 左回りで寿司を食ったときの差し引きカロリーの累積和
    vector<ll> L(N+2, 0LL); // 累積和
    vector<ll> Lmax(N+2, 0LL); // 累積max
    {
        ll nowX = C;
        for(ll i=N; i>=0; i--) {
            L[i] = L[i+1] + V[i] - (nowX-X[i]);
            Lmax[i] = max(Lmax[i+1], L[i]);
            nowX = X[i];
        }
    }

    // 右回りでどこまで寿司を食べるかを固定する
    ll ans = 0;
    for(ll r=0; r<=N; r++) {
        ll total = R[r];
        chmax(ans, total);

        // 初期位置へ戻る
        total -= X[r];

        // 左回りで、累積maxで最適な寿司まで食べる
        total += Lmax[r+1];
        chmax(ans, total);
    }

    // 左回りでどこまで寿司を食べるかを固定する
    for(ll l=N; l>=0; l--) {
        ll total = L[l];
        chmax(ans, total);

        // 初期位置へ戻る
        total -= C-X[l];

        // 右回りで、累積maxで最適な寿司まで食べる
        if (l-1 >= 0) total += Rmax[l-1];
        chmax(ans, total);
    }
    cout << ans << endl;
}


void solve2() {
    ll N, C; cin >> N >> C;
    vector<ll> X(N+1), V(N+1);
    for(ll i=1; i<N+1; i++) {
        cin >> X[i] >> V[i];
    }

    ll ans = 0;
    // 「右回りで寿司を食べる→初期位置へ戻る→左回りで寿司を食べる」で解く
    auto solver = [&](vector<ll> &X, vector<ll> &V) {
        // 右回りで寿司を食ったときの差し引きカロリーの累積和を求める
        vector<ll> R(N+1, 0LL); // 累積和
        {
            ll nowX = 0;
            for(ll i=1; i<=N; i++) {
                R[i] = R[i-1] + V[i] - (X[i]-nowX);
                nowX = X[i];
            }
        }
        // 左回りで寿司を食ったときの差し引きカロリーの累積maxを求める
        vector<ll> L(N+2, 0LL); // 累積和
        vector<ll> Lmax(N+2, 0LL); // 累積max
        {
            ll nowX = C;
            for(ll i=N; i>=0; i--) {
                L[i] = L[i+1] + V[i] - (nowX-X[i]);
                Lmax[i] = max(Lmax[i+1], L[i]);
                nowX = X[i];
            }
        }

        // 右回りでどこまで寿司を食べるかを固定する
        for(ll r=0; r<=N; r++) {
            ll total = R[r];
            chmax(ans, total);

            // 初期位置へ戻る
            total -= X[r];

            // 左回りで、累積maxで最適な寿司まで食べる
            total += Lmax[r+1];
            chmax(ans, total);
        }
    };
    solver(X, V);

    // 「左回りで寿司を食べる→初期位置へ戻る→右回りで寿司を食べる」も試す
    vector<ll> revX(N+1), revV(N+1);
    for(ll i=1; i<=N; i++) {
        revX[i] = C - X[N+1-i];
        revV[i] = V[N+1-i];
    }
    solver(revX, revV);

    // 答え
    cout << ans << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}