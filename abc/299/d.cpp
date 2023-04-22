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

    // クエリ20回まで
    vector<ll> S(N, -1);
    S[0] = 0;
    S[N-1] = 1;
    ll l = 0, r = N-1;
    for(ll t=0; t<20; t++) {
        ll mid = (l+r)/2;
        cout << "? " << mid+1 << endl;
        ll res; cin >> res;
        S[mid] = res;
        if (res == 0) {
            // 右を探索
            l = mid;
        }
        else {
            // 左を探索
            r = mid;
        }
    }

    // pを探す
    for(ll i=0; i<N-1; i++) {
        if (S[i]!=-1 && S[i+1]!=-1 && S[i] != S[i+1]) {
            cout << "! " << i+1 << endl;
            return;
        }
    }

}


int main() {
    solve();
    return 0;
}