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
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}


ll g1(ll x) {
    if (x==0) return 0;

    vector<ll> Xs;
    ll a = x;
    while(1) {
        if (a==0) break;
        ll amari = a%10;
        Xs.emplace_back(amari);
        a /= 10;
    }

    sort(Xs.begin(), Xs.end());

    ll ans = 0;
    ll b = 1;
    for(ll i=0; i<Xs.size(); i++) {
        ans += Xs[i]*b;
        b *= 10;
    }
    return ans;
}

ll g2(ll x) {
    // 小さい順に並び替える
    if (x==0) return 0;

    vector<ll> Xs;
    ll a = x;
    while(1) {
        if (a==0) break;
        ll amari = a%10;
        Xs.emplace_back(amari);
        a /= 10;
    }

    sort(Xs.rbegin(), Xs.rend());

    ll ans = 0;
    ll b = 1;
    for(ll i=0; i<Xs.size(); i++) {
        ans += Xs[i]*b;
        b *= 10;
    }
    return ans;
}

ll f(ll x) {
    return g1(x)-g2(x);
}


void solve(){
    ll N, K; cin >> N >> K;
    vector<ll> As(K+1);
    As[0] = N;

    for (int i=0; i<K; i++) {
        As[i+1] = f(As[i]);
    }
    cout << As[K] << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}