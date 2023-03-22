#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
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


// 解説AC
// ある竹が最後に伐採された時刻がxのとき、それ以前に伐採されているか否かに関わらず、その竹から得られる得点はxである。
// イベントを逆順に見て、各N個の竹について、最後に伐採される時刻を記録する。
// 記録後、まだ伐採されてない竹の集合からその竹を取り除く。各竹は高々1回しか取り除かれない。
void solve() {
    ll N, M; cin >> N >> M;
    vector<tuple<ll,ll,ll>> events;
    for(ll i=0; i<M; i++) {
        ll t, l, r; cin >> t >> l >> r;
        events.push_back({t,l,r});
    }
    sort(events.begin(), events.end());
    reverse(events.begin(), events.end());

    // 最後に伐採された時刻を記録する
    vector<ll> cut_time(N+1, 0);  // 最後に伐採される時刻
    set<ll> banboos; // まだ伐採されてない竹
    for(ll i=1; i<=N; i++) banboos.insert(i);
    for(ll i=0; i<M; i++) {
        auto[t, l, r] = events[i];
        auto it = banboos.lower_bound(l);
        while(it != banboos.end() && (*it) <= r) {
            cut_time[(*it)] = t;
            auto tmp_it = it; // setを破壊する操作が怖いので
            tmp_it++;
            banboos.erase(it);
            it = tmp_it;
        }
    }

    // 得点の総和計算
    ll ans = 0;
    for(ll i=1; i<=N; i++) ans += cut_time[i];
    cout << ans << endl;
}

// 区間アフィン変換・区間和
struct S {
    ll value;
    int size;
};
struct F {
    ll b, c;
};
S op(S l, S r) { return S{l.value + r.value, l.size + r.size}; }
S e() { return S{0, 0}; }
S mapping(F f, S x) { return S{x.value * f.b + x.size * f.c, x.size}; }
F composition(F f, F g) { return F{g.b * f.b, g.c * f.b + f.c}; }
F id() { return F{1, 0}; }

// 遅延セグメント木解法
void solve2() {
    ll N, M; cin >> N >> M;
    vector<S> v(N, {0, 1});

    // 遅延セグメント木作成
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

    // クエリ処理
    ll ans = 0;
    ll pre_t = 0;  // 前回の時刻
    for(ll i=0; i<M; i++) {
        ll t, l, r; cin >> t >> l >> r;
        l--; r--;
        // すべての竹を成長させる
        seg.apply(0, N, F{1, t-pre_t}); // 1倍して経過時刻を足す
        pre_t = t;
        // 伐採区間の竹の区間和を取得する
        ans += seg.prod(l, r+1).value;
        // 伐採区間の竹を伐採させる
        seg.apply(l, r+1, F{0, 0}); // 0倍して0にする
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}