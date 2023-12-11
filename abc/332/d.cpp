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


// 状態数は H! × W! (最大で14400)しかないので、BFSで探索できる
void solve() {
    ll H, W; cin >> H >> W;
    vector A(H, vector<ll>(W));
    vector B(H, vector<ll>(W));
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) cin >> A[i][j];
    }
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) cin >> B[i][j];
    }

    auto is_same = [&H, &W, &B](vector<vector<ll>> const &A) -> bool {
        for(ll h=0; h<H; h++) {
            for(ll w=0; w<W; w++) {
                if (A[h][w] != B[h][w]) return false;
            }
        }
        return true;
    };

    queue<pair<vector<vector<ll>>,ll>> que; // (状態,コスト)
    que.push({A,0});
    set<vector<vector<ll>>> visited;
    visited.insert(A);
    while(!que.empty()) {
        auto[A, cost] = que.front(); que.pop();

        if (is_same(A)) {
            cout << cost << endl;
            return;
        }

        // 行の入れ替え
        for(ll i=0; i<H-1; i++) {
            ll j = i+1;
            for(ll w=0; w<W; w++) swap(A[i][w], A[j][w]);
            if (visited.count(A)) {
                for(ll w=0; w<W; w++) swap(A[i][w], A[j][w]);
                continue;
            }
            visited.insert(A);
            que.push({A,cost+1});
            for(ll w=0; w<W; w++) swap(A[i][w], A[j][w]);
        }

        // 列の入れ替え
        for(ll i=0; i<W-1; i++) {
            ll j = i+1;
            for(ll h=0; h<H; h++) swap(A[h][i], A[h][j]);
            if (visited.count(A)) {
                for(ll h=0; h<H; h++) swap(A[h][i], A[h][j]);
                continue;
            }
            visited.insert(A);
            que.push({A,cost+1});
            for(ll h=0; h<H; h++) swap(A[h][i], A[h][j]);
        }
    }
    cout << -1 << endl;
}


int main() {
    solve();
    return 0;
}