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
    ll H, W, M; cin >> H >> W >> M;
    vector<ll> T(M), A(M), X(M);
    for(ll m=0; m<M; m++) {
        cin >> T[m] >> A[m] >> X[m];
        A[m]--;
    }

    // 逆順に見ていくと、数字が確定したものを数えられる
    vector<bool> usedR(H, false); // usedR[h] := h行目のマスは、数字が確定して埋まった
    vector<bool> usedC(W, false); // usedC[w] := w列目のマスは、数字が確定して埋まった
    ll restR = H; // まだ埋まってない行数
    ll restC = W; // まだ埋まってない列数
    map<ll,ll> mp;
    for(ll m=M-1; m>=0; m--) {
        if (T[m]==1) {
            // A[m]行をX[m]に書き換える
            if (usedR[A[m]]) continue;
            usedR[A[m]] = true;
            mp[X[m]] += restC;
            if (mp[X[m]]==0) mp.erase(X[m]);
            restR--;
        }
        else {
            // A[m]列をX[m]に書き換える
            if (usedC[A[m]]) continue;
            usedC[A[m]] = true;
            mp[X[m]] += restR;
            if (mp[X[m]]==0) mp.erase(X[m]);
            restC--;
        }
    }

    {// 残りはすべて0
        ll rest = H*W;
        for(auto[key, val]: mp) {
            rest -= val;
        }
        mp[0] += rest;
        if (mp[0]==0) mp.erase(0);
    }

    // 出力
    cout << mp.size() << endl;
    for(auto[key, val]: mp) {
        cout << key << " " << val << endl;
    }
}


int main() {
    solve();
    return 0;
}