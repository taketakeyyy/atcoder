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
    vector<ll> A(N);
    map<ll,ll> num2idx;// 国民番号からiへの辞書
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        num2idx[A[i]] = i;
    }
    sort(A.begin(), A.end());

    // 各国民がもらえるお菓子の個数をシミュレーションする
    ll rnd = K/N;
    ll restK = K%N;
    vector<ll> ans(N);
    for(ll i=0; i<N; i++) {
        if (restK >= 1) {
            ans[num2idx[A[i]]] = rnd+1;
            restK--;
        }
        else {
            ans[num2idx[A[i]]] = rnd;
        }
    }

    // 出力
    for(ll i=0; i<N; i++) {
        cout << ans[i] << endl;
    }
}


int main() {
    solve();
    return 0;
}