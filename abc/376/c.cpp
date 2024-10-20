#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
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


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    vector<ll> B(N-1);
    for(ll i=0; i<N-1; i++) cin >> B[i];

    // 大きい箱から順に使っていく
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    ll bi = N-2;
    vector<bool> usedToy(N, false); // 箱に入れれたおもちゃ
    for(ll ai=N-1; ai>=0; ai--) {
        if (bi == -1) break;
        if (B[bi] >= A[ai]) {
            // おもちゃを箱にいれる
            usedToy[ai] = true;
            bi--;
            continue;
        }
        else {
            // おもちゃを入れられない
            continue;
        }
    }

    // 入れられなかったおもちゃはひとつだけ？
    ll cnt = 0;
    ll ans = -1;
    for(ll i=0; i<N; i++) {
        if (usedToy[i]) continue;
        cnt++;
        ans = A[i];
    }
    if (cnt != 1) {
        cout << -1 << endl;
    }
    else {
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}