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
    ll N, K; cin >> N >> K;
    if (K == 1) {
        cout << N << endl;
        return;
    }

    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // 尺取法っぽく順にK個連続単調増加しているかチェックする
    ll ans = 0;
    ll seq_num = 1;
    for(ll i=1; i<N; i++) {
        if (A[i] > A[i-1]) {
            seq_num = min(seq_num+1, K);
        }
        else {
            seq_num = 1;
        }

        if (seq_num == K) {
            ans++;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}