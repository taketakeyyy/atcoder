#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// 「4本の矢を投げる」を、「2本の矢を投げることを2回する」と考える。
void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> P1(N);  // 1回投げて作れる整数
    for(ll i=0; i<N; i++) cin >> P1[i];
    P1.push_back(0);  // 投げない場合のために0を入れとくとラク
    sort(P1.begin(), P1.end());
    vector<ll> P2;  // 2回投げて作れる整数
    for(ll i=0; i<(ll)P1.size(); i++) {
        for(ll j=0; j<(ll)P1.size(); j++) {
            P2.push_back(P1[i]+P1[j]);
        }
    }
    sort(P2.begin(), P2.end());

    // P2[i]を決め打ちしたときの、残りのM-P2[i]に近い値を二分探索する
    ll ans = 0;
    for(ll i=0; i<(ll)P2.size(); i++) {
        if (M-P2[i] >= 0) {
            auto it = upper_bound(P2.begin(), P2.end(), M-P2[i]);
            ans = max(ans, P2[i]+(*(--it)));
        }
    }

    cout << ans << endl;
}


// 半分全列挙
// 4本のダーツの和をa+b+c+dとする。
// (a+b)と(c+d)に分割し、(a+b)で作れる点数を全列挙する。(c+d)も同様。
// M以下で最大になる(a+b)と(c+d)の組み合わせを二分探索で探す
void solve2() {
    ll N, M; cin >> N >> M;
    vector<ll> P(N);
    for(ll i=0; i<N; i++) cin >> P[i];
    P.push_back(0); // 0点は必ず必要

    // P2 := ダーツを2本投げて作ることのできる点数の集合
    auto genP2 = [&]() {
        set<ll> P2;
        for(ll i=0; i<N+1; i++) {
            for(ll j=0; j<N+1; j++) {
                P2.insert(P[i]+P[j]);
            }
        }
        return P2;
    };
    auto P2 = genP2();

    // 前半2本投げた点数を固定して、後半2本投げたときのM以下の最大の点数を二分探索する
    ll ans = 0;
    for(ll v1: P2) {
        ll target = M-v1;
        if (target < 0) continue;
        auto it = P2.upper_bound(target);
        it--;
        ans = max(ans, v1 + (*it));
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}