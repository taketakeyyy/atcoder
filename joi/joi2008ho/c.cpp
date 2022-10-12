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


int main() {
    solve();
    return 0;
}