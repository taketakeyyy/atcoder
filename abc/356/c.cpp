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
    ll N, M, K; cin >> N >> M >> K;
    vector A(M, vector<ll>());
    vector<ll> C(M);
    vector<char> R(M);
    for(ll m=0; m<M; m++) {
        cin >> C[m];
        A[m].resize(C[m]);
        for(ll i=0; i<C[m]; i++) {
            cin >> A[m][i];
            A[m][i]--;
        }
        cin >> R[m];
    }

    // 正しい鍵がbitのときを全探索
    ll ans = 0;
    for(ll bit=0; bit<(1<<N); bit++) { // 1e4
        bool is_ok = true;
        // m回目の試行
        for(ll m=0; m<M; m++) { // 100
            ll correct = 0; // 正しい鍵を挿入した数
            for(ll i=0; i<C[m]; i++) {
                if (bit>>A[m][i]&1) {
                    correct++;
                }
            }

            if (correct >= K) {
                if (R[m] != 'o') {
                    is_ok = false;
                    break;
                }
            }
            else {
                if (R[m] != 'x') {
                    is_ok = false;
                    break;
                }
            }
        }

        if (is_ok) ans++;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}