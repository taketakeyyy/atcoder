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


void solve1() {
    // 周期性を使った解法
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
    }

    ll now = 0;
    set<ll> visited;
    vector<ll> path;
    while(!visited.count(now)) {
        visited.insert(now);
        path.push_back(now);
        now = A[now]-1;
    }
    ll loop_start_id = now;

    vector<ll> sippoG;  // しっぽ用グラフ
    vector<ll> loopG;  // ループ用グラフ
    bool is_loopG = false;
    for(ll i=0; i<(ll)path.size(); i++) {
        if (loop_start_id == path[i]) { is_loopG = true; }
        if (is_loopG) {
            loopG.push_back(path[i]);
        }
        else {
            sippoG.push_back(path[i]);
        }
    }

    // K回使ったときの到着する街の番号は？
    if (K <= (ll)sippoG.size()-1) {
        cout << sippoG[K]+1 << endl;
    }
    else {
        K -= sippoG.size();
        K %= loopG.size();
        cout << loopG[K]+1 << endl;
    }
}


void solve2() {
    // ダブリングを使った解法
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        A[i]--;
    }

    // ダブリングのグラフ構築
    const ll D = 60;  // ダブリングの個数。2^60あれば十分なので
    const ll MAX_N = 200005;  // 最大の頂点番号
    vector doubling(D, vector<ll>(MAX_N));  // doubling[k][i] := 頂点iから2^k辿った先の頂点は？
    for(ll i=0; i<N; i++) {
        doubling[0][i] = A[i];
    }
    for(ll k=1; k<D; k++) {
        for(ll i=0; i<N; i++) {
            doubling[k][i] = doubling[k-1][doubling[k-1][i]];  // 2^{k}辿った先は、「2^{k-1}辿った先」を2回辿ればよい
        }
    }

    // ダブリングを使って解く
    ll now = 0;
    for(ll k=D-1; k>=0; k--) {
        if ((K>>k)&1) {
            now = doubling[k][now];
        }
    }
    cout << now+1 << endl;
}

int main() {
    // solve1();
    solve2();
    return 0;
}