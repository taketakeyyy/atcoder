#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%MOD+MOD)%MOD){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += MOD-a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= MOD; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime MOD
    mint inv() const { return pow(MOD-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
};


void solve(){
    /*解説AC*/
    int N, C;
    cin >> N >> C;
    map<int, ll> events;
    for(int i=0; i<N; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        events[a] += c;
        events[b+1] -= c;
    }

    ll ans = 0L;
    int pre_key = -1;
    ll pre_value;
    for (auto p: events) {
        auto key = p.first;
        auto value = p.second;
        if (pre_key == -1) {
            pre_key = key;
            pre_value = value;
            continue;
        }

        if (pre_value < C) {
            ans += pre_value * (ll)(key - pre_key);
        }
        else {
            ans += (ll)C * (ll)(key - pre_key);
        }

        pre_value += value;
        pre_key = key;
    }

    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}