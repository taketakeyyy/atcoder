#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1'000'000'007
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


void solve() {
    ll N; cin >> N;
    ll MG; cin >> MG;
    vector G(N, vector(N, false)); // G[i][j] := (i,j)に辺あるか
    for(ll i=0; i<MG; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u][v] = true;
        G[v][u] = true;
    }
    ll MH; cin >> MH;
    vector H(N, vector(N, false)); // H[i][j] := (i,j)に辺あるか
    for(ll i=0; i<MH; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        H[a][b] = true;
        H[b][a] = true;
    }
    vector<vector<ll>> A(N, vector<ll>(N, 0LL));
    for(ll i=0; i<N-1; i++) {
        for(ll j=i+1; j<N; j++) {
            cin >> A[i][j];
        }
    }

    // Hの順列を全探索する
    vector<ll> P(N);
    for(ll i=0; i<N; i++) P[i] = i;
    sort(P.begin(), P.end());
    ll ans = INF;
    do {
        ll total = 0; // コスト
        for(ll i=0; i<N; i++) {
            for(ll j=i+1; j<N; j++) {
                if (G[i][j]) {
                    if (H[P[i]][P[j]]) continue;
                    ll mn = min(P[i], P[j]);
                    ll mx = max(P[i], P[j]);
                    total += A[mn][mx];
                }
                else {
                    if (!H[P[i]][P[j]]) continue;
                    ll mn = min(P[i], P[j]);
                    ll mx = max(P[i], P[j]);
                    total += A[mn][mx];
                }
            }
        }
        chmin(ans, total);
    }while (next_permutation(P.begin(), P.end()));
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}