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
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// 区間和セグ木
#include <atcoder/segtree>
using S1 = long long;
S1 op(S1 a, S1 b) { return a + b; }
S1 e() { return 0LL; }

void solve() {
    ll N; cin >> N;
    string S; cin >> S;

    // 各文字の分布をセグ木で管理
    vector<ll> mp(26, 0); // mp[c] := 文字cの分布
    vector<atcoder::segtree<S1, op, e>> cnt(26, atcoder::segtree<S1, op, e>(N));
    for(ll i=0; i<N; i++) {
        mp[S[i]-'a']++;
        cnt[S[i]-'a'].set(i,1);
    }

    // S[l:r]が昇順になっているか
    atcoder::segtree<S1, op, e> order(N);
    for(ll i=0; i<N-1; i++) {
        if (S[i] > S[i+1]) {
            order.set(i,1);
        }
    }

    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll type; cin >> type;
        if (type == 1) {
            // Sのx文字目をcに置き換える
            ll x; cin >> x; x--;
            char c; cin >> c;
            // 分布更新
            cnt[S[x]-'a'].set(x,0);
            cnt[c-'a'].set(x,1);
            mp[S[x]-'a']--;
            mp[c-'a']++;
            // order更新
            S[x] = c;
            if (x-1 >= 0) {
                if (S[x-1] > S[x]) order.set(x-1,1);
                else order.set(x-1,0);
            }
            if (x+1 < N) {
                if (S[x] > S[x+1]) order.set(x,1);
                else order.set(x,0);
            }
        }
        else {
            // S[l:r]がTの部分文字列か？
            // * order[l:r]が0か？
            // * S(l:r)のcntとmpが一致するか
            ll l, r; cin >> l >> r;
            l--; r--;
            if (order.prod(l, r+1-1) == 0) {
                bool is_ok = true;
                ll sl = S[l]-'a';
                ll sr = S[r]-'a';
                for(ll si=sl+1; si<sr; si++) {
                    if (mp[si] == cnt[si].prod(l,r+1)) continue;
                    is_ok = false;
                    break;
                }
                if (is_ok) cout << "Yes" << endl;
                else cout << "No" << endl;
            }
            else {
                cout << "No" << endl;
            }
        }
    }
}


int main() {
    solve();
    return 0;
}