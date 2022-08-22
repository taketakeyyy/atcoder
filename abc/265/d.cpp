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


void solve1() {
    ll N, P, Q, R; cin >> N >> P >> Q >> R;
    vector<ll> A(N+1);
    vector<ll> rA(N+1, 0);  // 累積和
    for(ll i=1; i<=N; i++) {
        cin >> A[i];
        rA[i] += rA[i-1] + A[i];
    }

    for(ll x=1; x<N; x++) {
        ll xi = lower_bound(rA.begin(), rA.end(), P+rA[x-1]) - rA.begin();
        if (rA[xi] != P+rA[x-1]) continue;

        ll y=xi+1;
        ll yi = lower_bound(rA.begin(), rA.end(), Q+rA[y-1]) - rA.begin();
        if (rA[yi] != Q+rA[y-1]) continue;

        ll z=yi+1;
        ll zi = lower_bound(rA.begin(), rA.end(), R+rA[z-1]) - rA.begin();
        if (rA[zi] != R+rA[z-1]) continue;

        ll w=zi+1;

        x--; y--; z--; w--;
        if (w <= N) {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
}


void solve2() {
    ll N, P, Q, R; cin >> N >> P >> Q >> R;
    vector<ll> A(N+1);
    vector<ll> rA(N+1, 0);  // 累積和
    set<ll> rAset; rAset.insert(0);  // 累積和のset
    for(ll i=1; i<=N; i++) {
        cin >> A[i];
        rA[i] += rA[i-1] + A[i];
        rAset.insert(rA[i]);
    }

    for(ll i=0; i<=N; i++) {
        if (rAset.count(rA[i]+P) && rAset.count(rA[i]+P+Q) && rAset.count(rA[i]+P+Q+R)) {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
}


int main() {
    // solve1();
    solve2();
    return 0;
}