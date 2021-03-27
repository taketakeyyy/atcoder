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
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    // なにもわからん。解説AC
    // 整数化、整数論、式変形
    ll N, M; cin >> N >> M;
    vector<ll> A;
    set<ll> sets;
    // 重複したA[i]は取り除く
    rep(i,N) {
        ll a; cin >> a;
        if (sets.count(a)) continue;
        sets.insert(a);
        A.push_back(a);
    };

    // A -> A'
    for(int i=0; i<A.size(); i++) {
        A[i] /= 2;
    }

    // A' -> A''
    auto f = [](ll x) {
        // xを2で何回割り切れるかの回数
        ll cnt = 0;
        while(x%2==0) {
            x /= 2;
            cnt++;
        }
        return cnt;
    };
    ll t = f(A[0]);
    for(int i=0; i<A.size(); i++) {
        if (f(A[i]) != t) {
            cout << 0 << endl;
            return;
        }
        A[i] >>= t;  // A[i] /= 2^t
    }
    M >>= t;

    ll l = 1;
    for (int i=0; i<A.size(); i++) {
        l = lcm(l, A[i]);
        if (l > M) {
            cout << 0 << endl;
            return;
        }
    }

    M /= l;
    ll ans = (M+1)/2;
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}