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
    ll N; cin >> N;
    vector<string> S(N);
    for(ll i=0; i<N; i++) {
        cin >> S[i];
    }

    auto comp = [&](pair<ll,ll> &p1, pair<ll,ll> &p2) {
        if (p1.first == p2.first) {
            return p1.second < p2.second;
        }
        return p1.first > p2.first;
    };

    vector<pair<ll,ll>> P; // (勝ち数、番号)
    for(ll i=0; i<N; i++) {
        ll win = 0;
        for(ll j=0; j<N; j++) {
            if (i==j) continue;
            if (S[i][j] == 'o') win++;
        }
        P.push_back({win,i});
    }
    sort(P.begin(), P.end(), comp);

    // 出力
    for(ll i=0; i<N; i++) {
        auto[ignore, id] = P[i];
        cout << id+1 << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}