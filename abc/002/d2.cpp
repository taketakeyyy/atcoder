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


// Nが小さいので派閥に選ぶ国会議員をbit全探索できる。
// 選んだ国会議員が全員知り合い同士だったらOKで、その人数を数える
void solve() {
    ll N, M; cin >> N >> M;
    vector<set<ll>> relation(N);  // relation[i] := 議員iの知り合いの集合
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y; x--; y--;
        relation[x].insert(y);
        relation[y].insert(x);
    }

    ll ans = 0;
    // 派閥に選ぶ国会議員をbit全探索する
    for(ll bit=0; bit<(1<<N); bit++) {
        vector<ll> giin;  // 今回派閥に選んだ国会議員たち
        for(ll d=0; d<N; d++) {
            if (bit>>d&1) {
                giin.push_back(d);
            }
        }

        // 選んだ国会議員は互いに全員知り合いかチェックする
        bool is_ok = true;
        for(ll i=0; i<(ll)giin.size(); i++) {
            for(ll j=i+1; j<(ll)giin.size(); j++) {
                if (relation[giin[i]].count(giin[j])) continue;
                is_ok = false; break;
            }
        }

        if (is_ok) ans = max(ans, (ll)giin.size());
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}