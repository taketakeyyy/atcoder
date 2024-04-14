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
    ll N, M; cin >> N >> M;
    vector<ll> A(M), B(M);
    vector<ll> indeg(N, 0); // 入次数
    for(ll i=0; i<M; i++) {
        cin >> A[i] >> B[i];
        A[i]--; B[i]--;
        indeg[B[i]]++;
    }

    // 入次数0のものが答え
    vector<ll> ans;
    for(ll i=0; i<N; i++) {
        if (indeg[i] == 0) {
            ans.push_back(i+1);
        }
    }

    if (ans.size() == 1) {
        cout << ans[0] << endl;
    }
    else {
        cout << -1 << endl;
    }
}


int main() {
    solve();
    return 0;
}