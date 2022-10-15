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


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    set<ll> Aset;
    vector<ll> A2;
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        if (!Aset.count(A[i])) {
            A2.push_back(A[i]);
        }
        Aset.insert(A[i]);
    }
    sort(A2.begin(), A2.end());

    vector<ll> ans(N);
    for(ll i=0; i<N; i++) {
        // ll idx = Aset.upper_bound(A[i]) - Aset.begin();
        ll idx = upper_bound(A2.begin(), A2.end(), A[i]) - A2.begin();
        ans[(ll)Aset.size()-idx]++;
    }

    // 出力
    for(ll k=0; k<=N-1; k++) {
        cout << ans[k] << endl;
    }

}


int main() {
    solve();
    return 0;
}