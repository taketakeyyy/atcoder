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


void solve() {
    ll N, Q; cin >> N >> Q;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    sort(A.begin(), A.end());

    // 点Bとの距離がD以下の、点Aの個数を返す
    auto f = [&A](ll B, ll D) {
        ll left = B-D;
        ll lidx = lower_bound(A.begin(), A.end(), left) - A.begin();
        ll right = B+D;
        ll ridx = upper_bound(A.begin(), A.end(), right) - A.begin();
        ll cnt = ridx - lidx;
        return cnt;
    };

    // クエリ処理
    for(ll q=0; q<Q; q++) {
        ll b, k; cin >> b >> k;

        // 二分探索
        ll l=0, r=2e8+10;
        while(r-l != 1) {
            ll mid = (l+r)/2;
            if (f(b,mid) < k) l = mid;
            else r = mid;
        }
        if (f(b,l) >= k) cout << l << endl;
        else cout << r << endl;
    }
}


int main() {
    solve();
    return 0;
}