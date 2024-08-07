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
    ll N, M; cin >> N >> M;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    ll allA = accumulate(A.begin(), A.end(), 0LL);
    if (allA <= M) {
        cout << "infinite" << endl;
        return;
    }

    sort(A.begin(), A.end());
    vector<ll> ruiA(N+1);
    for(ll i=0; i<N; i++) {
        ruiA[i+1] = ruiA[i] + A[i];
    }

    // 上限額をxにしたとき、総和はM円以下にできるか？
    auto f = [&](ll x) {
        ll idx = lower_bound(A.begin(), A.end(), x) - A.begin();

        ll total = ruiA[idx];
        total += (N-idx)*x;
        if (total <= M) return true;
        return false;
    };

    ll l = 0;
    ll r = 200000000000000;
    while(r-l != 1) {
        ll mid = (l+r)/2;
        if (f(mid)) l = mid;
        else r = mid;
    }
    if (f(r)) cout << r << endl;
    else cout << l << endl;
}


int main() {
    solve();
    return 0;
}