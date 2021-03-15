#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

ll N, A, B, C;
vector<ll> L;

ll dfs (ll i, ll a, ll b, ll c, ll cost) {
    if (i==N) {
        if (a==0 || b==0 || c==0) {
            // 少なくとも1本は選ばないとだめ
            return INF;
        }
        // 最初の1本目は合体魔法は使わないので30引いとく
        return cost + abs(A-a) + abs(B-b) + abs(C-c) - 30;
    }

    ll ret1 = dfs(i+1, a, b, c, cost);
    ll ret2 = dfs(i+1, a+L[i], b, c, cost+10);
    ll ret3 = dfs(i+1, a, b+L[i], c, cost+10);
    ll ret4 = dfs(i+1, a, b, c+L[i], cost+10);

    return min(ret1, min(ret2, min(ret3, ret4)));
}


void solve() {
    // 各竹L[i]について、
    // (1) Aと合成
    // (2) Bと合成
    // (3) Cと合成
    // (4) 使わない
    // の各パターンを全探索する。
    // 最後に、延長魔法と短縮魔法を使う。
    cin >> N >> A >> B >> C;
    rep(i,N) {
        ll l;
        cin >> l;
        L.push_back(l);
    }

    ll ans = dfs(0,0,0,0,0);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}