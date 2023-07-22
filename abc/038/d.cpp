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


// WA
// 平面走査
void solve() {
    ll N; cin >> N;
    vector<pair<ll,ll>> boxs1(N); // (w,h)
    vector<pair<ll,ll>> boxs2(N); // (h,w)
    for(ll i=0; i<N; i++) {
        ll w, h; cin >> w >> h;
        boxs1[i] = {w,h};
        boxs2[i] = {h,w};
    }

    ll ans = 1;

    // 平面走査する
    auto scan = [&](vector<pair<ll,ll>> &boxs) -> ll {
        ll res = 1;
        auto[now_w, now_h] = boxs[0];
        for(ll i=1; i<N; i++) {
            auto[w, h] = boxs[i];

            if (w > now_w && h > now_h) {
                res++;
                now_w = w;
                now_h = h;
            }
        }
        return res;
    };

    // wでソートして平面走査で貪欲法
    sort(boxs1.begin(), boxs1.end());
    ans = max(ans, scan(boxs1));

    // hでソートして平面走査で貪欲法
    sort(boxs2.begin(), boxs2.end());
    ans = max(ans, scan(boxs2));

    // 答え
    cout << ans << endl;
}


// AC
#include <atcoder/segtree>
using S = long long;
S op(S a, S b) { return max(a, b); }
S e() { return -1; }

void solve2() {
    ll N; cin >> N;
    vector<pair<ll,ll>> box(N); // (w,h)
    for(ll i=0; i<N; i++) {
        ll w, h; cin >> w >> h;
        box[i] = {w,h};
    }

    // wが小さい順（wが同じとき、hが大きい順）
    auto comp = [&](const pair<ll,ll> &p1, const pair<ll,ll> &p2) -> bool{
        if (p1.first == p2.first) {
            return p1.second > p2.second;
        }
        return p1.first < p2.first;
    };
    sort(box.begin(), box.end(), comp);

    // dp[h] := (左からi番目まで見て)、最後に採用した箱の高さがhのときの、採用できた箱の数の最大値
    vector<ll> dp(100000+1, 0);
    dp[box[0].second] = 1;
    atcoder::segtree<S, op, e> seg(dp);
    for(ll i=1; i<N; i++) {
        ll mx = max(seg.get(box[i].second), seg.prod(0, box[i].second)+1);
        seg.set(box[i].second, mx);
    }

    // 答え
    cout << seg.prod(0, 100000+1) << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}