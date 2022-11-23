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

ll M;  // グラフ数
double eps;  // エラー率

void init_solver() {
    ll N = 20;
    cout << N << endl; flush(cout);

    // グラフ作成
    for (ll k=0; k<M; k++) {
        vector<ll> ans;
        for(ll i=0; i<k; i++) {
            ans.push_back(1);
        }
        ll sz = N*(N-1)/2;
        for(ll i=0; i<sz-k; i++) {
            ans.push_back(0);
        }

        for(ll i=0; i<(ll)ans.size(); i++) cout << ans[i];
        cout << endl; flush(cout);
    }

    // クエリ処理
    for(ll q=0; q<100; q++) {
        string H; cin >> H;
        ll one = 0;
        for(ll i=0; i<(ll)H.size(); i++) {
            if (H[i] == '1') one++;
        }
        ll t = min(one, M-1);
        cout << t << endl; flush(cout);
    }
}

/**
 * (1) 自分でグラフGを作る（頂点数Nも自分で決める）
 * (2) クエリ処理で、Gから作られたグラフHが与えられる。
 * (3) HはどのGから作られたか予測し、予測値を出力せよ
 *
 */
void solve() {
    cin >> M >> eps;

    init_solver();

}


int main() {
    solve();
    return 0;
}