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
    ll N, K; cin >> N >> K;

    // 各靴下の数
    map<ll,ll> mp;
    for(ll i=0; i<N; i++) mp[i] = 2;

    // 靴下をなくす
    for(ll i=0; i<K; i++) {
        ll a; cin >> a; a--;
        mp[a]--;
    }

    // 靴下の数をベクトルになおす
    vector<ll> socks;
    for(auto[key, val]: mp) {
        for(ll i=0; i<val; i++) socks.push_back(key);
    }

    if ((2*N-K)%2 == 0) {
        // 靴下にあまりがないとき、左から貪欲にペアを組むのが最適
        ll ans = 0;
        for(ll i=0; i<2*N-K; i+=2) {
            ans += abs(socks[i]-socks[i+1]);
        }
        cout << ans << endl;
        return;
    }
    else {
        // 靴下にあまりがでるとき、しゃくとり法で最適な値を求める
        // 一番左をあまらせる場合
        vector<ll> B;
        for(ll i=1; i<2*N-K; i+=2) {
            B.push_back(abs(socks[i]-socks[i+1]));
        }
        // 一番右をあまらせる場合
        vector<ll> C;
        for(ll i=0; i<2*N-K-1; i+=2) {
            C.push_back(abs(socks[i]-socks[i+1]));
        }

        ll total = accumulate(B.begin(), B.end(), 0LL);
        ll ans = total;
        for(ll i=0; i<(ll)B.size(); i++) {
            total = total - B[i] + C[i];
            chmin(ans, total);
        }
        cout << ans << endl;
        return;
    }
}


int main() {
    solve();
    return 0;
}