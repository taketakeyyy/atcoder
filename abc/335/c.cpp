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


// 解説AC
// dequeを使う
void solve() {
    ll N, Q; cin >> N >> Q;
    deque<pair<ll,ll>> deq; // front側が頭
    for(ll i=0; i<N; i++) {
        deq.push_back({i+1,0});
    }

    // クエリ処理
    for(ll q=0; q<Q; q++) {
        ll query; cin >> query;
        if (query == 1) {
            // 頭を方向Cに1移動させる
            char C; cin >> C;
            auto[x, y] = deq.front();
            if (C == 'R') deq.push_front({x+1, y});
            else if (C == 'U') deq.push_front({x,y+1});
            else if (C == 'L') deq.push_front({x-1,y});
            else if (C == 'D') deq.push_front({x,y-1});
            deq.pop_back();
        }
        else {
            // パーツpのある座標を求める
            ll p; cin >> p;
            p--;
            auto[x, y] = deq[p];
            printf("%lld %lld\n", x, y);
        }
    }
}

// 配列を使うパターン
void solve2() {
    ll N, Q; cin >> N >> Q;
    vector<pair<ll,ll>> A; // 頭の移動履歴みたいなものを配列で管理する。配列のbackが頭
    for(ll i=N-1; i>=0; i--) {
        A.push_back({i+1,0});
    }

    // クエリ処理
    for(ll q=0; q<Q; q++) {
        ll query; cin >> query;
        if (query == 1) {
            // 頭を方向Cに1移動させる
            char C; cin >> C;
            // 移動するごとに座標を配列の後ろに追加していく
            auto[x, y] = A.back();
            if (C == 'R') A.push_back({x+1, y});
            else if (C == 'U') A.push_back({x,y+1});
            else if (C == 'L') A.push_back({x-1,y});
            else if (C == 'D') A.push_back({x,y-1});
        }
        else {
            // パーツpのある座標を求める
            ll p; cin >> p;
            p--;
            auto[x, y] = A[A.size()-1-p];
            printf("%lld %lld\n", x, y);
        }
    }
}


int main() {
    // solve();
    solve2();
    return 0;
}