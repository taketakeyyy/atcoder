#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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

ll N;
vector<vector<ll>> A;
ll M;
set<pair<ll,ll>> XYset;
ll ans = INF;


void solve() {
    cin >> N;
    A.resize(N);
    for(int i=0; i<N; i++) {
        A[i].resize(N,0);
        for(int j=0; j<N; j++) cin >> A[i][j];
    }
    cin >> M;
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        x--; y--;
        XYset.insert(make_pair(min(x,y), max(x,y)));
    }

    // Nが小さいのであり得る組み合わせを全探索すればOK
    // 順列全探索
    vector<ll> runners;
    for(ll i=0; i<N; i++) runners.push_back(i);
    do {
        bool is_ok = true;
        for(ll i=0; i<N-1; i++) {
            ll x = runners[i];
            ll y = runners[i+1];
            if (XYset.count(make_pair(min(x,y), max(x,y)))) {
                is_ok = false;
                break;
            }
        }
        if (!is_ok) continue;

        ll total = 0;
        for(ll i=0; i<N; i++) {
            ll now = runners[i];
            total += A[now][i];
        }
        ans = min(ans, total);
    }while(next_permutation(runners.begin(), runners.end()));

    // 出力
    if (ans==INF) {
        cout << -1 << endl;
    }
    else {
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}