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
    ll N, M, K; cin >> N >> M >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    ll ans = 0;
    for(ll i=30; i>=0; i--) {
        ll cost = 0;  // 必要な操作回数
        ans += 1<<i;
        sort(A.begin(), A.end(), greater<ll>());

        for(ll j=0; j<K; j++) {
            if (A[j] < ans) {
                cost += ans - A[j];
            }
        }

        if (cost > M) {
            for(ll j=0; j<K; j++) {
                if (A[j] >= ans) {
                    A[j] -= 1<<i;
                }
            }
            ans ^= 1<<i;
        }
    }
    cout << ans << endl;

}


int main() {
    solve();
    return 0;
}