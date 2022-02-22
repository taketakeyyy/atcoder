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

/* 平均mid以上にすることができるか？ */
bool average_main(ll mid, ll N, vector<ll> &A) {
    vector<ll> f(N, 0);  // f[i] := i番目までのカードを選び、i番目のカードを選ぶときのB[i]の総和の最大値
    vector<ll> g(N, 0);  // g[i] := i番目までのカードを選び、i番目のカードを選ばないときのB[i]の総和の最大値
    f[0] = A[0]-mid;
    g[0] = 0;

    for(ll i=1; i<N; i++) {
        ll b = A[i]-mid;
        f[i] = max(f[i-1]+b, g[i-1]+b);
        g[i] = f[i-1];
    }

    if (f[N-1] >= 0 || g[N-1] >= 0) {
        // 平均値mid以上は作れる
        return true;
    }
    return false;
}

ll average(ll N, vector<ll> &A) {
    ll l=0, r=1000000000001;
    while(abs(r-l) > 1) {
        ll mid = (l+r)/2;
        bool is_ok = average_main(mid, N, A);

        if (is_ok) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    if (average_main(l, N, A)) {
        return l;
    }
    else {
        return r;
    }
}


bool median_main(ll mid, ll N, vector<ll> &A) {
    vector<ll> f(N, 0);
    vector<ll> g(N, 0);
    if (A[0] >= mid) {
        f[0] = 1;
    }
    else {
        f[0] = -1;
    }
    g[0] = 0;

    for (ll i=1; i<N; i++) {
        ll b;
        if (A[i] >= mid) {
            b = 1;
        }
        else {
            b = -1;
        }
        f[i] = max(f[i-1]+b, g[i-1]+b);
        g[i] = f[i-1];
    }

    if (f[N-1] > 0 || g[N-1] > 0) {
        return true;
    }
    return false;
}

ll median(ll N, vector<ll> &A) {
    ll l=0, r=1000000000001;
    while(abs(r-l) > 1) {
        ll mid = (l+r)/2;
        bool is_ok = median_main(mid, N, A);

        if (is_ok) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    if (median_main(l, N, A)) {
        return l;
    }
    return r;
}


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        A[i] *= 1000;
    }

    ll ans1 = average(N, A);
    ll ans2 = median(N, A);

    printf("%.3lf\n", (double)ans1/1000);
    cout << ans2/1000 << endl;
}


int main() {
    solve();
    return 0;
}