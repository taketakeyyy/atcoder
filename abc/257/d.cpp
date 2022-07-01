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


bool f(ll s, ll N, vector<tuple<ll,ll,ll>> &jumps) {
    vector<vector<ll>> dist(N, vector<ll>(N, 0));
    for(ll i=0; i<N; i++) {
        auto[x1, y1, p1] = jumps[i];
        for(ll j=0; j<N; j++) {
            if (i == j) continue;
            auto[x2, y2, p2] = jumps[j];
            ll d = abs(x1-x2) + abs(y1-y2);
            if (p1*s >= d) {
                dist[i][j] = 1;
            }
            else {
                dist[i][j] = INF;
            }
        }
    }

    // ワーシャルフロイド
    for(ll k=0; k<N; k++) {
        for(ll i=0; i<N; i++) {
            for(ll j=0; j<N; j++) {
                if (dist[i][k]==INF || dist[k][j]==INF) {}  // オーバーフロー対策 (INF+INFだめ)
                else {
                    dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
                }
            }
        }
    }

    // 適切な始点を選べば全点行けるか？
    for(ll i=0; i<N; i++) {
        bool is_ok = true;
        for(ll j=0; j<N; j++) {
            if (dist[i][j] == INF) {
                is_ok = false;
                break;
            }
        }
        if (is_ok) return true;
    }
    return false;
}

void solve() {
    ll N; cin >> N;
    vector<tuple<ll,ll,ll>> jumps(N);
    for(ll i=0; i<N; i++) {
        ll x, y, p; cin >> x >> y >> p;
        jumps[i] = {x, y, p};
    }

    // sをにぶたんしながらワーシャルフロイド
    ll ls = 1;
    ll rs = 4e9+1;
    while(rs-ls != 1) {
        ll s = (ls+rs)/2;
        bool is_ok = f(s, N, jumps);
        if (is_ok) {
            rs = s;
        }
        else {
            ls = s;
        }
    }
    if (f(ls, N, jumps)) {
        cout << ls << endl;
    }
    else {
        cout << rs << endl;
    }
}


int main() {
    solve();
    return 0;
}