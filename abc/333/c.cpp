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

// レピュニットを用意すればOK
void solve() {
    ll N; cin >> N;
    vector<ll> repunit;
    ll one = 1;
    ll REP_SIZE = 19;
    for(ll i=1; i<=REP_SIZE; i++) {
        repunit.push_back(one);
        one *= 10; one+=1;
    }

    vector<ll> rep_sum;
    for(ll i=0; i<REP_SIZE; i++) {
        ll a = repunit[i];
        for(ll j=i; j<REP_SIZE; j++) {
            ll b = repunit[j];
            for(ll k=j; k<REP_SIZE; k++) {
                ll c = repunit[k];
                rep_sum.push_back(a+b+c);
            }
        }
    }
    sort(rep_sum.begin(), rep_sum.end());

    // cout << rep_sum.size() << endl;
    cout << rep_sum[N-1] << endl;
}


int main() {
    solve();
    return 0;
}