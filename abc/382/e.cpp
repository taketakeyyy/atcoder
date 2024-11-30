#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }


void solve() {
    ll N, X; cin >> N >> X;
    vector<ll> P(N);
    for(ll i=0; i<N; i++) cin >> P[i];

    // prob[i][x] := （パックを開封した時、）i枚目まで見て、レアカードをx枚入手する確率を求める
    vector<double> prob(N+1, 0.0);
    prob[0] = 1.0;
    for(ll i=0; i<N; i++) {
        vector<double> new_prob(N+1, 0.0);

        // レアカードを引けない場合
        for(ll n=0; n<=i; n++) {
            new_prob[n] += prob[n] * (1.0-(double)P[i]/100.0);
        }

        // レアカードを引く場合
        for(ll n=1; n<=i+1; n++) {
            new_prob[n] += prob[n-1] * ((double)P[i]/100.0);
        }

        swap(new_prob, prob);
    }

    // 期待値E[x] := 現在のレアカードの枚数がxのときの、終了するまでのパックの開封数の期待値
    vector<double> E(X+10+N, 0.0);
    // E[X] = 0;
    for(ll x=X-1; x>=0; x--) {
        double sum_right = 0;
        for(ll i=1; i<=N; i++) {
            sum_right += (1+E[x+i])*prob[i];
        }
        sum_right += prob[0];
        E[x] = sum_right / (1.0 - prob[0]);
    }

    // 答え
    printf("%.10f\n", E[0]);
}


int main() {
    solve();
    return 0;
}