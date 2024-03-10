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
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // 双方向連結リスト
    map<ll,ll> prev; // prev[a] := 値aの前の値
    map<ll,ll> next; // next[a] := 値aの後の値
    // 便宜上、双方向連結リストの先頭と最後尾を定義する
    constexpr ll HEAD = -1; // 先頭の値
    constexpr ll TAIL = INF; // 最後尾の値
    next[HEAD] = A[0];
    prev[A[0]] = HEAD;
    for(ll i=0; i<N-1; i++) {
        next[A[i]] = A[i+1];
        prev[A[i+1]] = A[i];
    }
    next[A[N-1]] = TAIL;
    prev[TAIL] = A[N-1];

    // クエリ処理
    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll query; cin >> query;
        if (query == 1) {
            // A内の要素xの直後にyを挿入する
            ll x, y; cin >> x >> y;
            prev[y] = x;
            next[y] = next[x];
            next[x] = y;
            prev[next[y]] = y;
        }
        else {
            // A内の要素xを削除する
            ll x; cin >> x;
            next[prev[x]] = next[x];
            prev[next[x]] = prev[x];
        }
    }

    {// 出力
        ll now = next[HEAD];
        while(now != TAIL) {
            cout << now << " ";
            now = next[now];
        }
        cout << endl;
    }
}


int main() {
    solve();
    return 0;
}