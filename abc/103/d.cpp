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
    vector<ll> A(M), B(M);
    vector<pair<ll,ll>> data(M); // (a,b)間の争いのリスト
    for(ll i=0; i<M; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        A[i] = a; B[i] = b;
        data[i] = {a, b};
    }

    // 比較関数（pairのsecond昇順）
    auto comp = [&](const pair<ll,ll> &p1, const pair<ll,ll> &p2) -> bool {
        return p1.second < p2.second;
    };
    sort(data.begin(), data.end(), comp);

    // 区間スケジューリング問題
    ll ans = 1;
    ll last_r = data[0].second;
    for(ll i=1; i<M; i++) {
        auto[l,r] = data[i];
        if (l < last_r) continue;
        last_r = r;
        ans++;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}