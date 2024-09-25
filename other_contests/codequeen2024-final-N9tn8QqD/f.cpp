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


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // 平均を求める
    double mu = 0;
    for(ll i=0; i<N; i++) mu += A[i];
    mu /= (double)N;

    // 累積和
    vector<ll> S(N+1);
    for(ll i=0; i<N; i++) S[i+1] = S[i] + A[i];

    const ll s = S[N];
    for(ll i=0; i<=N; i++) {
        S[i] = S[i]*N-s*i;
    }
    ll idx = min_element(S.begin(), S.end()) - S.begin();
    cout << idx+1 << endl;
}

void solve2() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // 累積和
    vector<ll> S(N+1);
    for(ll i=1; i<=N; i++) S[i] = S[i-1] + A[i-1];

    // NS[i]-iS[N]が最小となるようなiを探す
    vector<ll> X(N+1);
    for(ll i=0; i<=N; i++) {
        X[i] = N*S[i] - i*S[N];
    }
    ll idx = min_element(X.begin(), X.end()) - X.begin();
    cout << idx+1 << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}