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

void solve() {
    ll N; cin >> N;
    vector<ll> X(N), Y(N);
    for(ll i=0; i<N; i++) {
        cin >> X[i] >> Y[i];
    }

    // 到達可能同士のグループに分ける
    vector<ll> A, B;
    A.push_back(0);
    for(ll i=1; i<N; i++) {
        ll dx = abs(X[0]-X[i]);
        ll dy = abs(Y[0]-Y[i]);
        if (dx%2==0) { // xの差が偶数のとき
            if (dy%2==0) A.push_back(i);
            else B.push_back(i);
        }
        else {//xの差が奇数のとき
            if (dy%2==0) B.push_back(i);
            else A.push_back(i);
        }
    }

    // iとjが到達可能なとき、距離distを計算できる
    auto dist = [&](ll i, ll j) {
        return max(abs(X[i]-X[j]), abs(Y[i]-Y[j]));
    };

    // ソルバー
    auto f = [&](vector<ll> vec) {
        ll N = vec.size();
        ll res = 0;

        // ここなんとかO(N)にしたい
        for(ll i=0; i<N; i++) {
            ll pi = vec[i];
            for(ll j=i+1; j<N; j++) {
                ll pj = vec[j];
                res += dist(pi, pj);
            }
        }
        return res;
    };

    ll ans = 0;
    ans += f(A);
    ans += f(B);
    cout << ans << endl;
}


// 解説AC
void solve2() {
    ll N; cin >> N;
    vector<vector<ll>> Xs(2), Ys(2);
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        ll u = x+y;
        ll v = x-y;
        Xs[u%2].push_back(u);
        Ys[u%2].push_back(v);
    }

    auto f = [&](vector<ll> Xs) -> ll {
        ll N = Xs.size();
        sort(Xs.begin(), Xs.end());
        ll res = 0;
        for(ll i=0; i<N; i++) {
            ll co = i -(N-i-1LL);
            res += co*Xs[i];
        }
        return res/2LL;
    };

    ll ans = 0;
    for(ll i=0; i<2; i++) ans += f(Xs[i]) + f(Ys[i]);
    cout << ans << endl;
}


void solve3() {
    ll N; cin >> N;
    vector<vector<ll>> Xs(2), Ys(2); // 45度回転後の座標。到達可能性でグループ分けする
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        ll u = x+y;
        ll v = x-y;
        Xs[u%2].push_back(u);
        Ys[u%2].push_back(v);
    }

    // 二重和：ΣΣ|u[i]-u[j]|をO(N)で求める
    auto f = [&](vector<ll> Xs) -> ll {
        ll N = Xs.size();
        sort(Xs.begin(), Xs.end());
        ll res = 0;
        for(ll i=0; i<N; i++) res -= (N-1LL-i)*Xs[i];
        for(ll i=1; i<N; i++) res += i*Xs[i];
        return res/2LL;
    };

    // 答え
    ll ans = 0;
    for(ll i=0; i<2; i++) ans += f(Xs[i]) + f(Ys[i]);
    cout << ans << endl;
}

int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}