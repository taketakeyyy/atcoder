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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

#include <atcoder/lazysegtree>
// 区間加算・区間最大値取得
using S = long long;
using F = long long;
const S INF = 8e18;
S op(S l, S r){ return std::max(l, r); }
S e(){ return -INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

void solve() {
    ll N, D, W; cin >> N >> D >> W;
    vector<pair<ll,ll>> coords(N);
    for(ll i=0; i<N; i++) {
        ll t, x; cin >> t >> x;
        coords[i] = {x,t};
    }
    sort(coords.begin(), coords.end());

    // 遅延セグメント木作成 num[t] := [t, t+D-1]の区間にある点の個数
    const ll MAX_T = 200000;
    vector<S> A(MAX_T+1LL, 0LL);
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> num(A);

    // xが小さい方から大きい方へ平面走査
    ll ans = -INF;
    set<pair<ll,ll>> st; // 点(x,t)の集合
    for(ll i=0; i<N; i++) {
        auto[x, t] = coords[i];
        st.insert({x,t});
        {// 区間加算
            ll l = max(0LL, t-(D-1));
            ll r = t;
            num.apply(l, r+1, 1LL);
        }

        {// 集合内のx座標の最大値と最小値の差がW-1以下になるようにする
            while(true) {
                if (st.empty()) break;
                auto it1 = st.begin(); // xが最小のもの
                auto it2 = st.end(); it2--; // xが最大のもの
                if (it2->first-it1->first > W-1) {
                    ll l = max(0LL, it1->second-(D-1));
                    ll r = it1->second;
                    num.apply(l, r+1, -1LL);
                    st.erase(it1);
                    continue;
                }
                break;
            }
        }

        // 答え更新
        chmax(ans, num.all_prod());
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}