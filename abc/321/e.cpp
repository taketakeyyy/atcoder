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

// TLE
void solve() {
    ll T; cin >> T;

    auto f = [&](auto f, ll u, ll d, ll pre_u, ll N, ll K, ll &ans) {
        // 終了条件
        if (d == K) {
            ans++; return;
        }
        if (d > K) return;

        {// 左の子探索
            ll v = u*2;
            if (v<=N && v!=pre_u) {
                ll tmp = v;
                ll cnt = 1;
                while(tmp*2 <= N) { // 高々64回
                    tmp *= 2;
                    cnt++;
                }
                if (d+cnt >= K) {
                    f(f, v, d+1, u, N, K, ans);
                }
            }
        }
        {// 右の子探索
            ll v = u*2+1;
            if (v<=N && v!=pre_u) {
                ll tmp = v;
                ll cnt = 1;
                while(tmp*2 <= N) {
                    tmp *= 2;
                    cnt++;
                }
                if (d+cnt >= K) {
                    f(f, v, d+1, u, N, K, ans);
                }
            }
        }
        {// 親探索
            ll v = u/2;
            if (v>=1 && v!=pre_u) {
                f(f, v, d+1, u, N, K, ans);
            }
        }
    };

    // クエリ処理
    vector<ll> anss;
    for(ll t=0; t<T; t++) {
        ll N, X, K; cin >> N >> X >> K;
        if (K == 0) {
            anss.push_back(1);
        }
        else {
            ll ans = 0;
            f(f,X,0,-1,N,K,ans);
            anss.push_back(ans);
        }
    }

    // 出力
    for(ll ans: anss) {
        cout << ans << endl;
    }
}


// 解説AC
void solve2() {
    ll T; cin >> T;

    // 頂点uからd下がったところの頂点数は？
    auto down_d_num = [&](ll u, ll d, ll N) -> ll {
        // オーバーフロー注意
        if (u > N) return 0;
        ll l = u, r = u;
        for(ll i=0; i<d; i++) {
            l = l*2;
            if (l > N) return 0;
            r = r*2+1;
        }
        r = min(r,N);
        return r-l+1;
    };

    // クエリ処理
    vector<ll> anss;
    for(ll t=0; t<T; t++) {
        ll N, X, K; cin >> N >> X >> K;
        ll ans = 0;

        if (K == 0) {
            anss.push_back(1);
            continue;
        }

        // 「i個上がって、K-i個下がる」を全探索したい
        ans = down_d_num(X, K, N);
        while(X > 1 && K >= 2) {
            ll bro = X^1; // 兄弟
            ans += down_d_num(bro, K-2, N); // 兄弟からK-2下がったところの頂点数は？
            K--; X /= 2; // 1個上がる
        }
        if (K==1 && X!=1) ans++;
        anss.push_back(ans);
    }

    // 出力
    for(ll ans: anss) {
        cout << ans << endl;
    }

}

int main() {
    // solve();
    solve2();
    return 0;
}