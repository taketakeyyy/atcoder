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
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, Q; cin >> N >> Q;
    string S; cin >> S;
    ll ans = 0;
    for(ll i=0; i<N-2; i++) {
        if (S[i]=='A' and S[i+1]=='B' and S[i+2]=='C') ans++;
    }

    auto f = [&S, &N](ll x) {
        if (S[x] == 'A') {
            if (x+2<N and S[x+1]=='B' and S[x+2]=='C') return true;
            return false;
        }
        if (S[x] == 'B') {
            if (x-1>=0 and x+1<N and S[x-1]=='A' and S[x+1]=='C') return true;
            return false;
        }
        if (S[x] == 'C') {
            if (x-2>=0 and S[x-2]=='A' and S[x-1]=='B') return true;
            return false;
        }
        return false;
    };

    for(ll q=0; q<Q; q++) {
        ll x; char c; cin >> x >> c;
        x--;

        // xの位置のABCを探す
        if (f(x)) ans--;

        S[x] = c;
        if (f(x)) ans++;

        // 出力
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}