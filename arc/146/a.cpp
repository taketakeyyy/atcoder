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


// 大きな数を作ることの典型として、
// ・桁数大きいのが正義
// ・桁数が同じなら、9から順に試す
// 今回は3枚選ぶだけなので、大きい3枚の組み合わせを全探索する
void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<=N-1; i++) cin >> A[i];
    sort(A.begin(), A.end());
    reverse(A.begin(), A.end());

    vector<ll> B;
    B.push_back(A[2]);
    B.push_back(A[1]);
    B.push_back(A[0]);

    ll ans = 0;
    do {
        string S;
        for(ll i=0; i<3; i++) {
            S += to_string(B[i]);
        }
        ans = max(ans, stoll(S));
    } while(next_permutation(B.begin(), B.end()));
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}