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

// 品物の選び方の全探索は2^32(=4e9)でTLEする。
// Nが半分だと2^16(=65536)で全探索できる。半分全列挙で解く。
void solve() {
    ll N, X; cin >> N >> X;
    vector<ll> W(N);
    for(ll i=0; i<N; i++) cin >> W[i];

    // P[i] := [l,r)の範囲で作ることのできる大きさiの分布
    auto genP = [&](ll l, ll r) {
        // Wを[l,r)の範囲に切り取ったものをAとする
        vector<ll> A;
        for(ll i=l; i<r; i++) A.push_back(W[i]);
        ll NA = A.size();

        // Aから作れる大きさをbit全探索
        unordered_map<ll,ll> P;
        for(ll bit=0; bit<(1<<NA); bit++) {
            ll total = 0; // 大きさの総和
            for(ll d=0; d<NA; d++) {
                if (bit>>d&1) {
                    total += A[d];
                }
            }
            if (total <= X) P[total]++;
        }
        return P;
    };
    auto P1 = genP(0, N/2); // 前半部分
    auto P2 = genP(N/2, N); // 後半部分

    // ちょうどXとなる選び方を探索する
    ll ans = 0;
    for(auto [p1, v1]: P1) {
        ll x = X-p1;
        if (x<0 || X<x) continue;
        if (P2.count(x)) {
            ans += v1 * P2[x];
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}