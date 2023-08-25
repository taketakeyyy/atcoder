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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    vector<ll> F(N), S(N);
    vector<priority_queue<ll>> flaver(N+1); // flaver[i] := フレーバーがiのアイス
    vector<pair<ll,ll>> ices;
    for(ll i=0; i<N; i++) {
        cin >> F[i] >> S[i];
        ices.push_back({S[i], F[i]});
        flaver[F[i]].push(S[i]);
    }

    // 異なるフレーバーから2種類選ぶ
    sort(ices.begin(), ices.end());
    reverse(ices.begin(), ices.end());
    ll ans = ices[0].first;
    for(ll i=1; i<N; i++) {
        if (ices[i].second != ices[0].second) {
            ans += ices[i].first;
            break;
        }
    }

    // 同じフレーバーから2種類選ぶ
    for(ll i=0; i<N+1; i++) {
        if (flaver[i].size() < 2) continue;
        ll total = flaver[i].top(); flaver[i].pop();
        total += flaver[i].top()/2;
        ans = max(ans, total);
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}