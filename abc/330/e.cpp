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

#include <atcoder/segtree>
using S = long long;
S op(S a, S b) { return min(a, b); }
S e() { return INF; }
// max_rightの二分探索用
S target;
bool comp(S x) { return x < target; }


void solve() {
    ll N, Q; cin >> N >> Q;
    set<ll> notAset;
    for(ll i=0; i<=2e5+1; i++) {
        notAset.insert(i);
    }
    set<ll> Aset;
    map<ll,ll> mp;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        Aset.insert(A[i]);
        notAset.erase(A[i]);
        mp[A[i]]++;
    }

    // セグメントツリー作成
    // atcoder::segtree<S, op, e> seg(A);

    // mexを知りたい
    ll mex = 0;
    for(ll a: Aset) {
        if (a == mex) {
            mex++;
            continue;
        }
        break;
    }

    vector<ll> ans(Q);
    for(ll q=0; q<Q; q++) {
        ll i, x; cin >> i >> x;
        i--;
        ll a = A[i];
        A[i] = x;
        // seg.set(i, x);
        mp[a]--;
        mp[x]++;
        notAset.erase(x);
        if (mp[a] == 0) {
            Aset.erase(a);
            notAset.insert(a);
            if (a < mex) {
                // mex更新
                mex = a;
            }
        }
        if (mp[x] == 1) {
            if(mex == x) {
                // mex更新
                mex = *notAset.begin();
                // mex = seg.prod(0,N);
            }
            Aset.insert(x);
        }
        ans[q] = mex;
    }

    // 出力
    for(ll mex: ans) {
        cout << mex << endl;
    }
}


int main() {
    solve();
    return 0;
}