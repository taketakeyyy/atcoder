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

double distance(ll x1, ll y1, ll x2, ll y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}



void solve() {
    ll N; cin >> N;
    vector<pair<ll,ll>> XYs(N);
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        XYs[i] = {x,y};
    }
    vector<ll> A(N);
    for(ll i=0; i<N; i++) A[i] = i;

    // 順列全列挙
    double ans = 0;
    ll cnt = 0;
    do {
        cnt++;
        double total = 0;
        for(ll i=1; i<N; i++) {
            auto[x1, y1] = XYs[A[i-1]];
            auto[x2, y2] = XYs[A[i]];
            total += distance(x1, y1, x2, y2);
        }
        ans += total;
    }while(next_permutation(A.begin(), A.end()));
    ans /= cnt;

    // 出力
    printf("%.7lf\n", ans);
}


int main() {
    solve();
    return 0;
}