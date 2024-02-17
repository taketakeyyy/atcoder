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

#include <atcoder/lazysegtree>
struct S{
    long long value;
    int size;
};
using F = long long;
const F ID = 8e18;
S op(S a, S b){ return {a.value+b.value, a.size+b.size}; }
S e(){ return {0, 0}; }
S mapping(F f, S x){
    if(f != ID) x.value = f*x.size;
    return x;
}
F composition(F f, F g){ return (f == ID ? g : f); }
F id(){ return ID; }

// 解説AC
void solve() {
    ll N, Q; cin >> N >> Q;
    string S1; cin >> S1;

    // Aの作成
    vector<S> A(N, {0, 1}); // (値, サイズ)
    for(ll i=0; i<(ll)S1.size()-1; i++) {
        if (S1[i]==S1[i+1]) A[i] = {1,1};
        else A[i] = {0,1};
    }

    // 遅延セグメント木作成
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    for(ll q=0; q<Q; q++) {
        ll query; cin >> query;
        if (query==1) {
            // [L,R]の0と1を反転させる
            ll L, R; cin >> L >> R;
            L--; R--;
            if (L-1 >= 0) seg.set(L-1, {seg.get(L-1).value^1,1});
            seg.set(R, {seg.get(R).value^1,1});
        }
        else {
            // [L,R]の文字列が良い文字列か判定する
            ll L, R; cin >> L >> R;
            L--; R--;
            if (L==R) {
                cout << "Yes" << endl;
            }
            else {
                if (seg.prod(L,R).value==0) cout << "Yes" << endl;
                else cout << "No" << endl;
            }
        }
    }
}


int main() {
    solve();
    return 0;
}