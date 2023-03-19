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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, Q; cin >> N >> Q;

    // まだ一度も呼ばれてない人
    priority_queue<ll, vector<ll>, greater<ll>> uncall;  // 小さい順を維持する優先度付きキュー
    for(ll i=0; i<N; i++) {
        uncall.push(i);
    }

    // クエリ処理
    priority_queue<ll, vector<ll>, greater<ll>> called;  // 一度は呼ばれた人たち
    vector<bool> accepted(N, false);  // 受付に行ったか
    vector<ll> ans;
    for(ll q=0; q<Q; q++) {
        ll event; cin >> event;
        if (event == 1) {
            ll idx = uncall.top();
            uncall.pop();
            called.push(idx);
        }
        else if (event == 2) {
            ll x; cin >> x;
            x--;
            accepted[x] = true;
        }
        else {
            ll idx;
            while(1) {
                idx = called.top();
                if (accepted[idx]) {
                    called.pop();
                    continue;
                }
                break;
            }
            ans.push_back(idx+1);
        }
    }

    // 出力
    for(ll x : ans) {
        cout << x << endl;
    }
}


int main() {
    solve();
    return 0;
}