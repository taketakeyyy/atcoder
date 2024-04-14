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

// BFS
void solve() {
    ll N, M; cin >> N >> M;
    vector<set<ll>> S(N);
    vector<set<ll>> value2Sidx(M+1); // value2Sidx[v] := 「値vが入っている集合S」のインデックスの集合
    for(ll i=0; i<N; i++) {
        ll A; cin >> A;
        for(ll j=0; j<A; j++) {
            ll v; cin >> v;
            S[i].insert(v);
            value2Sidx[v].insert(i);
        }
    }

    vector<bool> visited_v(M+1, false);
    vector<bool> visited_i(N, false);
    deque<pair<ll,ll>> deq; // (集合, コスト)
    // Mが入ってる集合をdeqに入れる
    visited_v[M] = true;
    for(ll i=0; i<N; i++) {
        if (S[i].count(M)) {
            visited_i[i] = true;
            for(ll v: S[i]) {
                if (visited_v[v]) continue;
                visited_v[v] = true;
                deq.push_back({v,0});
            }
        }
    }

    // BFS
    while(!deq.empty()) {
        auto[u, cost] = deq.front(); deq.pop_front();

        if (u == 1) {
            cout << cost << endl;
            return;
        }

        // uが入ってる集合をdeqに入れる
        for(ll i: value2Sidx[u]) {
            if (visited_i[i]) continue;
            visited_i[i] = true;
            if (S[i].count(u)) {
                for(ll v: S[i]) {
                    if (visited_v[v]) continue;
                    visited_v[v] = true;
                    deq.push_back({v,cost+1});
                }
            }
        }
    }
    cout << -1 << endl;
}


int main() {
    solve();
    return 0;
}