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
    vector<ll> C(N);
    vector<set<ll>> A(N);

    for(ll i=0; i<N; i++) {
        cin >> C[i];
        for(ll c=0; c<C[i]; c++) {
            ll a; cin >> a;
            A[i].insert(a);
        }
    }
    ll X; cin >> X;

    // Xに賭けた人は？
    ll mn = INF;
    vector<ll> cands;
    for(ll i=0; i<N; i++) {
        if (A[i].count(X)) {
            if (mn > A[i].size()) {
                mn = A[i].size();
            }
            cands.push_back(i);
        }
    }

    // 最小の人だけ残す
    vector<ll> ans;
    for(ll i=0; i<(ll)cands.size(); i++) {
        if ((ll)A[cands[i]].size() == mn) ans.push_back(cands[i]);
    }
    sort(ans.begin(),ans.end());

    // 出力
    cout << ans.size() << endl;
    for(ll val: ans) {
        cout << val+1 << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}