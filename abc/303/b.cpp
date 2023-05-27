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
    ll N, M; cin >> N >> M;
    vector<vector<ll>> A(M, vector<ll>(N));
    for(ll i=0; i<M; i++) {
        for(ll j=0; j<N; j++) {
            cin >> A[i][j];
        }
    }

    set<pair<ll,ll>> hunaka;
    for(ll i=1; i<N; i++) {
        for(ll j=i+1; j<=N; j++) {
            hunaka.insert({i,j});
        }
    }

    for(ll i=0; i<M; i++) {
        for(ll j=0; j<N-1; j++) {
            pair<ll,ll> p;
            p.first = min(A[i][j], A[i][j+1]);
            p.second = max(A[i][j], A[i][j+1]);
            hunaka.erase(p);
        }
    }

    cout << hunaka.size() << endl;
}


int main() {
    solve();
    return 0;
}