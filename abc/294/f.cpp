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


// 解説AC
void solve() {
    ll N, M, K; cin >> N >> M >> K;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }
    vector<ll> C(M), D(M);
    for(ll i=0; i<M; i++) {
        cin >> C[i] >> D[i];
    }

    double ng=0., ok=1.;
    for(ll i=0; i<100; i++) { // 適当回数
        double x = (ng+ok)/2;  // 濃度x
        double z = x/(1-x);
        vector<double> v(M);
        for(ll j=0; j<M; j++) v[j] = C[j] - D[j] * z;
        sort(v.begin(), v.end());

        ll num = 0;
        for(ll j=0; j<N; j++) {
            double w = A[j] - B[j] * z;
            num += M - (lower_bound(v.begin(), v.end(), -w) - v.begin());
        }
        (num < K ? ok : ng) = x;
    }
    printf("%.10lf\n", ok*100);
}


// 解説動画AC
void solve2() {
    ll N, M, K; cin >> N >> M >> K;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }
    vector<ll> C(M), D(M);
    for(ll i=0; i<M; i++) {
        cin >> C[i] >> D[i];
    }

    for(ll i=0; i<N; i++) B[i] += A[i];
    for(ll i=0; i<M; i++) D[i] += C[i];

    double ac = 0, wa = 1;
    auto f = [&](double x) {
        vector<double> S(N), T(M);
        for(ll i=0; i<N; i++) S[i] = A[i] - B[i]*x;
        for(ll i=0; i<M; i++) T[i] = D[i]*x - C[i];
        sort(S.begin(), S.end());
        sort(T.begin(), T.end());

        ll j = 0, res = 0;
        for(ll i=0; i<N; i++) {
            while(j < M && T[j] < S[i]) j++;
            res += j;
        }
        return res;
    };

    for(ll i=0; i<100; i++) {
        double wj = (ac+wa)/2;
        if (f(wj) >= K) ac = wj;
        else wa = wj;
    }

    printf("%.10lf\n", ac*100);
}


// 解説動画AC
void solve3() {
    ll N, M, K; cin >> N >> M >> K;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }
    vector<ll> C(M), D(M);
    for(ll i=0; i<M; i++) {
        cin >> C[i] >> D[i];
    }

    // 二分探索用関数
    // f(x) := 濃度がx以上のものの個数
    auto f = [&](double x) {
        vector<double> S(N), T(M);
        for(ll i=0; i<N; i++) S[i] = A[i] - (A[i]+B[i])*x;
        for(ll i=0; i<M; i++) T[i] = (C[i]+D[i])*x - C[i];
        sort(T.begin(), T.end());

        ll res = 0;
        for(ll i=0; i<N; i++) {
            // T の中で S[i] 以下の値は何個？
            ll idx = upper_bound(T.begin(), T.end(), S[i]) - T.begin();
            res += idx;
        }
        return res;
    };

    // 二分探索
    double ac = 0, wa = 1;
    for(ll i=0; i<100; i++) { // 小数の二分探索は適当な固定回数回す(100で十分)
        double wj = (ac+wa)/2;
        if (f(wj) >= K) ac = wj;
        else wa = wj;
    }
    printf("%.10lf\n", ac*100);
}


int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}